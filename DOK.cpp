//
// Created by d-qql on 11.09.2020.
//

#include "DOK.h"
DOK::DOK(int n, int m){
    this->resize(n, m);
}
DOK::DOK(vector<Triplet> &matrix, int n, int m) {
    //cout<<"Input height and weight of matrix: "<<endl;
    //cin>>n>>m;
    this->resize(n, m);
    this->fill(matrix);
}

void DOK::fill(vector<Triplet> &matrix) {
    this->count=matrix.size();
    //cout<<"Input your coordinates with value in format \"i j val\" "<<endl;
    for(int k = 0; k < this->count; k++){
        this->insert(matrix[k]);
    }
}
/*
 * Inserts element with coordinates i, j and value b in matrix
 */
void DOK::insert(Triplet &Element){
    try {
        if(Element.i > this->size_n || Element.j > size_m) throw 1;
        pair<int, int> coordinates = {Element.i, Element.j};
        this->dict.insert(make_pair(coordinates, Element.b));
    }
    catch (int a) {
        cout<<"Inserting coordinates {"<<Element.i<<", "<<Element.j<<"} out of range. "<<endl;
    }
}

void DOK::resize(int n, int m){
    this->size_n=n;
    this->size_m=m;
}

const DOK DOK::operator+(const DOK &matrix) const{
    try{
        if(this->size_n != matrix.size_n || this->size_m != matrix.size_m) throw 1;
        DOK M = *this;
        for(auto j: matrix.dict){
            if(M.dict.find(j.first)!=M.dict.cend()) {
                M.dict[j.first] += j.second;
            }else{
                M.dict.insert({j.first, j.second});
                M.count++;
            }
        }
        return M;
    }
    catch (int a) {
        cout<<"Sizes of Matrices are different."<<endl;
    }
}
const DOK DOK::operator-(const DOK &matrix) const{
    return -1*matrix+*this;
}

 void DOK::print() const {
    cout<<endl;
    for(int i = 1; i <= this->size_n; i++){
        for(int j = 1; j <= this->size_m; j++){
            if(this->dict.find({i, j})!= this->dict.cend()) cout<<this->dict.find(make_pair(i, j))->second<<" "; else cout<<0<<" ";
        }
        cout<<endl;
    }
}

const DOK DOK::operator*(const DOK &matrix) const{
    try {
        if(this->size_m != matrix.size_n) throw 1;
        DOK M = DOK(this->size_n, matrix.size_m);
        for (int i = 1; i <= this->size_n; i++) {
            for (int j = 1; j <= matrix.size_m; j++) {
                double a=0;
                for(int k = 1; k<=this->size_m; k++){
                    if(this->dict.find({i,k}) != this->dict.cend() && matrix.dict.find({k, j})!=matrix.dict.cend()){
                        a+=this->dict.find({i,k})->second*matrix.dict.find({k,j})->second;
                        //cout<<a<<endl;
                    }
                }
                Triplet m = {i, j, a};
                M.insert(m);
            }
        }
        return M;
    }
    catch (int a) {
        cout<<"Wrong sizes of matrices to multiplication"<<endl;
    }
}

const DOK DOK::operator*(double k) const{
    DOK M = *this;
    for(auto i: M.dict){
        M.dict[i.first]*=k;
    }
    return M;
}

const DOK operator*(double k, const DOK &matrix){
    return matrix*k;
}
ostream& operator<<(ostream &os, const DOK &matrix){
    matrix.DOK::print();
    return os;
}