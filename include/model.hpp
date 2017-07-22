#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <array>

#include "utility.hpp"
#include "vector.hpp"

namespace model {

struct Node {
    vector3d position;
    Index<Node> index;
};

struct Cell {
    enum class Type {
        Tetra,
        Hexa,
    };
    Type type;
    Index<Cell> index;
    std::vector<Index<Node>> node_indices;
};

struct Face {
    enum class Type {
        Triangle,
        Rectangle,
    };
    Type type;
    Index<Face> index;
    std::vector<Index<Node>> node_indices;
};

struct Mesh {
    std::vector<Node> nodes;
    std::vector<Cell> cells;
    std::vector<Face> faces;

    static Mesh load(char const* filename);
};


}

#endif // MODEL_HPP
