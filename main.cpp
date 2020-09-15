#include <iostream>
#include "DOK.h"
int main() {
    //Перегружены операторы сложения матриц, умножения матриц, умножения матрицы на число и наоборот
    vector<Triplet<double>> in = {{1, 1, 1},
                          {1, 2, 2},
                          {1, 3, 3},
                          {2, 1, 4},
                          {2, 2, 5},
                          {2, 3, 6},
                          {3, 1, 7},
                          {3, 2, 8},
                          {3, 3, 9}};
    Matrices<double>* k = new DOK<double>(in, 3, 3);
    cout<<k;
    /*Matrices<double> p = DOK<double>(in, 3, 3);
    cout<<(*p)*(*k);
    k->print();
    p.print();
    p=p+k;
    double m = 2;
    p.print();
    cout<<p+k;
    cout<<p*2.<<2.*p;
    p*=k;
    p*=m;
    cout<<p;
    cout<<p*m;
    k*=20.;
    cout<<k;
    k+=p;
    cout<<k;

    cout<<p(1, 3);
   p(1, 3) = 2;
    cout<<p(1, 3);
*/
    return 0;
}
