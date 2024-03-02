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
            Block *currentBlock = nullptr; // Pointer to hold the current block

            for (auto i : fptr->instructions) {
                auto label_cast = dynamic_cast<labelInstruction *>(i);
                if (label_cast) {
                    if (currentBlock) {
                        appendBlock.push_back(currentBlock); // Append the current block to the vector
                    }
                    currentBlock = new Block(label_cast->label); // Create a new block for the new label
                }
                if (!currentBlock) {
                    currentBlock = new Block(""); // Create a new block if there's no current block
                }
                currentBlock->appendInstruction(i); // Append instruction to the current block
            }
            if (currentBlock) {
                appendBlock.push_back(currentBlock); // Append the last block to the vector
            }
            fptr->codeBlocks = appendBlock;
        }
    }
}
