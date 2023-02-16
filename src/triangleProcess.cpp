#include "triangleProcess.hpp"

std::vector<std::vector<Vec3D<float>>> triangleProcess::getTriangle() {
    std::vector<std::vector<Vec3D<float>>> triangles;
    // Vec2D<float> triangle; 
    for (int faceIndex = 0; faceIndex < __faces.size(); faceIndex++) {
        std::vector<Vec3D<float>> faceVertex;
        faceVertex.push_back(Vec3D<float>(__vertexs[__faces[faceIndex][0]][0], __vertexs[__faces[faceIndex][0]][1], __vertexs[__faces[faceIndex][0]][2]));
        faceVertex.push_back(Vec3D<float>(__vertexs[__faces[faceIndex][1]][0], __vertexs[__faces[faceIndex][1]][1], __vertexs[__faces[faceIndex][1]][2]));
        faceVertex.push_back(Vec3D<float>(__vertexs[__faces[faceIndex][2]][0], __vertexs[__faces[faceIndex][2]][1], __vertexs[__faces[faceIndex][2]][2]));

        triangles.push_back(faceVertex);
    }
    return triangles;
}

void triangleProcess::look_at(Vec3D<float> eye, Vec3D<float> at, Vec3D<float> up) {
    Vec3D<float> Z = (at - eye).normal();
    Vec3D<float> X = (up.cross(Z)).normal();
    Vec3D<float> Y = (Z.cross(X)).normal();

    for (int vertexIndex = 0; vertexIndex < __vertexs.size(); vertexIndex++) {
        __vertexs[vertexIndex] = Vec3D<float>((__Overtexs[vertexIndex] - eye)[0],
                                              (__Overtexs[vertexIndex] - eye)[1],
                                              (__Overtexs[vertexIndex] - eye)[2]);
        Vec3D<float> newVertex(__vertexs[vertexIndex].dot(X),
                               __vertexs[vertexIndex].dot(Y), 
                               __vertexs[vertexIndex].dot(Z));
        __vertexs[vertexIndex] = newVertex;
    }
}

