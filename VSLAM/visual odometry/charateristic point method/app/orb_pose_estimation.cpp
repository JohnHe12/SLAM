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
    cv::Mat img_one = cv::imread(argv[1],0);
    cv::Mat img_two = cv::imread(argv[2],0);
    assert(img_one.data != nullptr && img_two.data != nullptr);
    // create the detector fast,to extract the keypoints
    Keypoints keypoints_one;
    Keypoints keypoints_two;
    cv::FAST(img_one,keypoints_one,40);
    cv::FAST(img_two,keypoints_two,40);

    // feature descriptor oritated BRIEF


    // 2. create the descriptor
    Descriptor descriptor_one;
    Descriptor descriptor_two;
    compute_descriptor(descriptor_one,img_one,keypoints_one);
    compute_descriptor(descriptor_two,img_two,keypoints_two);

    // match the feature through the BRIEF descriptor with Haming distance and brute force matching
    Match match;
    bfMatch(descriptor_one,descriptor_two,match);

    // calculate the essention matrix ---> x2^TE*x1 = 0, eight-point-method

    // draw the match picture
    cv::Mat good_match;
    cv::drawMatches(img_one,keypoints_one,img_two,keypoints_two,match,good_match);
    cv::imshow("good_match",good_match);
    cv::waitKey(0);

    return 0;
}
