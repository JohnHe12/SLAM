#include<opencv2/opencv.hpp>
#include<cmath>
#include<iostream>

int main(int argc,char** argv)
{
    cv::Point2f p(1,1);
    double m = cv::norm(p);

    std::cout << "norm: " << m << std::endl;

    (m == std::sqrt(2)) ? std::cout << "yes" : std::cout<<"no";

    std::cout << "?" << std::endl;

    return 0;
}