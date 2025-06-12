//
// Created by BartKrups on 04.04.2025.
//

#include "sPhilDPP.h"
using namespace std;
void sPhilDPP::eat(int num)
{
    printf("Philosopher %d is eating\n", num + 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    printf("Philosopher %d finished eating\n", num + 1);
    arr[num]++;
}

void sPhilDPP::stats(){
    while (true) {
        if(mutex_access.try_lock()) {
            printf("Eaten: ");
            for (int i = 0; i < N; i++) {
                printf("%d - %d ,  ", i + 1, arr[i]);
            }
            printf("\n");
            mutex_access.unlock();
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void sPhilDPP::putForks(int num)
{
    int left = num;
    int right = (num + 1) % N;
    forks[left]->release();
    forks[right]->release();
}

bool sPhilDPP::pickForks(int num)
{
    int left = num;
    int right = (num + 1) % N;
    if (!forks[left]->try_acquire()){
        printf("Philosohper %d tried to pick up left fork, but failed\n", num + 1);
        return false;
    }
    printf("Philosohper %d picked up left fork\n", num + 1);


    if (!forks[right]->try_acquire()) {
        forks[left]->release();
        printf("Philosohper %d tried to pick up right fork, but failed, and also put left fork\n", num + 1);
        return false;
    }
    printf("Philosohper %d picked up right fork\n", num + 1);
    return true;

}

void sPhilDPP::philosopher(int num)
{
    while(true)
    {
        printf("Philosopher %d is thinking\n", num + 1);
        if(pickForks(num))
        {
            eat(num);
            putForks(num);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    }
}

void sPhilDPP::init(){
    for (int i = 0; i < N; i++) {
        forks.push_back(make_unique<binary_semaphore>(1));
    }
    arr = new int[N];

    for (int i = 0; i < N; i++) {
        arr[i] = 0;
    }

    vector<thread> threads;


    for (int i = 0; i < N; i++) {
        threads.emplace_back([this, i](){ this->philosopher(i);});
    }

    //thread(stats).join();

    for (auto& t : threads) {
        t.join();
    }

}
