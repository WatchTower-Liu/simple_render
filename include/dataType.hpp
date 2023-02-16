#ifndef _DATATYPE_H_
#define _DATATYPE_H_

#include <initializer_list>
#include <algorithm>
#include <cmath>

template<typename T, typename F, int size>
struct VecND
{
    T data[size];
    VecND(std::initializer_list<T> D){
        int index = 0;
        for (auto DD = D.begin(); DD != D.end(); DD++) {
            data[index] = *DD;
            index++;
        }
    }
    VecND(T* D){
        for (int index = 0; index < size; index++) {
            data[index] = D[index];
        }
    }
    T operator[] (int idx) {
        if (idx >= size)
            throw "index out of range";
        return data[idx];
    }
    F operator - (F other) {
        T newData[size];
        for (int index = 0; index < size; index++)
            newData[index] = data[index] - other[index];

        return static_cast<F>(newData);
    }
    F operator + (F other) {
        T newData[size];
        for (int index = 0; index < size; index++)
            newData[index] = data[index] + other[index];

        return static_cast<F>(newData);
    }
    F operator * (F other) {
        T newData[size];
        for (int index = 0; index < size; index++)
            newData[index] = data[index] * other[index];

        return static_cast<F>(newData);
    }
    F operator / (F other) {
        T newData[size];
        for (int index = 0; index < size; index++)
            newData[index] = data[index] / other[index];

        return static_cast<F>(newData);
    }
    T dot (F other) {
        T result = 0;
        for (int index = 0; index < size; index++)
            result += (data[index] * other[index]);

        return result;
    }
    F normal() {
        T newData[size];
        T NN = 0;
        for (int index = 0; index < size; index++) {
            NN += data[index] * data[index];
        }
        NN = sqrt(NN);
        for (int index = 0; index < size; index++) {
            newData[index] = data[index] / NN;
        }
        return newData;
    }
};

template<typename T>
struct Vec3D : public VecND<T, Vec3D<T>, 3>
{
    Vec3D(T e1, T e2, T e3) : VecND<T, Vec3D<T>, 3>{e1, e2, e3}{}
    Vec3D(std::initializer_list<T> D) : VecND<T, Vec3D<T>, 3>(D){}
    Vec3D(T* D) : VecND<T, Vec3D<T>, 3>(D){}
    //若向量a=(a1,b1,c1)，向量b=(a2,b2,c2)，则a×b=(b1c2-b2c1，c1a2-a1c2，a1b2-a2b1)。
    Vec3D<T> cross(Vec3D<T> other) {
        return Vec3D<T>(VecND<T, Vec3D<T>, 3>::data[1]*other[2] - other[1]*VecND<T, Vec3D<T>, 3>::data[2], 
                          VecND<T, Vec3D<T>, 3>::data[2]*other[0] - VecND<T, Vec3D<T>, 3>::data[0]*other[2], 
                          VecND<T, Vec3D<T>, 3>::data[0]*other[1] - other[0]*VecND<T, Vec3D<T>, 3>::data[1]);
    }
};

template<typename T>
struct Vec2D : public VecND<T, Vec2D<T>, 2>
{
    Vec2D(T e1, T e2) : VecND<T, Vec2D<T>, 2>{e1, e2}{}
    Vec2D(std::initializer_list<T> D) : VecND<T, Vec2D<T>, 2>(D){}
    Vec2D(T* D) : VecND<T, Vec2D<T>, 2>(D){}
    //a(x1，y1)，b(x2，y2)，则a×b＝(x1y2－x2y1) z轴
    T cross(Vec2D<T> other) {
        return VecND<T, Vec2D<T>, 2>::data[0]*other[1] - other[0]*VecND<T, Vec2D<T>, 2>::data[1];
    }
};



#endif
