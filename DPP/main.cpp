#include <iostream>
#include <thread>
#include <semaphore>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "noMutexPhil/sPhilDPP.h"


int main() {
    int amount;
    printf("Choose amount of philosophers:");
    cin >> amount;
    sPhilDPP(amount).init();

    return 0;
}

