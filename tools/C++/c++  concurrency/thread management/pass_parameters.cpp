#include<iostream>
#include<thread>

void func(std::unique_ptr<int> ptr)
{
    *ptr;
}

int main(int argc,char** argv)
{
    std::unique_ptr<int> a(new int(42));
    
    std::thread t(func,std::unique_ptr<int>(new int(22)));
    t.join();
    return 0;
}