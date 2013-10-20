#pragma once
#include <vector>

#include <EigenTypedef.h>
#include <Mesh.h>

#include "EdgeMap.h"

class MeshSeparator {
    public:
        MeshSeparator(const MatrixI& faces);

        size_t separate();
        MatrixI get_component(size_t i) {
            return m_components.at(i);
        }

        void clear();

    private:
        void compute_face_connectivity();
        MatrixI flood(size_t seed);
        std::vector<size_t> get_adjacent_faces(size_t fi);

    private:
        std::vector<MatrixI> m_components;
        MatrixI m_faces;
        std::vector<bool> m_visited;

        typedef EdgeMap<size_t> EdgeMapI;
        typedef EdgeMapI::ValueType AdjFaces;
        EdgeMapI m_edge_map;
};
