#include<thread>
#include<iostream>

class func
{
public:
    explicit func(int& i_):i(i_) {};
    void operator()()
    {
        for(size_t t=0;t<100000000000;t++)
        {
            std::cout << i << std::endl;
        }

    }

public:
    int& i;
};

int main()
{
    int a = 3;
    func f(a);
    std::thread t(f);
    t.detach();

    return 0;
}