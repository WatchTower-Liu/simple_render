#include "light.h"

std::vector<float> light::faceLight(std::vector<std::vector<Vec3D<float>>> faces) {
    int faceNum = faces.size();
    std::vector<float> faceLight;
    for (int faceIndex = 0; faceIndex < faceNum; faceIndex++) {
        Vec3D<float> V1 = (faces[faceIndex][1] - faces[faceIndex][0]);
        Vec3D<float> V2 = (faces[faceIndex][2] - faces[faceIndex][0]);
        Vec3D<float> N = V1.cross(V2);
        N = N.normal();
        float L = N.dot(__lightDir);
        L = L*200;
        faceLight.push_back(L);
    }
    return faceLight;
}