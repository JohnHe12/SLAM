#include"ults.h"
#include"BRIEF_patten.h"

void compute_descriptor(Descriptor& descriptor,const cv::Mat& img,const Keypoints& keypoints)
{
    const int half_patch_size = 8;
    const int half_boundary = 16;
    int bad = 0; 
    for(const auto& kp:keypoints)
    {
        if(kp.pt.x<half_boundary || kp.pt.x>(img.cols-half_boundary) || 
        kp.pt.y < half_boundary || kp.pt.y>(img.rows-half_boundary))
        {
            bad++;
            descriptor.push_back({});
            continue;
        }

        // float m01(0),m10(0);
        // for(int i=kp.pt.x-half_patch_size;i<kp.pt.x+half_patch_size;++i)
        // {
        //     for(int j= kp.pt.y-half_patch_size;j<kp.pt.y+half_patch_size;++j)
        //     {
        //         m10+=i*img.at<uchar>(i,j);
        //         m01+=j*img.at<uchar>(i,j);
        //     }
        // };

            float m01 = 0, m10 = 0;
    for (int dx = -half_patch_size; dx < half_patch_size; ++dx) {
      for (int dy = -half_patch_size; dy < half_patch_size; ++dy) {
        uchar pixel = img.at<uchar>(kp.pt.y + dy, kp.pt.x + dx);
        m10 += dx * pixel;
        m01 += dy * pixel;
      }
    }

        //theta = acr tan(m10/m01)
        float m_squr = sqrt(m10*m10+m01*m01)+1e-18;// avoid divede zero
        //compute sin and cos 
        float sin_theta = m01 / m_squr;
        float cos_theta = m10 / m_squr;

        // generate the oritated BRIEF
        Desc desc(8,0);
        for(int i=0;i<8;i++)
        {
            u_int32_t d =0;
            for(int j=0;j<32;j++)
            {
                int point_index = (i*32+j)*4;
                cv::Point2f p(ORB_pattern[point_index],ORB_pattern[point_index+1]);
                cv::Point2f q(ORB_pattern[point_index+2],ORB_pattern[point_index+3]);
                
                //rotate BRIEF ---> RP, R=[cos_theat,-sin_theta] ---> P_rotate^T = [x*cos_theta-y*sin_theta,x*sin_theta+y*cos_theta]
                //                        [sin_theta,cons_theta]

                //debug: first time not add the keypoint coordiate cause the Segmentation fault (core dumped) problem because the Mat out of range 
                cv::Point2f p_rotate=cv::Point2f((p.x*cos_theta-p.y*sin_theta),(p.x*sin_theta+p.y*cos_theta))+kp.pt;
                cv::Point2f q_rotate=cv::Point2f((q.x*cos_theta-q.y*sin_theta),(q.x*sin_theta+q.y*cos_theta))+kp.pt;

                // juge the value of p and q --> problem: value of the gray sacle image is clear, but rgb is not 
                if(img.at<uchar>(p_rotate.y,p_rotate.x)<img.at<uchar>(q_rotate.y,q_rotate.x))
                {
                    d |= 1 << j;
                }

            }
            desc[i] = d;    
        }

        descriptor.push_back(desc);

    };

    std::cout << "bad point/total: " << bad << "/"<< keypoints.size()<<std::endl;

};