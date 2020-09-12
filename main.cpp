#include <iostream>
#include "DOK.h"
int main() {
    //Перегружены операторы сложения матриц, умножения матриц, умножения матрицы на число и наоборот
    vector<Triplet> in = {{1, 1, 1},
                          {1, 2, 2},
                          {1, 3, 3},
                          {2, 1, 4},
                          {2, 2, 5},
                          {2, 3, 6},
                          {3, 1, 7},
                          {3, 2, 8},
                          {3, 3, 9}};
    DOK k = DOK(in, 3, 3);

    DOK p = DOK(in, 3, 3);
    cout<<p*k;
    k.print();
    p.print();
    p=p+k;

    p.print();
    cout<<p+k;
    cout<<p*10<<2*p;
    p*=k;
    cout<<p;
    k*=20;
    cout<<k;
    k+=p;
    cout<<k;


    return 0;
}
