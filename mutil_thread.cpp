//
// Created by zwl on 24-9-11.
//
#include<thread>
#include<iostream>
#include<condition_variable>
#include<mutex>
using namespace std;

mutex m;
condition_variable cv;
int cur_num;

void fun(int thread_id, int traget_num) {
    for(int i = 1; i <= 100; i++) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [traget_num]{ return traget_num == cur_num; });
        cout << thread_id << ":" << i << endl;
        cur_num = (cur_num + 1)%3;
        cv.notify_all();
    }
}

int main() {
    thread t1(fun, 1, 0);
    thread t2(fun, 2, 1);
    thread t3(fun, 3, 2);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}