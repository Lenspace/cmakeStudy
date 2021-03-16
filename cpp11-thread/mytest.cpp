#include <iostream>
#include <thread>
using namespace std;

void call_from_thread(int n)
{
    cout << "call from thread " << n << endl;
}

int main()
{
    std::thread t[10];

    for (int i = 0; i < 10; i++)
    {
        t[i] = std::thread(call_from_thread, i);
    }

    cout << "thread begin." << endl;
    for (int i = 0; i < 10; i++)
    {
        t[i].join();
    }

    return 0;
}