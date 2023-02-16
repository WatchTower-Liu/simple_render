#include "load_model.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.hpp"

#include <iostream>

std::tuple<std::vector<Vec3D<float>>, std::vector<Vec3D<int>>> loadModel::load() {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, _fileName.c_str());

    if (!warn.empty()) {
        std::cout << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    if (!ret) {
        throw "cont load anything!!!";
    }
    std::vector<Vec3D<float>> vertexs;
    std::vector<Vec3D<int>> faces;
    // Loop over shapes

    for (size_t vertexIndex = 0; vertexIndex < attrib.vertices.size() / 3; vertexIndex++){
        tinyobj::real_t vx = attrib.vertices[3*vertexIndex+0]*100;
        tinyobj::real_t vy = attrib.vertices[3*vertexIndex+1]*100;
        tinyobj::real_t vz = attrib.vertices[3*vertexIndex+2]*100;
        Vec3D<float> vertex(vx, vy, vz);
        vertexs.push_back(vertex);
    }

    for (size_t s = 0; s < shapes.size(); s++) {
    // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
            if (fv != 3){
                std::cout << "face error!! " << std::endl;
                continue;
            }
            tinyobj::index_t face1 = shapes[s].mesh.indices[index_offset + 0];
            tinyobj::index_t face2 = shapes[s].mesh.indices[index_offset + 1];
            tinyobj::index_t face3 = shapes[s].mesh.indices[index_offset + 2];
            Vec3D<int> face(face1.vertex_index, face2.vertex_index, face3.vertex_index);
            faces.push_back(face);
               
            index_offset += fv;
        }
    }
    return {vertexs, faces};
}

