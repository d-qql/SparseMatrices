#ifndef SPARSEMATRICES_DOK_H
#define SPARSEMATRICES_DOK_H
#include <map>
#include <iostream>
#include <vector>
#include <iterator>
#include "Triplet.h"
#include "Solver.h"
using namespace std;
template<typename T>
class DOK{
private:
    /*
     * Dictionary of Keys, pair<int, int> is coordinates of non-zero elements,
     * next int is value
     */

    int size_n;
    int size_m;
    // int count;
public:
    map<pair<int, int>, T> dict;
    DOK(vector<Triplet<T>> &matrix, int n, int m);
    DOK(int n, int m);
    ~DOK(){};
    void fill(vector<Triplet<T>> &matrix);
    void insert(const Triplet<T> &Element);
    void resize(int n, int m);
    void print() const;
    pair<int, int> getSize() const;
    vector<T> gradientDownShifting(vector<T> x, vector<T> b);
    T norm(const vector<T> x);
    map<int, double> Polinome();
    //vector<map<int, double>> Derivatives(map<int, double> Poli);
    DOK<T>& operator+=(const DOK<T> &matrix);
    const DOK<T> operator+(const DOK<T>& matrix) const;
    DOK<T>& operator-=(const DOK<T>& matrix);
    const DOK<T> operator-(const DOK<T> &matrix) const;
    DOK<T>& operator*=(const DOK<T> &matrix);
    const DOK<T> operator*(const DOK<T>& matrix) const;
    DOK<T>& operator*=(T& k);
    const DOK<T> operator*(T& k) const;
    DOK<T>& operator*=(const T& k);
    const DOK<T> operator*(const T& k) const;
    T& operator()(int row, int col);
    const T& operator()(int row, int col) const;


};

template<typename T>
vector<T> operator*(const DOK<T> &matrix, const vector<T> &x){
    vector<T> result;
    for(int i = 0; i < x.size(); i++){
        T temp = 0;
        for(int j = 0; j < x.size(); j++){
            if(matrix.dict.find({i, j})!= matrix.dict.end()){
                temp+=matrix.dict.find({i, j})->second*x[j];
            }
        }
        result.push_back(temp);
    }
    return move(result);
}

template<typename T>
T operator*(const vector<T> &x, const vector<T> &b) {
    T result = 0;
    for(int i = 0; i < x.size(); i++){
        result+=x[i]*b[i];
    }
}

template<typename T>
const vector<T> operator*(const vector<T> &x, const DOK<T> &matrix) {
    vector<T> result;
    for(int i = 0; i < x.size(); i++){
        T temp = 0;
        for(int j = 0; j < x.size(); j++){
            if(matrix.dict.find({i, j})!= matrix.dict.end()){
                temp+=matrix.dict.find({j, i})->second*x[j];
            }
        }
        result.push_back(temp);
    }
    return move(result);
}

template<typename  T>
const DOK<T> operator*(T& k, const DOK<T> &matrix){
    return matrix*k;
}
template<typename  T>
const DOK<T> operator*(const T& k, const DOK<T> &matrix){
    return matrix*k;
}

template<typename T>
vector<T>& operator*=(const DOK<T> &matrix, const vector<T> &x){
    return matrix*x;
}


template<typename T>
vector<T> operator*(const vector<T> &x, T k){
    vector<T> result = x;
    for(int i = 0; i<x.size(); i++){
        result[i]*=k;
    }
    return result;
}
template<typename T>
vector<T> operator*(T k, const vector<T> &x) {
    return x*k;
}

template<typename T>
vector<T> operator-(const vector<T> &x, const vector<T> &b){
    vector<T> result;
    for(int i = 0; i< x.size(); i++){
        result.push_back(x[i]-b[i]);
    }
    return result;
}

template<typename  T>
ostream& operator<<(ostream &os, const DOK<T> &matrix){
    matrix.DOK<T>::print();
    return os;
}


#endif //SPARSEMATRICES_DOK_H