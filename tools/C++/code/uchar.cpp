#include<iostream>
#include<string>
#include <type_traits>
#include <cassert>
#include<vector>
typedef unsigned char uchar;

// the type is under the link https://en.cppreference.com/w/cpp/language/types

int main(int argc, char ** argv)
{

    if(argc != 2)
    {
        std::cout << "usage ./char arc" << std::endl;
        return 1; 
    }
    
    std::cout <<"argv[0]: " <<argv[0] << std::endl;
    std::cout <<"argv[1]: " <<argv[1] << std::endl;
    std::cout <<"argv[1][0]: " <<argv[1][0] << std::endl;


    std::vector<int32_t> v(8,3);
    for (auto i = v.begin(); i != v.end(); ++i)
        std::cout << *i << " ";

    return 0;
}