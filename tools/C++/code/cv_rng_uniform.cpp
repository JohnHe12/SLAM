#include<opencv2/opencv.hpp>
#include<iostream>

int main(int argc, char**argv)
{
    cv::RNG rgn;
    for(int i=0;i<10;i++)
    {
        int x = rgn.uniform(20,100);

        std::cout << x << std::endl;
    }

    return 0;
}