#define eigen_assert(X) if(!(X)){throw (std::runtime_error("assert error"));}
#include"ults.h"
#include"eigen3/Eigen/Dense"

Eigen::Matrix3d Findfundametialmatrix(const Keypoints& points1,const Keypoints& points2,const Match& match)
{
    //calculate the normalized
    //eigen_assert(points1.size()==points2.size());
    Eigen::Vector2d p1(0,0),p2(0,0);
    int N = match.size();

    for(int i=0;i<N;i++)
    {
        p1[0] += points1[match[i].queryIdx].pt.x;
        p1[1] += points1[match[i].queryIdx].pt.y;

        p2[0] += points2[match[i].trainIdx].pt.x;
        p2[1] += points2[match[i].trainIdx].pt.y;

    }

    double t = 1./N;
    // calculate the average value of x and y
    p1 *= t;
    p2 *= t;

    std::cout << "p1: " << p1 << "\np2: " << p2<< std::endl;
    std::cout << "point: " << points1[match[0].queryIdx].pt.x << std::endl;
    double mean_x1(0),mean_y1(0),mean_x2(0),mean_y2(0);

    for(int i=0;i<N;i++)
    {
       mean_x1 +=(std::fabs(points1[match[i].queryIdx].pt.x-p1[0]));
       //std::cout << mean_x1 << std::endl;
       mean_y1 +=(std::fabs(points1[match[i].queryIdx].pt.y-p1[1]));

       mean_x2 +=(std::fabs(points2[match[i].trainIdx].pt.x-p2[0]));
       mean_y2 +=(std::fabs(points2[match[i].trainIdx].pt.y-p2[1]));
    }

    double sX1 = mean_x1 * t;
    double sY1 = mean_y1 * t;

    double sX2 = mean_x2 * t;
    double sY2 = mean_y2 * t;

    Eigen::Matrix<double,Eigen::Dynamic,9> A(N,9);
    double u1(0),v1(0),u2(0),v2(0);
    for(int i=0;i<N;i++)
    {
        auto r = A.row(i);
        u1 = (points1[match[i].queryIdx].pt.x-p1[0]) * sX1;
        v1 = (points1[match[i].queryIdx].pt.y-p1[1]) * sY1;

        u2 = (points2[match[i].trainIdx].pt.x-p2[0]) * sX2;
        v2 = (points2[match[i].trainIdx].pt.y-p2[1]) * sY2;

        r(0) = u2 * u1;     
        r(1) = u2 * v1;     
        r(2) = u2;            
        r(3) = v2 * u1;     
        r(4) = v2 * v1;     
        r(5) = v2;            
        r(6) = u1;           
        r(7) = v1;           
        r(8) = 1.0;         
    }

    Eigen::SelfAdjointEigenSolver< Eigen::Matrix<double, Eigen::Dynamic, 9> > es;
    es.compute(A.transpose()*A);
    Eigen::Matrix<double, 1, 9> f = es.eigenvectors().col(0);
    Eigen::Matrix3d F;
    F <<
    f(0),f(1),f(2),
    f(3),f(4),f(5),
    f(6),f(7),f(8);

    std::cout << "F: " << F << std::endl;

    Eigen::JacobiSVD<Eigen::Matrix3d> svd(F,Eigen::ComputeFullU | Eigen::ComputeFullV);

    Eigen::DiagonalMatrix<double, 3> Sigma(svd.singularValues()(0), svd.singularValues()(1), 0.0);
    std::cout << "here " << std::endl;
    std::cout << "F: " << F << std::endl;
    std::cout << "U: " << svd.matrixU() << std::endl;
    Eigen::Matrix3d FPrime;
    FPrime = svd.matrixU() * Sigma * svd.matrixV().transpose();
    std::cout << "############" << std::endl;

    //normalized matrix
    Eigen::Matrix3d T_1, T_2;
    T_1 << 
    sX1,0,-p1[0]*sX1,
    0,sY1,-p1[1]*sY1,
    0,0,1;

    T_2 << 
    sX2,0,-p2[0]*sX2,
    0,sY2,-p2[1]*sY2,
    0,0,1;

    //(T2x2)^T F' (T1x1) = x2^T T2^T F'T1 x1
    Eigen::Matrix3d F_prime = T_2.transpose() * FPrime * T_1;

    F_prime = F_prime /F_prime(2,2);

    return F_prime;
}