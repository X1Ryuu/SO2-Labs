/*
//
// Created by BartKrups on 04.04.2025.
//

#include "mPhilDPP.h"
void philosopherMutex(int num){
    int left = num;
    int right = (num + 1) % N;
    while (true) {

    {
    mutex_access.lock();


    if (!forks[left]->try_acquire()){
    mutex_access.unlock();
    printf("Philosohper %d tried to pick up left fork, but failed\n", num + 1);
    continue;
    }else
    {
    printf("Philosohper %d picked up left fork\n", num + 1);
    }

    if (!forks[right]->try_acquire()) {
    forks[left]->release();
    mutex_access.unlock();
    printf("Philosohper %d tried to pick up right fork, but failed, and also put left fork\n", num + 1);
    continue;
    }else
    {
    printf("Philosohper %d picked up right fork\n", num + 1);
    }

    eat(num);

    mutex_access.unlock();
    forks[left]->release();
    forks[right]->release();
    printf("Philosopher %d is thinking\n", num + 1);
    }

    this_thread::sleep_for(chrono::milliseconds(2000));

}*/
