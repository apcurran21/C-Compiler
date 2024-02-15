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

#include <parser.h>
#include "liveness_analysis.h"
#include "interference_graph.h"
#include "spill.h"
#include "graph_coloring.h"
#include <code_generator.h>
#include "spill_code_generator.h"
#include "L2.h"

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
    // p = L2::parse_spill_file(argv[optind]);
    // auto replacementVar = p.variables[p.variables.size() - 2]; 
    // bool changed = L2::spillForL2(p,replacementVar);
    // L2::generate_spill_code(p, changed, );

    // idk how we were testing spill, should fix before submitting
    // the setup seems super specific to one test case
  }

  /*
   * Liveness test.
   */
  if (liveness_only){
    // auto In_Out_sets = L2::liveness_analysis(&p, true);
    auto gen_kill_sets = L2::Gen_Kill_Store(&p);
    auto in_out_sets = L2::In_Out_Store(&p);
    auto curr_f_res = L2::liveness_analysis(&p, 0, gen_kill_sets, in_out_sets, true);

    return 0;
  }

  /*
   * Interference graph test.
   */
  if (interference_only){
    // auto liveness = L2::liveness_analysis(&p, false);
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
    L2::Gen_Kill_Store gen_kill_sets = L2::Gen_Kill_Store(&p);
    L2::In_Out_Store in_out_sets = L2::In_Out_Store(&p);

    /*
    Create a graph and run the coloring algorithm for each of the program's functions
    -NOTE! we should probably keep the list of spilled variables external to the graph instance
      - it would make sense to keep a set/vector as a field in the current function instance
    */
    int f_index = 0;
    for (auto fptr : p.functions) {
      while (true){
        /*
        Compute liveness for the current state of the current function
        - ie there might be additional spill instructions from the last iteration of the do-while loop
        */
        L2::Curr_F_Liveness liveness_results = L2::liveness_analysis(&p, f_index, gen_kill_sets, in_out_sets, false);

        /*
        Build an interference graph based off of the liveness
        */
        Graph* graph = L2::build_graph(fptr, liveness_results);

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
        auto color_result = L2::color_graph(graph);
        bool big_fail = std::get<0>(color_result);
        std::set<Variable*> new_spilled_vars = std::get<1>(color_result);

        if (big_fail) {
          /*
          Spill everything then do the code generation
          - this will likely entail adding all variables to the function's spilled vars list then going through this loop one more time.
          - since spilled variables are guaranteed not to interfere, we could also just color each one of these spilled variables in the
            updated program representation with "r10" since we know it is highest priority. The loop would then end and we could generate code.
          */
          break;
        } else if (new_spilled_vars.size() == 0) {
          /*
          Every variable was able to be colored, meaning we can move onto the code generation track
          the current state of the graph and move onto code generation.
          */
          all_graphs[fptr] = graph;
          break;
        } else {
          /*
          Some variables could not be colored, so we spill each of them and retry coloring in the next while loop iteration.
          */
          for (auto var : new_spilled_vars) {
            L2::spillForL2(p, var);
          }
        }
        if (debug) std::cerr << "made it out of the coloring loop for function " << fptr->name << "\n";
      }
      
    

      /*
      Now that we have all the colored graphs, we can generate the code.
      */
      
    }

      




  //     /*
  //     Create a convenience struct to hold the gen, kill, in, and out sets for the current function.
  //     */
  //     L2::Curr_F_Liveness curr_f_liveness = {
  //       liveness_results.gen_kill_sets.Gen_Set[f_index],
  //       liveness_results.gen_kill_sets.Kill_Set[f_index],
  //       liveness_results.in_out_sets.In_Set[f_index],
  //       liveness_results.in_out_sets.Out_Set[f_index]
  //     };

  //     // auto g = build_graph(p, liveness_results);
  //     auto g = L2::build_graph(fptr, curr_f_liveness);

  //     bool changed = false;



  //     f_index++;
  //   }

  //   do {



  //   } while ()







  //   /*
  //   'liveness_results' holds a Gen_Kill_Store and an In_Out_Store,
  //   where each store tracks the corresponding sets for each instruction
  //   within each function of the program.
  //   */
  //   auto liveness_results = L2::liveness_analysis(&p, false);

  //   /*
  //   initialize a map so that we can track the interference graphs for each function
  //   */
  //   std::map<L2::Function*, L2::Graph*> all_graphs;

  //   /*
  //   Create and color a graph for each of the program's functions
  //   */
  //   int f_index = 0;
  //   for (auto fptr : p.functions) {
  //     /*
  //     Create a convenience struct to hold the gen, kill, in, and out sets for the current function.
  //     */
  //     L2::Curr_F_Liveness curr_f_liveness = {
  //       liveness_results.gen_kill_sets.Gen_Set[f_index],
  //       liveness_results.gen_kill_sets.Kill_Set[f_index],
  //       liveness_results.in_out_sets.In_Set[f_index],
  //       liveness_results.in_out_sets.Out_Set[f_index]
  //     };

  //     // auto g = build_graph(p, liveness_results);
  //     auto g = L2::build_graph(fptr, curr_f_liveness);

  //     bool changed = false;



  //     f_index++;
  //   }

  //   auto g = new L2:: Graph();
  //   bool changed = false;
  //   // L2::Graph colored_graph;
  //   // do {
  //     /*
  //     We want to continue our process of generating liveness, creating the
  //     interference graph based on it, and coloring that graph until we are able to
  //     color all variables. At this point, we can replace all the variables with their
  //     corresponding colors in the final interference graph.
  //     */
  //   //   auto liveness = L2::liveness_analysis(&p, false);
  //   //   auto interference_graph = g->build_graph(p, liveness);
  //   //   auto g = new L2::Graph();
  //   //   auto colored_graph = L2::color_graph(interference_graph);
  //   //   for (auto var_ptr : interference_graph->spilled_vars) {
  //   //     // what is 'changed' for?
  //   //     bool changed = L2::spillForL2(p, var_ptr);
  //   //   }
  //   // } while (false); // we should really do while interference graph produces new spilled variables

  //   // use the interference graph to replace the variables in the program with registers
    
  //   // run code gen on the updated program
  //   // L2::generate_code(p, colored_graph); 
  //   return 0;
  }

  return 0;
}
