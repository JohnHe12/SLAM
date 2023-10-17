#include<thread>
#include<iostream>

class join_thread
{
    std::thread t;

public:
    join_thread() = default;
    template<typename Callable, typename ... Args>
    explicit join_thread(Callable&& func,Args&& ... args):
    t(std::forward<Callable>(func),std::forward<Args>(args)...){};

    explicit join_thread(std::thread t_) noexcept:
    t(std::move(t_))
    {}
    join_thread(join_thread&& other) noexcept:
    t(std::move(other.t))
    {}
    join_thread& operator=(join_thread&& other) noexcept
    {
    if(joinable()){
    join();
    }
    t = std::move(other.t);
    return *this;
    }
    join_thread& operator=(std::thread other) noexcept
    {
    if(joinable())
    join();
    t=std::move(other);
    return *this;
    }
    ~join_thread() noexcept
    {
    if(joinable())
    {
        join();
        std::cout << "joinable" << std::endl;
    }
    else
    std::cout << "not joinable" << std::endl;
    }

    bool joinable() const noexcept
    {
    return t.joinable();
    }

    void join()
    {
        t.join();
    }

    std::thread& as_thread() noexcept
    {
    return t;
    }
    const std::thread& as_thread() const noexcept
    {
    return t;
    }
};

void func(int i)
{
    ++i;
}

void func2(int j)
{
    j++;
}
int main()
{
    join_thread b(func,1);
    join_thread c(func2,2);
    join_thread d(func2,3);
    join_thread a(std::move(b));
    a=std::move(c);
    a=std::move(d);

    // std::thread t1(func,1);
    // // 1
    // std::thread t2=std::move(t1);
    // // 2
    // t1=std::thread(func2,1);
    // // 3
    // std::thread t3;
    // // 4
    // t3=std::move(t2); // 5
    // t1=std::move(t3);

    return 0;
}