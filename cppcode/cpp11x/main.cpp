#include <iostream>

#include <atomic>
#include <thread>
#include <vector>
#include <sstream>

std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;
std::stringstream stream;

std::atomic_flag calc_winner = ATOMIC_FLAG_INIT;
std::atomic<bool> calc_ready(false);

void append_number(int x)
{
    while (lock_stream.test_and_set()) {}

    stream << "thread #" << x << std::endl;
}

void th_counter(int id)
{
    while (!calc_ready) //等待主线程设置为true
    {
        std::this_thread::yield();
    }

    for (int i = 0; i < 100000; i++) {}

    if (!calc_winner.test_and_set())
    {
        std::cout << "thread #" << id << " won!\n";
    }
}

struct BaseStruct
{
    int a;
};

struct AltStruct
{
    AltStruct(int x, float y) : _x(x), _y(y) {}
    AltStruct(const BaseStruct &bs) : _bs(bs){};

    int get_x(){ return _x; }

private:
    int _x;
    float _y;

    BaseStruct _bs;
};

int main(int argc, char **argv)
{
    //std::cout << "hello world!" << std::endl;

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++)
    {
        //threads.push_back(std::thread(append_number,i) );
        threads.push_back(std::thread(th_counter, i) );
    }
    calc_ready = true; //开始计算

    for (auto &th : threads) th.join();

    AltStruct as{1,1.0};
    std::cout << "as._x=" << as.get_x() << std::endl;
    
    BaseStruct bs;
    AltStruct as2{bs};

    return 0;
}
