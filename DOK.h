#ifndef SPARSEMATRICES_DOK_H
#define SPARSEMATRICES_DOK_H
#include <map>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;
template<typename T>
struct Triplet{
    int i;
    int j;
    T b;
};
template<typename T>
class DOK{
private:
    /*
     * Dictionary of Keys, pair<int, int> is coordinates of non-zero elements,
     * next int is value
     */
    map<pair<int, int>, T> dict;
    int size_n;
    int size_m;
    // int count;
public:
    DOK(vector<Triplet<T>> &matrix, int n, int m);
    DOK(int n, int m);
    ~DOK(){};
    void fill(vector<Triplet<T>> &matrix);
    void insert(const Triplet<T> &Element);
    void resize(int n, int m);
    void print() const;
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


template<typename  T>
const DOK<T> operator*(T& k, const DOK<T> &matrix){
    return matrix*k;
}
template<typename  T>
const DOK<T> operator*(const T& k, const DOK<T> &matrix){
    return matrix*k;
}

template<typename  T>
ostream& operator<<(ostream &os, const DOK<T> &matrix){
    matrix.DOK<T>::print();
    return os;
}

#endif //SPARSEMATRICES_DOK_H