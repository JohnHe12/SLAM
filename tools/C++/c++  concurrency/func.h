#ifndef FUNC_H
#define FUNC_H

#include<iostream>
class func
{
public:
    explicit func(int& i_):i(i_) {};
    void operator()()
    {
        for(size_t t=0;t<100;t++)
        {
            i++;
        }

    }

public:
    int& i;
};

#endif