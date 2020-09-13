//
// Created by d-qql on 13.09.2020.
//

#ifndef SPARSEMATRICES_MATRICES_H
#define SPARSEMATRICES_MATRICES_H
#include <vector>
using namespace std;
template<typename T>
struct Triplet{
    int i;
    int j;
    T b;
};
template<typename T>
class Matrices
{
public:
    // Виртуальный деструктор
    virtual ~Matrices() = 0;

    /*
     * Виртуальные методы, должны быть реализованы вашим контейнером
     */

    virtual void fill(vector<Triplet<T>> &matrix) = 0;
    virtual const Matrices<T> operator+(const Matrices<T> &matrix) const = 0;
    virtual const Matrices<T> operator-(const Matrices<T> &matrix) const = 0;
    virtual const Matrices<T> operator*(const Matrices<T> &matrix) const = 0;
    virtual const Matrices<T> operator*(T& k) const = 0;
    virtual const Matrices<T> operator*(const T& k) const = 0;
    virtual T& operator()(int row, int col) = 0;
    virtual const T& operator()(int row, int col) const = 0;
};
#endif //SPARSEMATRICES_MATRICES_H
