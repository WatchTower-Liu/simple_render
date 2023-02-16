#include "render_triangle.h"
#include <vector>

std::vector<int> renderTriangle::getBBox(std::vector<Vec3D<float>> triangle) {
    CHECKTRIANGLE(triangle);
    std::vector<int> BBox;
    float minX = std::min(std::min(triangle[0][0], triangle[1][0]), triangle[2][0]);
    float minY = std::min(std::min(triangle[0][1], triangle[1][1]), triangle[2][1]);
    float maxX = std::max(std::max(triangle[0][0], triangle[1][0]), triangle[2][0]);
    float maxY = std::max(std::max(triangle[0][1], triangle[1][1]), triangle[2][1]);
    BBox.push_back(static_cast<int>(minX - 1)); BBox.push_back(static_cast<int>(minY - 1));
    BBox.push_back(static_cast<int>(maxX + 1)); BBox.push_back(static_cast<int>(maxY + 1));

    return BBox;
}

void renderTriangle::render_triangle(cv::Mat img, std::vector<Vec3D<float>> triangle) {
    CHECKTRIANGLE(triangle);
    std::vector<int> BBox = getBBox(triangle);

    int randColor = rand();
    unsigned char C = static_cast<unsigned char>(randColor%255);
    for (int rowIndex = BBox[1] >= 0 ? BBox[1] : 0; rowIndex <= BBox[3] && rowIndex < img.rows; rowIndex++) {
        for (int colIndex = BBox[0] >= 0 ? BBox[0] : 0; colIndex <= BBox[2] && colIndex < img.cols; colIndex++) {
            Vec3D<float> P(static_cast<float>(colIndex), static_cast<float>(rowIndex), 0);
            Vec3D<float> bc_coord = barycentric(triangle, P);
            if (bc_coord[0]>=0 && bc_coord[1]>=0 && bc_coord[2]>=0) {
                
                img.at<cv::Vec3b>(rowIndex, colIndex) = {C, C, C};
            } 
        }
    }
}

void renderTriangle::render_triangle(cv::Mat img, std::vector<Vec3D<float>> triangle, cv::Mat texture) {
    CHECKTRIANGLE(triangle);
    std::vector<int> BBox = getBBox(triangle);

    for (int rowIndex = BBox[1] >= 0 ? BBox[1] : 0; rowIndex <= BBox[3] && rowIndex < img.rows; rowIndex++) {
        for (int colIndex = BBox[0] >= 0 ? BBox[0] : 0; colIndex <= BBox[2] && colIndex < img.cols; colIndex++) {
            Vec3D<float> P(static_cast<float>(colIndex), static_cast<float>(rowIndex), 0);
            Vec3D<float> bc_coord = barycentric(triangle, P);
            if (bc_coord[0]>=0 && bc_coord[1]>=0 && bc_coord[2]>=0) {
                img.at<cv::Vec3b>(rowIndex, colIndex) = {0, 255, 0};
            } 
        }
    }
}

void renderTriangle::render_triangle(cv::Mat img, cv::Mat depth, std::vector<Vec3D<float>> triangle, float lightColor) {
    CHECKTRIANGLE(triangle);

    std::vector<int> BBox = getBBox(triangle);

    for (int rowIndex = BBox[1] >= 0 ? BBox[1] : 0; rowIndex <= BBox[3] && rowIndex < img.rows; rowIndex++) {
        for (int colIndex = BBox[0] >= 0 ? BBox[0] : 0; colIndex <= BBox[2] && colIndex < img.cols; colIndex++) {
            Vec3D<float> P(static_cast<float>(colIndex), static_cast<float>(rowIndex), 0);
            Vec3D<float> bc_coord = barycentric(triangle, P);
            if (bc_coord[0]>=0 && bc_coord[1]>=0 && bc_coord[2]>=0) {
                float z = bc_coord[0] * triangle[0][2] + bc_coord[1] * triangle[1][2] + bc_coord[2] * triangle[2][2];
                float D = depth.at<float>(rowIndex, colIndex);
                if (z < D) {
                    depth.at<float>(rowIndex, colIndex) = z;
                    if (lightColor > 0)
                        img.at<cv::Vec3b>(rowIndex, colIndex) = {unsigned char(lightColor), unsigned char(lightColor), unsigned char(lightColor)};
                    // img.at<cv::Vec3b>(rowIndex, colIndex) = {128,128,128};
                }
            } 
        }
    }
}

Vec3D<float> renderTriangle::barycentric(std::vector<Vec3D<float>> triangle , Vec3D<float> P) {
    Vec3D<float> U = Vec3D<float>(triangle[1][0] - triangle[0][0], 
                                  triangle[2][0] - triangle[0][0], 
                                  triangle[0][0] - P[0]);
    U = U.cross(Vec3D<float>(triangle[1][1] - triangle[0][1], 
                             triangle[2][1] - triangle[0][1], 
                             triangle[0][1] - P[1]));
    if (abs(U[2]) < 1)return Vec3D<float>( - 1., 1., 1.);
    return Vec3D<float>(1 - (U[0] + U[1]) / U[2], U[0] / U[2], U[1] / U[2]);
}
