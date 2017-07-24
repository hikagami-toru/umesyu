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

static vector3d calc_triangle_normal(std::array<vector3d, 3> const& nodes_pos) {
    auto a = nodes_pos[1] - nodes_pos[0];
    auto b = nodes_pos[2] - nodes_pos[0];
    return cross(a, b).normal();
}

void model::Face::split_to_triangles(std::vector<TriangleInfo>& triangles, Mesh const& mesh) const {
    auto node_pos = [&](int i) -> vector3d {
        auto node_index = node_indices[i].data;
        return mesh.nodes[node_index].position;
    };
    auto make_triangle_info = [&](std::array<int, 3> const& indicies) -> TriangleInfo {
        std::array<vector3d, 3> positions{
            node_pos(indicies[0]), node_pos(indicies[1]), node_pos(indicies[2])
        };
        return TriangleInfo {
            positions,
            calc_triangle_normal(positions)
        };
    };

    switch (type) {
    case Type::Triangle:
        triangles.push_back(make_triangle_info({0, 1, 2}));
        break;
    case Type::Rectangle:
        triangles.push_back(make_triangle_info({0, 1, 2}));
        triangles.push_back(make_triangle_info({0, 2, 3}));
        break;
    }
}
