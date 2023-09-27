#include<iostream>
#include<bitset>
#include <nmmintrin.h>

/**
* calculate the binary operator |=, it is a OR binary operator
* << move from left to right
* @param unit32_t d has 32 bitwise
*/
int main(int argc, char** argv)
{
    uint32_t d = 1;
    // 0000000000
    d |= 1 << 1;
    std::bitset<32> x(d);
    std::cout << x << std::endl;
    std::bitset<8> y;
    uint8_t a = 0;

    for(int k = 0; k < 3; k++)
    {
        y = a;
        std::cout << "a: " << y << std::endl;
        a |= 1;
        a = a << k;
        y = a;
        std::cout << "after a: " << y << std::endl;
    }

    // Haming distance
    //cv::C
    uint32_t b = 5;
    uint32_t c = 1;
    int distance = 0;

    #ifdef ENABLE_SSE

    distance = _mm_popcnt_u32(b ^ c);

    std::cout << "distance: " << distance << std::endl;

    #endif


    return 0; 
}

