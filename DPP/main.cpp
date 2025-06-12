#include <iostream>
#include <thread>
#include <semaphore>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;
int N;
vector<unique_ptr<binary_semaphore>> forks;
mutex mutex_access;
int* arr;




void eat(int num) {
    printf("Philosopher %d is eating\n", num + 1);
    this_thread::sleep_for(chrono::milliseconds(2000));
    printf("Philosopher %d finished eating\n", num + 1);
    arr[num]++;

}

void stats(){
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

void putForks(int num)
{
    int left = num;
    int right = (num + 1) % N;
    forks[left]->release();
    forks[right]->release();
}

bool pickForks(int num)
{
    int left = num;
    int right = (num + 1) % N;
    if (!forks[left]->try_acquire()){
        mutex_access.unlock();
        printf("Philosohper %d tried to pick up left fork, but failed\n", num + 1);
        return false;
    }
    printf("Philosohper %d picked up left fork\n", num + 1);


    if (!forks[right]->try_acquire()) {
        forks[left]->release();
        mutex_access.unlock();
        printf("Philosohper %d tried to pick up right fork, but failed, and also put left fork\n", num + 1);
        return false;
    }
    printf("Philosohper %d picked up right fork\n", num + 1);
    return true;

}

void philosopher(int num)
{
    while(true)
    {
        printf("Philosopher %d is thinking\n", num + 1);
        if(pickForks(num))
        {
            eat(num);
            putForks(num);
        }
        this_thread::sleep_for(chrono::milliseconds(2000));

    }
}

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

    }

}


int main() {
    int amount;
    printf("Choose amount of philosophers:");
    cin >> amount;
    N = amount;

    for (int i = 0; i < N; i++) {
        forks.push_back(make_unique<binary_semaphore>(1));
    }

    arr = new int[N];

    for (int i = 0; i < N; i++) {
        arr[i] = 0;
    }

    thread threads[N];


    for (int i = 0; i < N; i++) {
        threads[i] = thread(philosopher, i);
    }

    //thread(stats).join();

    for (int i = 0; i < N; i++)
        threads[i].join();

    return 0;
}

