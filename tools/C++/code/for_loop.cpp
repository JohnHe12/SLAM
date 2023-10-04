#include<iostream>

int main(int argc,char** argv)
{
    std::cout << "i: " << std::endl;
    for(int i=0;i<8;++i)
    {
        std::cout << i << std::endl;
    }

    std::cout << "j: " << std::endl;

    for(int j=0;j<8;j++)
    {
        std::cout << j << std::endl;
    }
}