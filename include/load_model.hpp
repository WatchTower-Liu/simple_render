#ifndef _LOAD_MODEL_H_
#define _LOAD_MODEL_H_

#include <string>
#include <vector>
#include <tuple>

#include "dataType.hpp"

class loadModel{
public:
    loadModel(std::string fileName) : _fileName(fileName){}

    std::tuple<std::vector<Vec3D<float>>, std::vector<Vec3D<int>>> load();

private:
    std::string _fileName;

};


#endif