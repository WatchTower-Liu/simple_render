#include "render_triangle.h"
#include "load_model.hpp"
#include "renderModel.h"
#include "triangleProcess.hpp"
#include "light.h"

#include <opencv2/opencv.hpp>
#include <vector>

void mouCALLB(int event,    
             int x, int y,  
             int flags,     
             void *userdata) {
    float* userdataf = static_cast<float*>(userdata);
    if (event == cv::EVENT_LBUTTONDOWN) {
        userdataf[0] = x; userdataf[1] = y;
        userdataf[4] = 10;
    }
    if (event == cv::EVENT_LBUTTONUP) {
        userdataf[0] = x; userdataf[1] = y;
        userdataf[4] = -10;
    }
    if (event == cv::EVENT_MOUSEMOVE && userdataf[4] == 10) {
        userdataf[2] += (userdataf[0] - x)*0.001; userdataf[3] += (y - userdataf[1])*0.001;
    }

}


int main(){
    loadModel LM("../../assets/test5.obj");
    std::tuple<std::vector<Vec3D<float>>, std::vector<Vec3D<int>>> modelData = LM.load();
    std::vector<Vec3D<float>> Vertexs = std::get<0>(modelData);
    std::vector<Vec3D<int>> Faces = std::get<1>(modelData);
    triangleProcess TP(Vertexs, Faces);
    cv::namedWindow("1212", cv::WINDOW_NORMAL);
    float R[5] = {0, 0, 0, 0, 0};
    cv::setMouseCallback("1212", mouCALLB, R); 
    while (1) {
        TP.look_at(Vec3D<float>(R[2], R[3], 1), Vec3D<float>(0, 0, -10));
        std::cout << R[0] << " " << R[1] << " " << R[2] << " " << R[3] << std::endl;
        std::vector<std::vector<Vec3D<float>>> triangles = TP.getTriangle();

        light faceLight(Vec3D<float>{0, 0, -1});
        std::vector<float> lights = faceLight.faceLight(triangles);
        // std::cout << lights.size() <<std::endl;
        // std::cout << triangles.size() <<std::endl;
        cv::Mat img(800, 800, CV_8UC3, cv::Scalar(0,0,0)); 
        cv::Mat depath(800, 800, CV_32FC1, std::numeric_limits<float>::max()); 
        renderModel RM(triangles);
        RM.render(img, depath, lights);
        
        cv::imshow("1212", img);
        cv::waitKey(20);
    }

    return 0;
}
