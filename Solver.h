//
// Created by d-qql on 09.10.2020.
//

#ifndef SPARSEMATRICES_SOLVER_H
#define SPARSEMATRICES_SOLVER_H
#include <map>
#include <cmath>
#include <vector>
struct Trip{
    std::pair<double, double> Segment;
    int count;
};
using namespace std;
class Solver {
public:
    static vector<double> oneRadicalSegments(vector<map<int, double>> ShturmChain, pair<double, double> Segment);
    //static vector<double> Solution(map<int, double> Poli);
    static int baseNumber(vector<map<int, double>> ShturmChain, double a, double b);
    static pair<double, double> Lagrange(map<int, double> Poli);
    static vector<map<int, double>> ShturmChain(const map<int, double> &Poli, const map<int, double> &Derivative);
    static map<int, double> Derivative(map<int, double> Poli);
    static vector<map<int, double>> Derivatives(map<int, double> Poli);
    int Budan_Fourier(vector<map<int, double>> Derivatives, double a, double b);
    static map<int, double> Division(map<int, double> up, map<int, double> down);
};


#endif //SPARSEMATRICES_SOLVER_H
