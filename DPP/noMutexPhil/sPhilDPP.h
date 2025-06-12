//
// Created by BartKrups on 04.04.2025.
//

#ifndef NPHILDPP_H
#define NPHILDPP_H
#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>
using namespace std;

class sPhilDPP {
private:
    int N;
    std::mutex mutex_access;
    std::vector<std::unique_ptr<std::binary_semaphore>> forks;
    int* arr;
    void eat(int num);
    void philosopher(int num);
    bool pickForks(int num);
    void putForks(int num);
public:
    sPhilDPP(int N): N(N){

    };
    void init();

    void stats();

};



#endif //NPHILDPP_H
