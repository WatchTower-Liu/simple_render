#ifndef _TRIANGLEPROCESS_H_
#define _TRIANGLEPROCESS_H_

#include <vector>
#include "dataType.hpp"

class triangleProcess{
public:
    triangleProcess(std::vector<Vec3D<float>> vertexs, std::vector<Vec3D<int>> faces) : __Overtexs(vertexs), __vertexs(vertexs), __faces(faces) {}

    void look_at(Vec3D<float> eye, Vec3D<float> at = Vec3D<float>(0, 0, 0), Vec3D<float> up = Vec3D<float>(0, -1, 0));

    std::vector<std::vector<Vec3D<float>>> getTriangle();
private:
    std::vector<Vec3D<float>> __vertexs;
    std::vector<Vec3D<float>> __Overtexs;
    std::vector<Vec3D<int>> __faces;

};

#endif