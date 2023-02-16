#include "renderModel.h"
#include "render_triangle.h"

void renderModel::render(cv::Mat img) {
    renderTriangle triRender;
    Vec3D<float> center(img.cols/2, img.rows/2, 0);
    for (int triIndex = 0; triIndex < __triangles.size(); triIndex++) {
        std::vector<Vec3D<float>> centerTriangle = pushToCenter(__triangles[triIndex], center);
        triRender.render_triangle(img, centerTriangle);
    }
}

void renderModel::render(cv::Mat img, cv::Mat depth, std::vector<float> light) {
    renderTriangle triRender;
    Vec3D<float> center(img.cols/2, img.rows/2, 0);
    for (int triIndex = 0; triIndex < __triangles.size(); triIndex++) {
        std::vector<Vec3D<float>> centerTriangle = pushToCenter(__triangles[triIndex], center);
        triRender.render_triangle(img, depth, centerTriangle, light[triIndex]);
    }
}

std::vector<Vec3D<float>> renderModel::pushToCenter(std::vector<Vec3D<float>> triangle, Vec3D<float> center) {
    std::vector<Vec3D<float>> centerTriangle;
    for (int triangleIndex = 0; triangleIndex < triangle.size(); triangleIndex++) {
        centerTriangle.push_back(triangle[triangleIndex] + center);
    }
    return centerTriangle;
}