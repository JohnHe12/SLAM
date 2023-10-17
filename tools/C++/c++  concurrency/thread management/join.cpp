#include<thread>
#include<iostream>

void func(int i)
{
    i++;
};

void func2(int j)
{
    j++;
};

int main()
{
    std::thread t(func,1);
    std::cout << "t joinable: " << t.joinable() << std::endl;

    std::thread t2;
    std::cout << "t2 joinable: " << t2.joinable() << std::endl;

    t2 = std::thread(func2,2);
    std::cout << "t2 joinable: " << t2.joinable() << std::endl;

    t.join();
    std::cout << "after join, t joinable: " << t.joinable() << std::endl;
    
    t=std::move(t2);
    std::cout << "after join,t = std::move(t2) t joinable: " << t.joinable() << std::endl;
    std::cout << "t2 joinable: " << t2.joinable() << std::endl;
    t.join();


    return 0;    
}