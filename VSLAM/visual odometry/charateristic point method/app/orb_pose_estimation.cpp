#include<iostream>
#include"ults.h"

/**
 * this file is to create a orb feature extractor by john 2023/10/2
 * use C++ 14 and opencv 4
 * the step of the orb:
 * 1. calculate the feature detector: Fast
 * 2. feature descriptor: oritated BRIEF ---> calculate the angle
 * 3. match the feature: brute-force-matching and Haming distance
 * 4. calculate the essention matrix
 * 5. recover the motion of the camera ---> R,t
 * 6. calculte the 3d point coordinate
*/

int main(int argc, char ** argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: ./pose_estimate path image1 path image2" << std::endl;
    }
    // imread the two neighboring images
    cv::Mat img_one = cv::imread(argv[1],cv::IMREAD_UNCHANGED);
    cv::Mat img_two = cv::imread(argv[2],cv::IMREAD_UNCHANGED);

    // create the detector fast,to extract the keypoints
    Keypoints keypoints_one;
    Keypoints keypoints_two;
    cv::FAST(img_one,keypoints_one,40);
    cv::FAST(img_two,keypoints_two,40);

    // feature descriptor oritated BRIEF
    // 1. calculate the angle
    double m01,m10,m00;
    m01,m10,m00 = calculate_angel(keypoints_one,img_one);
    double sintheta,costheta;
    sintheta = m10/m00;
    costheta = m01/m00;
    
    // 2. create the descriptor
    Desc descriptor_one(8,0),descriptor_two(8,0);
    compute_descriptor(descriptor_one,img_one,keypoints_one,sintheta,costheta);
    compute_descriptor(descriptor_two,img_two,keypoints_two,sintheta,costheta);

    // match the feature through the BRIEF descriptor with Haming distance and brute force matching
    Match match;
    bfMatch(descriptor_one,descriptor_two,match);

    // calculate the essention matrix ---> x2^TE*x1 = 0, eight-point-method

    return 0;
}
