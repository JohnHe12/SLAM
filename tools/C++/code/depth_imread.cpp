#include<opencv2/opencv.hpp>
#include<iostream>
#include<typeinfo>

int main(int argc, char** argv)
{
    cv::Mat img;

    if(argc!=2)
    {
        std::cout << "Usage ./depth <path to depth image>" << std::endl;
    }

    img = cv::imread(argv[1],cv::IMREAD_UNCHANGED);

    unsigned short p1=img.ptr<unsigned short>(320)[240]; // this pointer points to the second row second element

    std::cout << "element: " <<p1 <<std::endl;
    std::cout << "is type unsigned short: " <<
    (typeid(p1)==typeid(unsigned short)? "yes":"No") << std::endl;
    
    return 0;
}