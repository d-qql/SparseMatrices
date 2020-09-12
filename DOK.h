//
// Created by d-qql on 11.09.2020.
//

#ifndef SPARSEMATRICES_DOK_H
#define SPARSEMATRICES_DOK_H

#include <map>
#include <iostream>
#include <vector>
using namespace std;
struct Triplet{
    int i;
    int j;
    double b;
};
class DOK {
private:
    /*
     * Dictionary of Keys, pair<int, int> is coordinates of non-zero elements,
     * next int is value
     */
    map<pair<int, int>, double> dict;
    int size_n;
    int size_m;
    int count;

public:
    void fill(vector<Triplet> &matrix);
    void insert(Triplet &Element);
    void resize(int n, int m);
    DOK(vector<Triplet> &matrix, int n, int m);
    DOK(int n, int m);
    const DOK operator+(const DOK &matrix) const;
    const DOK operator-(const DOK &matrix) const;
    const DOK operator*(const DOK &matrix) const;
    const DOK operator*(double k) const;
    void print() const;
};
void operator+=(DOK& left, const DOK& right);
void operator-=(DOK& left, const DOK& right);
const DOK operator*(double k, const DOK &matrix);
void operator*=(DOK& left, const DOK& right);
void operator*=(DOK& left, double k);
ostream& operator<<(ostream &os, const DOK &matrix);

#endif //SPARSEMATRICES_DOK_H
