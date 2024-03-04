#include <set>
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <tuple>
#include "calculateCFG.h"

namespace IR {

    extern int const debug;
    
    void calculateCFG::forFunction(Function *f){
            std::queue<Block *> queue;
            for (auto block : f->codeBlocks){
                queue.push(block);
            };
            while (!queue.empty()){
                auto block = queue.front();
                queue.pop();
                while (!block->marked){
                    block ->marked = true;
                    f->executionTraceOrder.push_back(block);
                    for (auto blockSuccessor : block->successors){
                        if (!blockSuccessor->marked){
                            block = blockSuccessor;
                        }
                    }
                }
            }
        };

}