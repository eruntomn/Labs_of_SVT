#include <iostream>
#include <thread>
#include <mutex>
#include <string>

using namespace std;

int coins = 0;
int Bob_coins = 0;
int Tom_coins = 0;

mutex m;

void coin_sharing(string name, int& thief_coins, int& companion_coins)
{
    while (true)
    {
        m.lock();

        if (coins == 0)
        {
            m.unlock();
            break;
        }

        if (thief_coins > companion_coins)
        {
            m.unlock();
            continue; 
        }

        if (coins == 1 && thief_coins == companion_coins)
        {
            m.unlock();
            break;
        }

        coins--;
        thief_coins++;

        m.unlock();
    }
}

int main() {
    cout << "Enter the number of coins: ";
    cin >> coins;

    int initial_coins = coins;
    cout << "A lot of coins: " << coins << endl;

    thread t1(coin_sharing, "Bob", ref(Bob_coins), ref(Tom_coins));
    thread t2(coin_sharing, "Tom", ref(Tom_coins), ref(Bob_coins));

    t1.join();
    t2.join();

    cout << "Bob: " << Bob_coins << endl;
    cout << "Tom: " << Tom_coins << endl;
    cout << "The dead men: " << coins << endl;

    system("pause");
    return 0;
}