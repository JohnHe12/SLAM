#define cv_assert_empty(x) if(x) {throw (std::runtime_error("the image not be loaded, please check"));}
#include<iostream>
#include<opencv2/opencv.hpp>
#include"ults.h"
#include"eigen3/Eigen/Dense"

inline Eigen::Vector3d pixel_to_normalized(const Eigen::Vector2d& pixel,const Eigen::Matrix3d& K)
{
    Eigen::Vector3d p(pixel(0),pixel(1),1);
    Eigen::Vector3d x_i = K.inverse() * p;

    //std::cout << "x_i_3: " << x_i(2) << std::endl;
    return x_i;
}

/**
 * this function realized a epnp method by mysself
 * created by john 2023/10/08
 * 
 * as we all know, if we want to calculate the EPnP,it
 * needs to figure out the camera corrdinate of p2, and 
 * we let the the camera coordinate as the world coordinate 
*/

int main(int argc,char**argv)
{
    if(argc!=4)
    {
        std::cout <<
        "Usage: ./epnp <path to first image> <path to second image> <depth image 1>"
        << std::endl;

        return 1;
    }
    //imread the image
    cv::Mat img1 = cv::imread(argv[1],0);
    cv::Mat img2 = cv::imread(argv[2],0);

    cv_assert_empty(img1.empty() || img2.empty());

    //crate the 3d point from p1
    // find the match
    Keypoints keypoints_one;
    Keypoints keypoints_two;
    cv::FAST(img1,keypoints_one,40);
    cv::FAST(img2,keypoints_two,40);

    Descriptor descriptor_one;
    Descriptor descriptor_two;
    //calculate the descriptor
    compute_descriptor(descriptor_one,img1,keypoints_one);
    compute_descriptor(descriptor_two,img2,keypoints_two);

    // find the match
    Match matches;
    bfMatch(descriptor_one,descriptor_two,matches);

    // imread the depth image, attention: the depth image is stored in 16-bits----> unsigned short
    cv::Mat dp1 = cv::imread(argv[3],cv::IMREAD_UNCHANGED);
    //cv::Mat dp2 = cv::imread(argv[4],cv::IMREAD_UNCHANGED);

    // 3d - 2d
    std::vector<Eigen::Vector3d> points_3d;
    std::vector<Eigen::Vector2d> points_2d;

    Eigen::Matrix3d K;
    K << 520.9, 0, 325.1, 
         0, 521.0, 249.7, 
         0, 0, 1;
    int bad = 0;
    for(const auto& match:matches)
    {
        // extracte the depth imformation and delete the z=0 point
        unsigned short d=0;
        d = dp1.ptr<unsigned short>(int(keypoints_one[match.queryIdx].pt.y))[int(keypoints_one[match.queryIdx].pt.x)];
        if(d==0)
        {
            bad++;
            continue;
        }
        double dd=d/5000;
        Eigen::Vector2d p_pix(keypoints_one[match.queryIdx].pt.x,keypoints_one[match.queryIdx].pt.y);
        Eigen::Vector3d p1_n(pixel_to_normalized(p_pix,K));
        // the first camera coordinate as world coordinate
        Eigen::Vector3d p3w=p1_n * dd;
        assert(p3w(2)==dd);
        points_3d.push_back(p3w);
        Eigen::Vector2d p2_pix(keypoints_two[match.trainIdx].pt.x,keypoints_two[match.trainIdx].pt.y);
        points_2d.push_back(p2_pix);
    }

    std::cout << "bad depth/total match point: " << bad << "/" << matches.size() << std::endl;
    assert(points_3d.size()==points_2d.size()&&points_3d.size()==(matches.size()-bad));
    EPnP(points_3d,points_2d,K);
    return 0;
}