#include"ults.h"
#include<iostream>
#include <nmmintrin.h>

void bfMatch(const Descriptor& descriptor_one,const Descriptor& descriptor_two,Match& matches)
{
    //std::cout << "not finished " << std::endl;
    /*
    so this function is to use brute force to match the descriptor,
    1.loop every element in descriptor one, calculate the every distance with
    the descriptor_two.
    2.compare the distance, select the min distance as the match points
    3.push back the DMatch to the vector DMatch, Dmatch--> queridex,trainindex.distance
    4. good match: experience is the greater than the 2 times min distance,and limitation of the min
    distance is 30,which prevents from the too small min distance.

    */

    int min_distance =1000;
    for(int i=0;i<descriptor_one.size();i++)
    {
        if(descriptor_one[i].empty()) continue;
        cv::DMatch match(i,0,256);
        for(int j=0;j<descriptor_two.size();j++)
        {
            if(descriptor_two[j].empty()) continue;
            int distance=0;
            for(int k=0;k<8;k++)
            {
                distance += _mm_popcnt_u32(descriptor_one[i][k]^descriptor_two[j][k]);
            }
            if(distance<match.distance)
            {
                match.distance = distance;
                match.trainIdx=j;
            }

            if (distance<min_distance) min_distance=distance;
        }

        if(match.distance<MAX(min_distance,40))
        matches.push_back(match);
    }
    std::cout << "the match number: " << matches.size() << std::endl;
    std::cout << "min distance: " << min_distance << std::endl;

}