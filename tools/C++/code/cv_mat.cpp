#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

int main(int argc, char ** argv)
{
    cv::Mat t_x = cv::Mat::eye(3,3,CV_8U);

    std::cout << "Mat: " << t_x << std::endl;

    std::cout << t_x.at<int>(0,0) << std::endl;

    return 0;
}