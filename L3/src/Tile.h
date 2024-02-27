#pragma once 

#include <Tree.h>

namespace L3{
    class Tile {
        public:
        Tile (std::string const &name);

        Tree *tree;
        std::string tileName;
    }
}