#include <iostream>
#include "Core.h"

int main() {
    //Перегружены операторы сложения матриц, умножения матриц, умножения матрицы на число и наоборот
/*    vector<Triplet<double>> create;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            double k;
            cin>>k;
            create.push_back({i, j, k});
        }
    }*/
    vector<Triplet<double>> in = {{0, 0, 4},
                          {0, 1, 2},
                          {0, 2, 6},
                          {1, 0, 2},
                          {1, 1, 10},
                          {1, 2, 9},
                          {2, 0, 6},
                          {2, 1, 9},
                          {2, 2, 14}};
    DOK<double> A = DOK<double>(in, 3, 3);
    vector<double> res = A.gradientDownShifting({0, 1, 0}, {1, 2, 3});
    for(auto i: res){
        cout<<i<<endl;
    }
    /*DOK<double> k = DOK<double>(create, 5, 5);
    cout<<k<<endl;
    map<int, double> u = k.Polinome();
    map<int, double> g = {{20, 1}, {13, 100}, {8, -71}, {0, 0.25}};
    for(auto i = g.begin(); i!=g.end(); i++){
        cout<<i->second<<"x^"<<i->first<<" ";
    }

    cout<<k*k;
    cout<<k*10<<'\n'<<10.*k;
    vector<map<int, double>> D = Solver::Derivatives(g);
    for(auto &i : D){
        for(auto &j : i){
            cout<<j.second<<"x^"<<j.first<<" ";
        }
        cout<<endl;
    }
    map<int, double> P = Solver::Division(*D.begin(), *(D.begin()+1));
    for(auto i : P){
        cout<<i.second<<"x^"<<i.first<<" ";
    }
    cout<<endl;
    map<int, double> S = Solver::Derivative(g);
    for(auto &j : S){
        cout<<j.second<<"x^"<<j.first<<" ";
    }
    cout<<endl<<endl;
    vector<map<int, double>> S_CH = Solver::ShturmChain(g, Solver::Derivative(g));
    for(auto &i : S_CH){
        for(auto &j : i){
            cout<<j.second<<"x^"<<j.first<<" ";
        }
        cout<<endl;
    }
    pair<double, double> C = Solver::Lagrange(g);
    cout<<endl<<C.first<<" "<<C.second<<endl;
    cout<<Solver::baseNumber(S_CH, C.first, C.second);
    cout<<endl;
    vector<double> Bases = Solver::oneRadicalSegments(S_CH, C);
    for(auto &i : Bases){
        cout<<i<<endl;
    }*/

    return 0;
}
