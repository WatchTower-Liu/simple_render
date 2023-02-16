#ifndef _RENDER_TRIANGLE_H_
#define _RENDER_TRIANGLE_H_

#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>

#include "dataType.hpp"

#define CHECKTRIANGLE(triangle) if(triangle.size() != 3) throw "triangle vertex error!!" 

class renderTriangle {
public:
    renderTriangle(){}
    void render_triangle(cv::Mat img, std::vector<Vec3D<float>> triangle);
    void render_triangle(cv::Mat img, std::vector<Vec3D<float>> triangle, cv::Mat texture);
    void render_triangle(cv::Mat img, cv::Mat depth, std::vector<Vec3D<float>> triangle, float lightColor);

private:
    Vec3D<float> barycentric(std::vector<Vec3D<float>> triangle , Vec3D<float> P);

    std::vector<int> getBBox(std::vector<Vec3D<float>> triangle);
};

#endif