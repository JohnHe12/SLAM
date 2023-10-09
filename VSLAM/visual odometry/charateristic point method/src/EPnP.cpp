#include"ults.h"
#include<cmath>

Sophus::SE3d EPnP(const std::vector<Eigen::Vector3d>& p3d,const std::vector<Eigen::Vector2d>& p2d,const Eigen::Matrix3d& K)
{

    //Eigen::Matrix3d R=Eigen::AngleAxisd(M_PI/2,Eigen::Vector3d(0,0,1)).toRotationMatrix();

    //Eigen::Vector3d t(1.0,2.0,3.0);

    Sophus::SE3d T;
    int iteration = 6;
    double fx = K(0, 0);
    double fy = K(1, 1);
    double cx = K(0, 2);
    double cy = K(1, 2);
    for(int iter=0;iter<iteration;iter++)
    {
        int cost =0;
        std::cout <<"start T: \n" << T.matrix() << std::endl;
        Eigen::Matrix<double,6,6> H =Eigen::Matrix<double,6,6>::Zero();
        Eigen::Matrix<double,6,1> b =Eigen::Matrix<double,6,1>::Zero();
        for(int i=0;i<p3d.size();++i)
        {
            Eigen::Vector3d pc = T * p3d[i];
            Eigen::Vector2d proj(fx * pc[0] / pc[2] + cx, fy * pc[1] / pc[2] + cy);
            Eigen::Vector2d e = p2d[i] - proj;
            Eigen::Matrix<double,2,6> J;
            Eigen::Matrix<double,2,3> dk;
            dk(0,0)=K(0,0)/pc(2);
            dk(0,1)=0;
            dk(0,2) = -K(0,0)*pc(0)/(pc(2)*pc(2));
            dk(1,0)=0;
            dk(1,1)=K(1,1)/pc(2);
            dk(1,2)=-K(1,1)*pc(1)/(pc(2)*pc(2));
            dk = - dk;

            // std::cout << "dk:\n " << dk << std::endl;
            Eigen::Matrix<double,3,6> dp;
            Eigen::Matrix3d pc_hat = Sophus::SO3d::hat(pc);
            pc_hat = - pc_hat;
            // std::cout << "pc_hat: \n" << pc_hat << std::endl;
            dp << Eigen::Matrix3d::Identity(3,3),pc_hat;
            // std::cout << dp << std::endl;
            J = dk * dp;

            // use gauss-newton method to optimize the T(6x1)
            H += J.transpose() * J;
            // Eigen::Vector2d e;
            // e(0) = p2d[i](0)-(K * p3d[i])(0);
            // e(1) = p2d[i](1)-(K * p3d[i])(1);
            // std::cout << "e:\n" << e << std::endl;

            //Eigen::Matrix<double,6,1> b;
            b += -J.transpose() * e;
            cost += e.squaredNorm();
        }
        Eigen::Matrix<double,6,1,0> T_v;
        T_v = H.ldlt().solve(b);
        if (isnan(T_v[0])) 
        {
            std::cout << "result is nan!" << std::endl;
            break;
        }
        T = Sophus::SE3d::exp(T_v) * T;
        //std::cout << T_v << std::endl;
        std::cout <<"iteration " << iter << " cost= " << std::setprecision(12) << cost << std::endl;
        if(T_v.norm() < 1e-6)
        {
            break;
        }

    }
    
    std::cout << "the final T: \n" << T.matrix() << std::endl;

    return T;

}