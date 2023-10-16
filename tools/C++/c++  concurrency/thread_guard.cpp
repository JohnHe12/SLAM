#include<thread>
#include"func.h"

class thread_guard
{
    public:
    explicit thread_guard(std::thread& t_):t(t_) {};
    thread_guard(const thread_guard&)=delete;
    thread_guard operator=(const thread_guard&)=delete;
    ~thread_guard()
    {
        if(t.joinable())
        {
            t.join();
            std::cout << "stop the thread" << std::endl;
        }
    }

    std::thread& t;
};

int main()
{
    int a =3;
    func f(a);

    std::thread t(f);
    thread_guard g(t);
    std::cout << "start thread" << std::endl;
}
