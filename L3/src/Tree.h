#pragma once

#include <L3.h>

namespace L3{
    class Tree {
        public:
            Tree (L3::Instruction *i);
            void addChild(Tree *child);
            void addParent(Tree *parent);
            std::string toString(void);
            Instruction *i;
            std::vector<Tree *> children;
            std::vector<Tree*> parents;
    };
}