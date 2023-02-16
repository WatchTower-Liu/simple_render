#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "dataType.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

class light{
public:
    light(Vec3D<float> lightDir) : __lightDir(lightDir){};
    std::vector<float> faceLight(std::vector<std::vector<Vec3D<float>>> faces);

private:
    Vec3D<float> __lightDir;

};

#endif
