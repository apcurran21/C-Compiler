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
    void forProgram(Program *p){
        for (Function *fptr : p->functions){
            forFunction(fptr);
        }
    }
    void forFunction(Function *f) {
        std::list<Block*> blockList(f->codeBlocks.begin(), f->codeBlocks.end());

        // Clear the execution trace order to prepare for new linearization
        f->executionTraceOrder.clear();

        while (!blockList.empty()) {
            // Fetch the first block from the list
            Block* block = blockList.front();
            blockList.pop_front();

            // Only process the block if it has not been marked yet
            while (block && !block->marked) {
                // Mark the block as visited
                block->marked = true;

                // Add the block to the execution trace order
                f->executionTraceOrder.push_back(block);

                // Check for an unmarked successor to continue the trace
                Block* nextBlock = nullptr;
                for (auto successor : block->successors) {
                    if (!successor->marked) {
                        // Select the first unmarked successor
                        nextBlock = successor;
                        break;
                    }
                }

                // If an unmarked successor is found, remove it from the blockList
                if (nextBlock) {
                    blockList.remove(nextBlock);
                }

                // Move to the next block for the next iteration
                block = nextBlock;
            }
        }
    }
}
