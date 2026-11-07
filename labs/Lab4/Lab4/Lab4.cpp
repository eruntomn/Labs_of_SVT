#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int dish1 = 3000;
int dish2 = 3000;
int dish3 = 3000;

int fat1_eaten = 0;
int fat2_eaten = 0;
int fat3_eaten = 0;

int dead_count = 0;

bool cook_fired = false;
bool cook_quit = false;
bool all_dead = false;

mutex m;

const int gluttony = 20;
const int efficiency_factor = 1;

void Cook() {
    auto start = chrono::steady_clock::now();

    while (true) {
        m.lock();

        if (all_dead || cook_fired) {
            m.unlock();
            break;
        }
        m.unlock();

        auto now = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::seconds>(now - start).count() >= 5) {
            m.lock();
            if (!cook_fired && !all_dead) {
                cook_quit = true;
            }
            m.unlock();
            break;
        }

        m.lock();
        dish1 += efficiency_factor;
        dish2 += efficiency_factor;
        dish3 += efficiency_factor;
        m.unlock();

        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void FatGuy(string name, int& my_dish, int& my_eaten) {
    while (true) {
        m.lock();

        if (cook_fired || cook_quit || all_dead) {
            m.unlock();
            break;
        }
        if (my_eaten >= 10000) {
            dead_count++;
            if (dead_count == 3) {
                all_dead = true;
            }
            m.unlock();
            break;
        }

        if (dish1 <= 0 || dish2 <= 0 || dish3 <= 0) {
            cook_fired = true;
            m.unlock();
            break;
        }

        if (my_dish >= gluttony) {
            my_dish -= gluttony;
            my_eaten += gluttony;
        }
        else if (my_dish > 0) {
            my_eaten += my_dish;
            my_dish = 0;
        }

        m.unlock();

        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main() {
    cout << "Gluttony: " << gluttony << ", the effectiveness of the Kyk: " << efficiency_factor << endl;

    thread cook(Cook);
    thread f1(FatGuy, "Fat man 1", ref(dish1), ref(fat1_eaten));
    thread f2(FatGuy, "Fat man 2", ref(dish2), ref(fat2_eaten));
    thread f3(FatGuy, "Fat man 3", ref(dish3), ref(fat3_eaten));

    cook.join();
    f1.join();
    f2.join();
    f3.join();

    cout << "Fat man 1 ate: " << fat1_eaten << endl;
    cout << "Fat man 2 ate: " << fat2_eaten << endl;
    cout << "Fat man 3 ate: " << fat3_eaten << endl;

    if (all_dead) cout << "All burst (Kyk no salary)." << endl;
    else if (cook_fired) cout << "Kyk was fired." << endl;
    else if (cook_quit) cout << "Kyk quit himself." << endl;

    system("pause");
    return 0;
}