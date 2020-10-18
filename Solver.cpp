//
// Created by d-qql on 09.10.2020.
//

#include "Solver.h"
#include <iostream>
map<int, double> Solver::Division(map<int, double> up, map<int, double> down){
    double c;
    while(up.rbegin()!=up.rend() && up.rbegin()->first >= down.rbegin()->first){
        c = double(up.rbegin()->second)/double(down.rbegin()->second);
        int deltaPOW = up.rbegin()->first-down.rbegin()->first;
        for(auto i:down){
            if(up.find(i.first+deltaPOW) != up.end()){
                up.find(i.first+deltaPOW)->second-=c*i.second;
                if(abs(up.find(i.first+deltaPOW)->second) < 1e-10){
                    up.erase(up.find(i.first+deltaPOW));

                }
            }else{
                up.insert({i.first+deltaPOW, -c*i.second});
            }
        }
    }
    return up;
}

pair<double, double> Solver::Lagrange(map<int, double> Poli){
    double c = Poli.rbegin()->second;
    for(auto i : Poli){
        Poli[i.first]/=c;
        cout<<i.second<<"x^"<<i.first<<" ";
    }
    int k=Poli.rbegin()->first;
    for(auto i = Poli.rbegin(); i != Poli.rend(); i++){
        if(i->second<0){
            k = Poli.rbegin()->first-i->first;
            break;
        }
    }
    double A = 0;
    for(auto i : Poli){
        if(i.second<0&&i.second<A) A = i.second;
    }
    cout<<endl<<k<<" "<<A<<endl;
    double max = 1+pow(-A, 1./k);

    for(auto i : Poli){
        if(i.first % 2 == 1){
            Poli[i.first] *= -1;
        }
    }
    for(auto i : Poli){
        cout<<i.second<<"x^"<<i.first<<" ";
    }
    c = Poli.rbegin()->second;
    cout<<c<<endl;
    for(auto i : Poli){
        Poli[i.first]/=c;
    }
    for(auto i : Poli){
        cout<<i.second<<"x^"<<i.first<<" ";
    }
    k=Poli.rbegin()->first;
    for(auto i = Poli.rbegin(); i != Poli.rend(); i++){
        if(i->second<0){
            k = Poli.rbegin()->first-i->first;
            break;
        }
    }
    A = 0;
    for(auto i : Poli){
        if(i.second<0&&i.second<A) A = i.second;
    }
    cout<<endl<<k<<" "<<A;
    double min = -1 - pow(-A, 1./k);
    cout<<endl<<pow(-A, 1./k)<<endl;
    return {min, max};
}

vector<double> Solver::oneRadicalSegments(vector<map<int, double>> ShturmChain, pair<double, double> Segment) {
    vector<Trip> result;
    vector<double> R;
    result.push_back({Segment, baseNumber(ShturmChain, Segment.first, Segment.second)});
    bool running = true;
    while (running) {
        running = false;
        for (auto &i : result) {
            if (i.count > 1) {
                running = true;
            }
        }
       if(!running) break;
        for (int i = 0; i < result.size(); i++) {
            if (result[i].count > 1) {
                int leftCount = baseNumber(ShturmChain, result[i].Segment.first, (result[i].Segment.first + result[i].Segment.second) / 2);
                int rightCount = baseNumber(ShturmChain, (result[i].Segment.first + result[i].Segment.second) / 2, result[i].Segment.second);
                if(leftCount > 0 || rightCount > 0) {
                    if (leftCount > 0)
                        result.push_back({{result[i].Segment.first, (result[i].Segment.first + result[i].Segment.second) / 2}, leftCount}); //Как же он сука был прав(пуш бэк изменяет итератор)
                    if (rightCount > 0)
                        result.push_back({{(result[i].Segment.first + result[i].Segment.second) / 2, result[i].Segment.second}, rightCount});
                    result.erase(result.begin()+i);
                }
            }
        }
    }
    running = true;
    while(running){
        running = false;
        for(auto &i: result){
            if (i.Segment.second-i.Segment.first>1e-10){
                running = true;
            }
        }
        if(!running) break;
        for(int i = 0; i < result.size(); i++){
            if(result[i].Segment.second-result[i].Segment.first>1e-10){
                //cout<<result[i].Segment.second-result[i].Segment.first<<endl;
                int leftCount = baseNumber(ShturmChain, result[i].Segment.first, (result[i].Segment.first + result[i].Segment.second) / 2);
                int rightCount = baseNumber(ShturmChain, (result[i].Segment.first + result[i].Segment.second) / 2, result[i].Segment.second);
                if(leftCount == 1){
                    result.push_back({{result[i].Segment.first, (result[i].Segment.first + result[i].Segment.second) / 2}, leftCount});
                    result.erase(result.begin()+i);
                    continue;
                }
                if(rightCount == 1){
                    result.push_back({{(result[i].Segment.first + result[i].Segment.second) / 2, result[i].Segment.second}, rightCount});
                    result.erase(result.begin()+i);
                    continue;
                }
            }
        }
    }
    for(auto &i : result){
        R.push_back(i.Segment.first);
    }
    return R;
}

