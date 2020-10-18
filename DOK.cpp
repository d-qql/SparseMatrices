//
// Created by d-qql on 11.09.2020.
//

#include "DOK.h"
double tolerance = 1e-8;
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
void DOK<T>::print() const {
    cout<<endl;
    for(int i = 0; i < this->size_n; i++){
        for(int j = 0; j < this->size_m; j++){
            if(this->dict.find({i, j})!= this->dict.cend()) cout<<this->dict.find(make_pair(i, j))->second<<" "; else cout<<0<<" ";
        }
        cout<<endl;
    }
}

template<typename T>
pair<int, int> DOK<T>::getSize() const{
    return {size_n, size_m};
}
template<typename T>
T DOK<T>::norm(const vector<T> x){
    T result = 0;
    for(int i = 0; i < x.size(); i++){
        result+=pow(x[i],2);
    }
    return sqrt(result);
}

template<typename T>
vector<T> DOK<T>::gradientDownShifting(vector<T> X, vector<T> b){
    DOK<T> A = *this;

    while (norm(A*X - b) >= tolerance){
        vector<T> r = A*X-b;
        X = X - (r*r/(r*A*r))*r;
    }
    return X;
}

template<typename T>
map<int, double> DOK<T>::Polinome(){
    map<int, double> R;
    int n = this->getSize().first;
    cout<<n<<endl;
    DOK<T> I = DOK<T>(n, n);
    DOK<T> M = DOK<T>(n, n);
    for(int i = 0; i < n; i++){
        I.insert({i, i, 1});
    }
    cout<<I<<endl;
    double c = 1;
    R.insert({n, c});
    for(int i = 0; i < n; i++){
        M = *this*M+I*c;
        DOK<T> AM = *this*M;
        double tr = 0;
        for(int j = 0; j < n; j++){
            tr+=AM(j, j);
        }
        c = -tr/(i+1);
        if(abs(c)>tolerance) R.insert({n-i-1, c});
    }
    return R;
}



template<typename  T>
DOK<T>& DOK<T>::operator+=(const DOK<T> &matrix){
    try{
        if(this->size_n != matrix.size_n || this->size_m != matrix.size_m) throw 1;
        for(auto j: matrix.dict){
            if(this->dict.find(j.first)!=this->dict.cend()) {
                this->dict[j.first] += j.second;
            }else{
                this->dict.insert({j.first, j.second});
                //M.count++;
            }
        }
        return *this;
    }
    catch (int a) {
        cout<<"Sizes of Matrices are different."<<endl;
    }
}
template<typename T>
const DOK<T> DOK<T>::operator+(const DOK<T>& matrix) const{
    DOK<T> t = *this;
    return t+=matrix;
}

template<typename T>
DOK<T>& DOK<T>::operator-=(const DOK<T>& matrix){
    try{
        if(this->size_n != matrix.size_n || this->size_m != matrix.size_m) throw 1;
        for(auto j: matrix.dict){
            if(this->dict.find(j.first)!=this->dict.cend()) {
                this->dict[j.first] -= j.second;
            }else{
                this->dict.insert({j.first, -j.second});
                //M.count++;
            }
        }
        return *this;
    }
    catch (int a) {
        cout<<"Sizes of Matrices are different."<<endl;
    }
}

template<typename  T>
const DOK<T> DOK<T>::operator-(const DOK<T> &matrix) const{
    DOK<T> t = *this;
    return t-=matrix;
}

template<typename  T>
DOK<T>& DOK<T>::operator*=(const DOK<T> &matrix){
    try {
        if(this->size_m != matrix.size_n) throw 1;
        DOK<T> M = DOK(this->size_n, matrix.size_m);
        for (int i = 0; i < this->size_n; i++) {
            for (int j = 0; j < matrix.size_m; j++) {
                T a=0;
                for(int k = 0; k<this->size_m; k++){
                    if(this->dict.find({i,k}) != this->dict.cend() && matrix.dict.find({k, j})!=matrix.dict.cend()){
                        a+=this->dict.find({i,k})->second*matrix.dict.find({k,j})->second;
                        //cout<<a<<endl;
                    }
                }
                Triplet<T> m = {i, j, a};
                M.insert(m);
            }
        }
        *this=M;
        return *this;
    }
    catch (int a) {
        cout<<"Wrong sizes of matrices to multiplication"<<endl;
    }
}

template<typename T>
const DOK<T> DOK<T>::operator*(const DOK<T>& matrix) const{
    DOK<T> t = *this;
    return t*=matrix;
}


template<typename T>
DOK<T>& DOK<T>::operator*=(T& k){
    for(auto i: this->dict){
        this->dict[i.first]*=k;
    }
    return *this;
}
template<typename  T>
const DOK<T> DOK<T>::operator*(T& k) const{
    DOK<T> t = *this;
    return t*=k;
}

template<typename T>
DOK<T>& DOK<T>::operator*=(const T& k){
    for(auto i: this->dict){
        this->dict[i.first]*=k;
    }
    return *this;
}
template<typename  T>
const DOK<T> DOK<T>::operator*(const T& k) const{
    DOK<T> t = *this;
    return t*=k;
}

template<typename  T>
T& DOK<T>::operator()(int row, int col){
    return this->dict.find({row, col})->second;
}
template<typename  T>
const T& DOK<T>::operator()(int row, int col) const{
    return this->dict.find({row, col})->second;
}

template class DOK<double>;
//template class DOK<int>;