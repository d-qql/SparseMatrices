//
// Created by d-qql on 11.09.2020.
//

#include "DOK.h"
template<typename  T>
DOK<T>::DOK(int n, int m){
    this->resize(n, m);
}
template<typename  T>
DOK<T>::DOK(vector<Triplet<T>> &matrix, int n, int m) {
    //cout<<"Input height and weight of matrix: "<<endl;
    //cin>>n>>m;
    this->resize(n, m);
    this->fill(matrix);
}
template<typename  T>
void DOK<T>::fill(vector<Triplet<T>> &matrix) {
    //this->count=matrix.size();
    //cout<<"Input your coordinates with value in format \"i j val\" "<<endl;
    for(int k = 0; k < matrix.size(); k++){
        this->insert(matrix[k]);
    }
}
/*
 * Inserts element with coordinates i, j and value b in matrix
 */
template<typename  T>
void DOK<T>::insert(const Triplet<T> &Element){
    try {
        if(Element.i > this->size_n || Element.j > size_m) throw 1;
        pair<int, int> coordinates = {Element.i, Element.j};
        this->dict.insert(make_pair(coordinates, Element.b));
    }
    catch (int a) {
        cout<<"Inserting coordinates {"<<Element.i<<", "<<Element.j<<"} out of range. "<<endl;
    }
}
template<typename  T>
void DOK<T>::resize(int n, int m){
    this->size_n=n;
    this->size_m=m;
}
template<typename  T>
const DOK<T> DOK<T>::operator+(const DOK<T> &matrix) const{
    try{
        if(this->size_n != matrix.size_n || this->size_m != matrix.size_m) throw 1;
        DOK<T> M = *this;
        for(auto j: matrix.dict){
            if(M.dict.find(j.first)!=M.dict.cend()) {
                M.dict[j.first] += j.second;
            }else{
                M.dict.insert({j.first, j.second});
                //M.count++;
            }
        }
        return M;
    }
    catch (int a) {
        cout<<"Sizes of Matrices are different."<<endl;
    }
}
template<typename  T>
const DOK<T> DOK<T>::operator-(const DOK<T> &matrix) const{
    return -1.*matrix+*this;
}
template<typename  T>
 void DOK<T>::print() const {
    cout<<endl;
    for(int i = 1; i <= this->size_n; i++){
        for(int j = 1; j <= this->size_m; j++){
            if(this->dict.find({i, j})!= this->dict.cend()) cout<<this->dict.find(make_pair(i, j))->second<<" "; else cout<<0<<" ";
        }
        cout<<endl;
    }
}



template<typename  T>
const DOK<T> DOK<T>::operator*(const DOK<T> &matrix) const{
    try {
        if(this->size_m != matrix.size_n) throw 1;
        DOK<T> M = DOK(this->size_n, matrix.size_m);
        for (int i = 1; i <= this->size_n; i++) {
            for (int j = 1; j <= matrix.size_m; j++) {
                T a=0;
                for(int k = 1; k<=this->size_m; k++){
                    if(this->dict.find({i,k}) != this->dict.cend() && matrix.dict.find({k, j})!=matrix.dict.cend()){
                        a+=this->dict.find({i,k})->second*matrix.dict.find({k,j})->second;
                        //cout<<a<<endl;
                    }
                }
                Triplet<T> m = {i, j, a};
                M.insert(m);
            }
        }
        return M;
    }
    catch (int a) {
        cout<<"Wrong sizes of matrices to multiplication"<<endl;
    }
}

template<typename  T>
const DOK<T> DOK<T>::operator*(T& k) const{
    DOK<T> M = *this;
    for(auto i: M.dict){
        M.dict[i.first]*=k;
    }
    return M;
}
template<typename  T>
const DOK<T> DOK<T>::operator*(const T& k) const{
    DOK<T> M = *this;
    for(auto i: M.dict){
        M.dict[i.first]*=k;
    }
    return M;
}

template<typename  T>
 T& DOK<T>::operator()(int row, int col){
    return this->dict.find({row, col})->second;
}
template<typename  T>
const T& DOK<T>::operator()(int row, int col) const{
    return this->dict.find({row, col})->second;
}

template class Matrices<double>;