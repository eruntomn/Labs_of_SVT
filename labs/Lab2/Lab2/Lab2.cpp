#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <ctime>

using namespace std;

//mutex m;

void Func(string name)
{
    long double i = 0;
    long double step = 1e-9;

    time_t start = time(NULL); 
    time_t current = start;

    while ((current - start) < 1)
    {
        i += step;
        current = time(NULL); 
    }

    //m.lock();
    cout << name << ": " << i << endl;
    //m.unlock();
}

int main() {

    std::thread thread1(Func, "t1");
    std::thread thread2(Func, "t2");
    std::thread thread3(Func, "t3");

    thread1.join();
    thread2.join();
    thread3.join();

    system("pause");
    return 0;
}