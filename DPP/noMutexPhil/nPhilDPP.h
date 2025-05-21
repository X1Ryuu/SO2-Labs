//
// Created by BartKrups on 04.04.2025.
//

#ifndef NPHILDPP_H
#define NPHILDPP_H
#include <memory>
#include <semaphore>
#include <vector>


class nPhilDPP {
private:
    int num;
    int N;
    std::mutex mutex_access;
    std::vector<std::unique_ptr<std::binary_semaphore>> forks;
    int* arr;
public:
    nPhilDPP(int num):num(num){};
    bool pickForks(int num);
    void putForks(int num);
    void stats();
    void eat(int num);
    void philosopher(int num);
};



#endif //NPHILDPP_H