int Solver::baseNumber(vector<map<int, double>> ShturmChain, double a, double b){
    int changeA = 0, changeB = 0;
    double prevA = 0, prevB = 0, currentA = 0, currentB = 0;
    for(auto &i : *ShturmChain.begin()){
        prevA += pow(a, i.first)*i.second;
        prevB += pow(b, i.first)*i.second;
    }
    for(auto &k : ShturmChain){
        for(auto &i : k){
            currentA += pow(a, i.first)*i.second;
            currentB += pow(b, i.first)*i.second;
        }
        if(currentA*prevA<0) changeA++;
        if(currentB*prevB<0) changeB++;
        prevA = currentA;
        prevB = currentB;
        currentA = 0;
        currentB = 0;
    }
    return abs(changeA-changeB);
}

vector<pair<double, double>> oneRadicalSegments(map<int, double> Poli){
    pair<double, double> startSegment = Solver::Lagrange(Poli);

}

vector<map<int, double>> Solver::ShturmChain(const map<int, double> &Poli, const map<int, double> &Derivative){
    vector<map<int, double>> result;
    result.push_back(Poli);
    result.push_back(Derivative);
    for(int i = 2; i < Poli.rbegin()->first; i++){
        if(result[i-1].empty()) break;
        map<int, double> temp = Division(result[i-2], result[i-1]);
        for(auto j : temp){
            temp[j.first]*=-1;
        }
        result.push_back(temp);
    }
    return result;
}

map<int, double> Solver::Derivative(map<int, double> Poli){
    map<int, double> result;
    for(auto & j : Poli){
        if(j.first >= 1) {
            result.insert({j.first - 1, j.second * j.first});
        }
    }
    return result;
}

vector<map<int, double>> Solver::Derivatives(map<int, double> Poli){
    vector<map<int, double>> result;
    result.push_back(Poli);
    for(int i = 1; i <= Poli.rbegin()->first; i++){
        map<int, double> temp;
        for(auto & j : result[i-1]){
            if(j.first >= 1) {
                temp.insert({j.first - 1, j.second * j.first});
            }
        }
        result.push_back(temp);
    }
    return result;
}


int Solver::Budan_Fourier(vector<map<int, double>> Derivatives, double a, double b){
    int chA = 0, chB = 0;
    double poliA_prev = 0, poliB_prev = 0;
    for(auto j : *Derivatives.begin()) {
        poliA_prev += j.second * pow(a, j.first);
        poliB_prev += j.second * pow(b, j.first);
    }
    for(auto i = next(Derivatives.begin()); i != Derivatives.end(); i++){
        double poliA = 0, poliB = 0;
        for(auto &j : *i){
            poliA += j.second*pow(a, j.first);
            poliB += j.second*pow(b, j.first);
        }
        if(poliA*poliA_prev<0) chA++;
        if(poliB*poliB_prev<0) chB++;
        poliA_prev = poliA;
        poliB_prev = poliB;
    }
    return chA-chB;
}