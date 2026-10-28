//#include <iostream>
//#include <time.h>
//
//using namespace std;
//
//
//long long factorial(int n) {
//    long long res = 1;
//    for (int i = 2; i <= n; ++i) {
//        res *= i;
//    }
//    return res;
//}
//
//int main() {
//
//    const int iterations = 10000000;
//    volatile long long result = 0;
//
//    clock_t start = clock();
//
//    for (int i = 0; i < iterations; ++i) {
//        result = factorial(10);
//    }
//
//    clock_t end = clock();
//    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
//
//    cout << "Result: " << result << endl;
//    cout << "Count of iterations: " << iterations << endl;
//    cout << "Time: " << seconds << " seconds" << endl;
//
//    return 0;
//}
#include <iostream>
#include <thread>
#include <string>
#include <time.h>

using namespace std;

long long factorial(int n) {
    long long res = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
    }
    return res;
}

void Func(string name)
{
    const int iterations = 10000000;
    volatile long long result = 0;

    for (int i = 0; i < iterations; ++i) {
        result = factorial(10);
    }

    cout << "Stream " << name << " completed. Result: " << result << endl;
}

int main() {
    cout << "One after another" << endl;

    clock_t start1 = clock();

    Func("S1");
    Func("S2");

    clock_t end1 = clock();

    double time1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
    cout << "Time: " << time1 << " sec." << endl << endl;

    cout << "In the streams" << endl;

    clock_t start2 = clock();

    thread Stre1(Func, "Stre1");
    thread Stre2(Func, "Stre2");

    Stre1.join();
    Stre2.join();

    clock_t end2 = clock();

    double time2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    cout << "Time: " << time2 << " sec." << endl;

    system("pause");
    return 0;
}