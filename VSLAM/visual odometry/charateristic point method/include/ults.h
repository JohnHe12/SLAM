#ifndef ULTS_H
#define ULTS_H

#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
typedef std::vector<u_int32_t> Desc; // 8*32 = 256
typedef std::vector<cv::KeyPoint> Keypoints;
typedef std::vector<cv::DMatch> Match;

/**
 * @param keypoints the feature of the image
 * @param img the img of the detected photo
 * @return m00,m01,m10,and keypoints_one_new
*/
double calculate_angel(const Keypoints& keypoints,const cv::Mat& img);

/**
 * this function is to create the BRIEF descriptor
 * @param descriptor is to generate a 256 binary descriptor
 * @param img is the correspond keypoint image
 * @param keypoints the keypoints of the image
 * @param sintheta
 * @param costheta
 * @note if the discriptor of the keypoint is outside the boundry of the image, set the descriptor {}, and push back to the Desc.
*/
void compute_descriptor(Desc& descriptor,const cv::Mat& img,const Keypoints& keypoints,double sintheta,double costheta);

/**
 * this function is to use brute forcing match to caculate the Haming distance to match the descriptor
 * @param descriptor_one the first binary 8*32 descriptor vector
 * @param descriptor_two the second binary 8*32 descriptor
 * @param matches generate the matches point vector, the element of the cv::DMatch is the queridex the index in first descriptor
 * trainindex the index in second descriptor vector, and the distance, so here is the haming distance, calculate the number of 1
*/
void bfMatch(const Desc& descriptor_one,const Desc& descriptor_two,Match& matches);

#endif  