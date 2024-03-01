#include "Tree.h"

namespace L3 {

    Tree::Tree(Instruction *instr) : i(instr) {

    }

    void Tree::addChild(Tree *child) {
        children.push_back(child);
    }

    void Tree::addParent(Tree *parent) {
        parents.push_back(parent);
    }

} // namespace L3
