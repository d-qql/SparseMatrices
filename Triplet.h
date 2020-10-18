//
// Created by d-qql on 19.09.2020.
//

#ifndef SPARSEMATRICES_TRIPLET_H
#define SPARSEMATRICES_TRIPLET_H
template<typename T>
struct Triplet{
    int i;
    int j;
    T b;
};
template struct Triplet<double>;
#endif //SPARSEMATRICES_TRIPLET_H
