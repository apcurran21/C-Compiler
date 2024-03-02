#pragma once
#include <set>
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <tuple>
#include "IR.h"

namespace IR {
    void createCodeBlock(Program *p) {
        for (auto *fptr : p->functions) {
            std::vector<Block *> appendBlock;
            Block *currentBlock = nullptr; // Initialize currentBlock to nullptr.

            for (auto i : fptr->instructions) {
                auto label_cast = dynamic_cast<labelInstruction *>(i);
                if (label_cast) {
                    if (currentBlock) {
                        appendBlock.push_back(currentBlock); // Append the current block to the vector if it exists.
                    }
                    currentBlock = new Block(label_cast->label); // Create a new block for the new label.
                    // Since we're sure this happens for the first instruction, there's no need for a !currentBlock check.
                }
                currentBlock->appendInstruction(i); // Append instruction to the current block.
            }

            // After the loop, append the last block to the vector if it exists.
            if (currentBlock) {
                appendBlock.push_back(currentBlock);
            }

            fptr->codeBlocks = appendBlock; // Assign the vector of blocks to the function's codeBlocks.
        }
    }
}
