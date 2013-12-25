#include "FaceNormalAttribute.h"

#include <iostream>

#include <Mesh.h>

void FaceNormalAttribute::compute_from_mesh(Mesh& mesh) {
    size_t num_faces = mesh.get_num_faces();
    size_t num_vertex_per_face = mesh.get_vertex_per_face();

    VectorF& normals = m_values;
    normals = VectorF::Zero(num_faces * 3);

    if (num_vertex_per_face == 3) {
        for (size_t i=0; i<num_faces; i++) {
            normals.segment<3>(i*3) = compute_triangle_normal(mesh, i);
        }
    } else {
        std::cerr << "Face with " << num_vertex_per_face << " is not supported yet." << std::endl;
        return;
    }
}

Vector3F FaceNormalAttribute::compute_triangle_normal(Mesh& mesh, size_t i) {
    VectorI face = mesh.get_face(i);
    assert(face.size() == 3);

    Vector3F v[3] = {
        mesh.get_vertex(face[0]),
        mesh.get_vertex(face[1]),
        mesh.get_vertex(face[2])
    };

    Vector3F normal = (v[1] - v[0]).cross(v[2] - v[0]);
    normal.normalize();
    return normal;
}