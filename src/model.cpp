#include <fstream>

#include "model.hpp"

model::Mesh model::Mesh::load(char const* filename) {
    std::ifstream input{filename};
    if (!input)
        throw std::runtime_error{"can not read"};
    std::string reserved;
    input >> reserved;
    if (reserved != "OFF")
        throw std::runtime_error{"invalid file"};
    int n_nodes, n_faces, n_edges;
    input >> n_nodes >> n_faces >> n_edges;
    Mesh mesh{};
    mesh.nodes.reserve(n_nodes);
    mesh.faces.reserve(n_faces);

    for (int i = 0; i < n_nodes; ++i) {
        vector3d pos{};
        input >> pos[0] >> pos[1] >> pos[2];
        mesh.nodes.push_back(Node{pos, i});
    }
    for (int i = 0; i < n_faces; ++i) {
        int n_nodes_on_face;
        input >> n_nodes_on_face;
        auto type =
                n_nodes_on_face == 3 ? Face::Type::Triangle:
                n_nodes_on_face == 4 ? Face::Type::Rectangle:
                throw std::runtime_error{"invalid face"};
        std::vector<Index<Node>> node_ids{};
        util::times(n_nodes_on_face, [&]() {
            int id;
            input >> id;
            node_ids.push_back(Index<Node>{id});
        });
        mesh.faces.push_back(Face{type, i, node_ids});
    }
    return mesh;
}

