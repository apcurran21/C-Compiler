#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <iterator>
#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <assert.h>
#include <tuple>
// #include "L2/src/parser.h"
#include "parser.h"
#include "liveness_analysis.h"
#include "interference_graph.h"
#include "spill.h"
#include "graph_coloring.h"
#include "graph_coloring_alt.h"
#include <code_generator.h>
#include "spill_code_generator.h"
#include "L2.h"
#include "spill.h"
#include <unordered_map>

/*
Debugging
*/
int printdebug = 1;

void print_help (char *progName){
  // std::cerr << "Usage: " << progName << " [-v] [-g 0|1] [-O 0|1|2] [-s] [-l] [-i] SOURCE" << std::endl;
  std::cerr << "Usage: " << progName << " [-v] [-g 0|1] [-O 0|1|2] [-s] [-l] [-i] [-c] SOURCE" << std::endl;
  // ^ pass the argument c to run the graph coloring.
  return ;
}

int main(
  int argc, 
  char **argv
  ){
  auto enable_code_generator = true;
  auto spill_only = false;
  auto interference_only = false;
  auto liveness_only = false;
  auto run_color = false; // extra debug
  int32_t optLevel = 3;

  /* 
   * Check the compiler arguments.
   */
  auto verbose = false;
  if( argc < 2 ) {
    print_help(argv[0]);
    return 1;
  }
  int32_t opt;
  int64_t functionNumber = -1;
  while ((opt = getopt(argc, argv, "vg:O:slic")) != -1) {
    switch (opt){

      case 'l':
        liveness_only = true;
        break ;

      case 'i':
        interference_only = true;
        break ;

      case 's':
        spill_only = true;
        break ;

      case 'O':
        optLevel = strtoul(optarg, NULL, 0);
        break ;

      case 'g':
        enable_code_generator = (strtoul(optarg, NULL, 0) == 0) ? false : true ;
        break ;

      case 'v':
        verbose = true;
        break ;

      // our extra debug
      case 'c':
        run_color = true;
        break ;

      default:
        print_help(argv[0]);
        return 1;
    }
  }

  /*
   * Parse the input file.
   */
  L2::Program p;
  if (spill_only){

    /* 
     * Parse an L2 function and the spill arguments.
     */
    //p = L2::parse_spill_file(argv[optind]);
 
  } else if (liveness_only){

    /*
     * Parse an L2 function.
     */
    p = L2::parse_function_file(argv[optind]);
  } else if (interference_only || run_color){

    /*
     * Parse an L2 function.
     */
    p = L2::parse_function_file(argv[optind]);

  } else {

    /* 
     * Parse the L2 program.
     */
    p = L2::parse_file(argv[optind]);

  }

  /*
   * Special cases.
   */
  if (spill_only){
    p = L2::parse_spill_file(argv[optind]);

    if (printdebug) {
      std::cerr << "printing liveness before the spill\n\n";
      auto gen_kill_sets = L2::Gen_Kill_Store(&p);
      auto in_out_sets = L2::In_Out_Store(&p);
      L2::Curr_F_Liveness liveness_results = L2::liveness_analysis(&p, 0, gen_kill_sets, in_out_sets, true);
    }

    auto replacementVar = p.variables[p.variables.size() - 2]; 
    std::tuple resultTuple = L2::spillForL2(p.functions[0] ,replacementVar, -1);
    auto changed = std::get<0>(resultTuple);

    L2::generate_spill_code(p, changed);


    if (printdebug) {
      std::cerr << "printing liveness after the spill\n\n";
      auto gen_kill_sets = L2::Gen_Kill_Store(&p);
      auto in_out_sets = L2::In_Out_Store(&p);
      L2::Curr_F_Liveness liveness_results = L2::liveness_analysis(&p, 0, gen_kill_sets, in_out_sets, true);
    }

    // idk how we were testing spill, should fix before submitting
    // the setup seems super specific to one test case
  }

  /*
   * Liveness test.
   */
  if (liveness_only){
    // std::cerr << "in liveness before" << std::endl;
    // auto In_Out_sets = L2::liveness_analysis(&p, true);
    auto gen_kill_sets = L2::Gen_Kill_Store(&p);
    // std::cerr << "in liveness befor1e" << std::endl;
    auto in_out_sets = L2::In_Out_Store(&p);
    // std::cerr << "in liveness befor2e" << std::endl;
    auto curr_f_res = L2::liveness_analysis(&p, 0, gen_kill_sets, in_out_sets, true);
    // std::cerr << "in liveness compiler" << std::endl;
    return 0;
  }

  /*
   * Interference graph test.
   */
  if (interference_only){
    L2::Gen_Kill_Store gen_kill_sets = L2::Gen_Kill_Store(&p); 
    L2::In_Out_Store in_out_sets = L2::In_Out_Store(&p);
    L2::Curr_F_Liveness liveness_results = L2::liveness_analysis(&p, 0,  gen_kill_sets, in_out_sets, false);
    auto interference_graph = L2::build_graph(p.functions[0], liveness_results);
    interference_graph->printGraph();


    // auto g = new L2::Graph();
    // auto interference_graph = g->build_graph(p, liveness);
    // auto interference_graph = build_graph(p, liveness);
    // interference_graph->printGraph();
    return 0;
  }

  /*
  Extra debug graph coloring test.
  - currently it will just run the graph coloring alg once, edit later
  */
  if (run_color){
    // auto liveness = L2::liveness_analysis(&p, false);
    // // auto g = new L2::Graph();
    // // auto interference_graph = g->build_graph(p, liveness);
    // auto interference_graph = build_graph(p, liveness);
    // auto colored_graph = L2::color_graph(interference_graph);
    // // colored_graph->printGraph();
    // colored_graph->printColors();
    return 0;
  }

  /*
   * Generate the target code.
   */
  if (enable_code_generator){

    /*
    initialize a map so that we can track the interference graphs for each function
    */
    std::map<L2::Function*, L2::Graph*> all_graphs;

    /*
    initialize stores for the gen, kill, in, and out sets for each instruction in each function.
    - remember a store has structure vector<map<instruction, set>>
    */

    /*
    Create a graph and run the coloring algorithm for each of the program's functions
    -NOTE! we should probably keep the list of spilled variables external to the graph instance
      - it would make sense to keep a set/vector as a field in the current function instance
    */
    int f_index = 0;
    for (int f_index =0; f_index<p.functions.size();f_index++) {
      int spill_count = -1;
      auto fptr = p.functions[f_index];
      std::unordered_map<std::string, int> seenMap;
      while (true){
        L2::Gen_Kill_Store gen_kill_sets = L2::Gen_Kill_Store(&p);
        L2::In_Out_Store in_out_sets = L2::In_Out_Store(&p);
        /*
        Compute liveness for the current state of the current function
        - ie there might be additional spill instructions from the last iteration of the do-while loop
        */
        if (printdebug) std::cerr << "Printing in and out sets:\n";
        L2::Curr_F_Liveness liveness_results = L2::liveness_analysis(&p, f_index, gen_kill_sets, in_out_sets, printdebug);

        /*
        Build an interference graph based off of the liveness
        */
        L2::Graph* graph = L2::build_graph(fptr, liveness_results);
        if (printdebug) std::cerr << "Printing the graph:\n";
        if (printdebug) graph->printGraph();
        /*
        Color the interference graph
        - if the coloring was successful, then the size of the function's spilled variables set
          and the graph's spilled varaiables set will be the same.
        - if the two sets are not the same size, then this means that the graph coloring alg found 
          a particular variable that could not be allocated a register
        - note that we also need to check whether or not the coloring failed altogether - ie we found 
          a variable that couldn't be colored or spilled!
            - maybe we could just return a tuple that also contains the big Fail bool for this case
        */
        //std::tuple nodes_to_spill = L2::color_graph_alt(p, graph, fptr);
        // std::vector<L2::Node*> nodes_to_spill = std::get<1>(color_result);
        std::vector<L2::Node*> nodes_to_spill = L2::color_graph_alt(p, graph, fptr);
        // std::vector<L2::Variable*> new_spilled_vars;
        bool big_fail = false;

        if (big_fail) {
          /*
          Spill everything:
          */
          /*
          Spill all variables which aren't registers and aren't already spill variables
          */
          for (auto& pair : graph->nodes) {
            auto var = pair.first;
            auto reg_ptr = dynamic_cast<L2::Register*>(var);
            if ((!reg_ptr) && (fptr->spill_variables_set.find(var) == fptr->spill_variables_set.end())) {
              std::tuple<std::set<std::string>,L2::Function*> resultTuple = L2::spillForL2(fptr, var, spill_count);
              auto changed = std::get<0>(resultTuple); // For the std::set<std::string>
              L2::Function* newFunction = std::get<1>(resultTuple);
              fptr = newFunction;
              spill_count++;
            }
          }
          break;
        // } else if (new_spilled_vars.size() == 0) {
        } else if (nodes_to_spill.size() == 0) {
          /*
          Every variable was able to be colored, meaning we can move onto the code generation track
          the current state of the graph and move onto code generation.
          */
          all_graphs[fptr] = graph;
          break;
        } else {
          /*
          Some variables could not be colored, so we spill each of them and retry coloring in the next while loop iteration.
          - this function should also keep track of the new spill variables so we don't accidentally spill them later
          */
         /*
         bool duplicate_checker =false;
          for (auto &node : nodes_to_spill) {
            if (seenMap.find(node->var->name) != seenMap.end()){
              duplicate_checker = true;
              break;
            }
          }
          if (duplicate_checker){
            all_graphs[fptr] = graph;
            break;
          }
         
         */
          
          L2::PrintVisitor* myPrintVisitor = new L2::PrintVisitor();
          if (printdebug) std::cerr << "Printing program before spill:\n\n";
          for (auto &iptr : fptr->instructions) {
            iptr->accept(myPrintVisitor);
          }
          for (auto &node : nodes_to_spill) {
            std::tuple resultTuple = L2::spillForL2(fptr, node->var, 1);
            auto spilled_set = std::get<0>(resultTuple);
            L2::Function* newFunction = std::get<L2::Function*>(resultTuple);
            fptr = newFunction;
            spill_count++;
          }
          if (printdebug) std::cerr << "Printing program after spill:\n\n";
          for (auto &iptr : fptr->instructions) {
            iptr->accept(myPrintVisitor);
          }
          // seen_set = nodes_to_spill;
          /*
          Add the newly spilled variables to the function's tracking set. The color graph in the next loop iteration will get this updated set.
          - actually this probably isn't necessary, we only need to track the spill variables
          */
          // fptr->spilled_variables.insert(new_spilled_vars.begin(), new_spilled_vars.end());
        }
        // if (debug) std::cerr << "made it out of the coloring loop for function " << fptr->name << "\n";
      }
    }
    /*
    Now that we have all the colored graphs, we can generate the code.
    */
    L2::generate_code(p, all_graphs);
  }
  return 0;
}
