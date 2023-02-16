#ifndef _RENDERMODEL_H_
#define _RENDERMODEL_H_

#include "dataType.hpp"
#include <vector>
#include <opencv2/opencv.hpp>

class renderModel{
public:
    renderModel(std::vector<std::vector<Vec3D<float>>> triangles): __triangles(triangles) {}
    void render(cv::Mat img, cv::Mat depth, std::vector<float> light);
    void render(cv::Mat img);

private:
    std::vector<std::vector<Vec3D<float>>> __triangles;

    std::vector<Vec3D<float>> pushToCenter(std::vector<Vec3D<float>> triangle, Vec3D<float> center);

};

#endif
