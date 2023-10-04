#include<iostream>
#include"ults.h"
#include<eigen3/Eigen/Core>
#include"eigen3/Eigen/Dense"

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

/**
 * @param x the x of th pixel coordinate
 * @param y the y of the pixel coordinate 
 * @param K the camera intrinsics
 * @details
     |f_x  0  c_x |     
 K = | 0  f_y c_y |  p =1/Z*KP, here P is camera coordinate.
     | 0   0   1  |

| X |       | X/Z |
| Y | ----> | Y/Z |
| Z |       |  1  |
*/
Eigen::Vector3d pixel_to_normalized(double x,double y,const Eigen::Matrix3d& K);

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
    // the coordinate points that we got is pixel coordinate, we need to transfom to nomalized plane
    Eigen::Matrix3d K;
    K << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1;
    double focal_length = 521;
    cv::Point2f principal_point(325.1, 249.7);
    
    #ifdef USE_CV_ESS
    //use opencv to calculate the essention matrix
    std::cout << "use opencv" << std::endl;
    std::vector<cv::Point2f> p1;
    std::vector<cv::Point2f> p2;
    #endif

    // eight-points-method
    Eigen::Matrix<double,Eigen::Dynamic,9> A(match.size(),9);

    // use the first 8 points
    for(int i=0;i<match.size();i++)
    {
        double u_1 = keypoints_one[match[i].queryIdx].pt.x;
        double v_1 = keypoints_two[match[i].queryIdx].pt.y;

        //opencv
        #ifdef USE_CV_ESS
        p1.push_back(keypoints_one[match[i].queryIdx].pt);
        #endif

        Eigen::Vector3d x_1 = pixel_to_normalized(u_1,v_1,K);
        u_1 = x_1(0);
        v_1 = x_1(1);

        double u_2 = keypoints_two[match[i].trainIdx].pt.x;
        double v_2 = keypoints_two[match[i].trainIdx].pt.y;
        
        //opencv
        #ifdef USE_CV_ESS
        p2.push_back(keypoints_two[match[i].trainIdx].pt);
        #endif

        Eigen::Vector3d x_2 = pixel_to_normalized(u_2,v_2,K);
        u_2 = x_2(0);
        v_2 = x_2(1);

        A(i,0) = u_2 * u_1;
        A(i,1) = u_2 * v_1;
        A(i,2) = u_2;
        A(i,3) = v_2 * u_1;
        A(i,4) = v_2 * v_1;
        A(i,5) = v_2;
        A(i,6) = u_1;
        A(i,7) = v_1;
        A(i,8) = 1;
    }

    //opencv
    #ifdef USE_CV_ESS
    cv::Mat essential_matrix = cv::findEssentialMat(p1,p2,focal_length,principal_point);
    std::cout << "the essention matrix from opencv: " << essential_matrix << std::endl;
    #endif

    // Ax = 0, can not direct use qr to get the result
    //Eigen::Matrix<double,9,1> e = A.fullPivLu().solve(Eigen::Matrix<double,8,1>::Zero());
    // instead caculate the eigenvector of A^T*A
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix<double,Eigen::Dynamic,9>> es;
    es.compute(A.transpose()*A);
    Eigen::Matrix<double,1,9> e = es.eigenvectors().col(0);
    Eigen::Matrix3d E;
    E <<
    e(0), e(3), e(6),
    e(1), e(4), e(7),
    e(2), e(5), e(8);

    std::cout<< "e(3): " << e(3) << std::endl;

    // calculate the rank 2 E
    Eigen::JacobiSVD<Eigen::Matrix3d> svd(E,Eigen::ComputeFullU | Eigen::ComputeFullV);
    Eigen::Matrix3d Sigma_prime;
    Sigma_prime << 
    svd.singularValues()(0),0,0,
    0,svd.singularValues()(1),0,
    0,0,0;

    auto E_prime = svd.matrixU() * Sigma_prime * svd.matrixV().transpose();
    std::cout << "E: " << E_prime << std::endl;

    //
    Eigen::Matrix<double, Eigen::Dynamic, 9> B(match.size(), 9);
        
        for (int i = 0; i < match.size(); ++i) {
            const auto &ca = keypoints_two[match[i].trainIdx].pt;
            const auto &cb = keypoints_two[match[i].trainIdx].pt;
            
            auto r = B.row(i);
            
            r(0) = cb.x * ca.x;     // F11
            r(1) = cb.x * ca.y;     // F21
            r(2) = cb.x;              // F31
            r(3) = cb.y * ca.x;     // F12
            r(4) = cb.y * ca.y;     // F22
            r(5) = cb.y;              // F32
            r(6) = ca.x;              // F13
            r(7) = ca.y;              // F23
            r(8) = 1.0;                 // F33
        }
        
        // Seek for a least squares solution such that |Ax| = 1. Given by the unit eigenvector of A'A associated with the smallest eigenvalue.
        Eigen::SelfAdjointEigenSolver< Eigen::Matrix<double, Eigen::Dynamic, 9> > er;
        er.compute((B.transpose() * B));
        
        Eigen::Matrix<double, 1, 9> f = er.eigenvectors().col(0); // Sorted ascending by eigenvalue.
        
        Eigen::Matrix3d F;
        F <<
        f(0), f(3), f(6),
        f(1), f(4), f(7),
        f(2), f(5), f(8);
        
        // Enforce singularity constraint such that rank(F) = 2. Which is the closest singular matrix to F under Frobenius norm.
        Eigen::JacobiSVD<Eigen::Matrix3d> svd_f(F, Eigen::ComputeFullU | Eigen::ComputeFullV);
        Eigen::DiagonalMatrix<double, 3> dPrime(svd_f.singularValues()(0), svd_f.singularValues()(1), 0.0);
        Eigen::Matrix3d FPrime = svd_f.matrixU() * dPrime * svd_f.matrixV().transpose();
        std::cout << "F: " << FPrime << std::endl;
        std::cout <<"number: " << float(-5.34121e-14) << std::endl;

        cv::Mat fund;
        fund = cv::findFundamentalMat(p1,p2);

        std::cout << "F from opencv: " << fund << std::endl;

    // draw the match picture
    cv::Mat good_match;
    cv::drawMatches(img_one,keypoints_one,img_two,keypoints_two,match,good_match);
    cv::imshow("good_match",good_match);
    cv::waitKey(0);

    return 0;
}

Eigen::Vector3d pixel_to_normalized(double x,double y,const Eigen::Matrix3d& K)
{
    Eigen::Vector3d p(x,y,1);
    Eigen::Vector3d x_i = K.inverse() * p;

    //std::cout << "x_i_3: " << x_i(2) << std::endl;
    return x_i;
}
