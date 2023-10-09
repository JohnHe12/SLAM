#include"ults.h"
#include<opencv2/opencv.hpp>

Eigen::Vector3d pixel_nor(const Eigen::Vector3d& p,const Eigen::Matrix3d& K);
void pose_estimation_3d3d(const std::vector<Eigen::Vector3d> &pts1,
                          const std::vector<Eigen::Vector3d> &pts2,
                          Eigen::Matrix3d &R, Eigen::Vector3d &t);

int main(int argc, char ** argv)
{
    if(argc !=5)
    {
        std::cout << "Usage: ./icp img1 img2 dpth1 dpth2" << std::endl;

        return 1;
    }
    // imread the photo
    cv::Mat img1 = cv::imread(argv[1],0);
    cv::Mat img2 = cv::imread(argv[2],0);
    // imread the depth image
    cv::Mat dp1 = cv::imread(argv[3],cv::IMREAD_UNCHANGED);
    cv::Mat dp2 = cv::imread(argv[4],cv::IMREAD_UNCHANGED);

    // find the feature
    Keypoints k1;
    Keypoints k2;
    cv::FAST(img1,k1,40);
    cv::FAST(img2,k2,40);

    // generate descriptor
    Descriptor d1;
    Descriptor d2;
    compute_descriptor(d1,img1,k1);
    compute_descriptor(d2,img2,k2);
    
    // match the  kepoints
    Match matches;
    bfMatch(d1,d2,matches);

    //generate the 3d point set
    unsigned short ds1(0),ds2(0);
    int bad =0;

    std::vector<Eigen::Vector3d> pcs1,pcs2;

    Eigen::Matrix3d K;
    K << 520.9, 0, 325.1, 
          0, 521.0, 249.7, 
          0, 0, 1;

    for(int i=0;i<matches.size();i++)
    {
        ds1=dp1.ptr<unsigned short>(k1[matches[i].queryIdx].pt.y)[int(k1[matches[i].queryIdx].pt.x)];
        ds2=dp2.ptr<unsigned short>(k2[matches[i].trainIdx].pt.y)[int(k2[matches[i].trainIdx].pt.x)];
        if(ds1==0 || ds2==0)
        {
            bad++;
            continue;
        }

        Eigen::Vector3d pix1(k1[matches[i].queryIdx].pt.x,k1[matches[i].queryIdx].pt.y,1);
        Eigen::Vector3d pix2(k2[matches[i].trainIdx].pt.x,k2[matches[i].trainIdx].pt.y,1);

        double dd1=double(ds1)/5000.0;
        double dd2=double(ds2)/5000.0;

        Eigen::Vector3d pn1 = pixel_nor(pix1,K); 
        Eigen::Vector3d pn2 = pixel_nor(pix2,K);

        Eigen::Vector3d pc1=pn1*dd1;
        Eigen::Vector3d pc2=pn2*dd2;

        pcs1.push_back(pc1);
        pcs2.push_back(pc2);
    }
    Eigen::Matrix3d R;
    Eigen::Vector3d t;
    ICP(pcs1,pcs2,R,t);

    std::cout << "R: \n" << R << std::endl;
    std::cout << "t: \n" << t << std::endl;
}

void pose_estimation_3d3d(const std::vector<Eigen::Vector3d> &pts1,
                          const std::vector<Eigen::Vector3d> &pts2,
                          Eigen::Matrix3d &R, Eigen::Vector3d &t) {
  Eigen::Vector3d p1, p2;     // center of mass
  int N = pts1.size();
  for (int i = 0; i < N; i++) {
    p1 += pts1[i];
    p2 += pts2[i];
  }
  p1 = Eigen::Vector3d(p1 / N);
  p2 = Eigen::Vector3d(p2 / N);
  std::vector<Eigen::Vector3d> q1(N), q2(N); // remove the center
  for (int i = 0; i < N; i++) {
    q1[i] = pts1[i] - p1;
    q2[i] = pts2[i] - p2;
  }

  // compute q1*q2^T
  Eigen::Matrix3d W = Eigen::Matrix3d::Zero();
  for (int i = 0; i < N; i++) {
    W += Eigen::Vector3d(q1[i](0), q1[i](1), q1[i](2)) * Eigen::Vector3d(q2[i](0), q2[i](1), q2[i](2)).transpose();
  }
  std::cout << "W=" << W << std::endl;

  // SVD on W
  Eigen::JacobiSVD<Eigen::Matrix3d> svd(W, Eigen::ComputeFullU | Eigen::ComputeFullV);
  Eigen::Matrix3d U = svd.matrixU();
  Eigen::Matrix3d V = svd.matrixV();

  std::cout << "U=" << U << std::endl;
  std::cout << "V=" << V << std::endl;

  R = U * (V.transpose());
  if (R.determinant() < 0) {
    R = -R;
  }
  t = Eigen::Vector3d(p1(0), p1(1), p1(2)) - R * Eigen::Vector3d(p2(0), p2(1), p2(2));
}

Eigen::Vector3d pixel_nor(const Eigen::Vector3d& p,const Eigen::Matrix3d& K)
{
    Eigen::Vector3d x = K.inverse() * p;

    return x;
}