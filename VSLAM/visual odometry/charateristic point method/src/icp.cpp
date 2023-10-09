#undef eigen_assert
#define eigen_assert(x) if(!(x)){throw (std::runtime_error("the size of the 3d point set is not the same"));}
#include"ults.h"

using namespace Eigen;
void ICP(const std::vector<Eigen::Vector3d>&pc1,const std::vector<Eigen::Vector3d>&pc2,Eigen::Matrix3d&R,Eigen::Vector3d&t)
{
    // calculate the center point of the 3d point set
    eigen_assert(pc1.size()==pc2.size());
    Vector3d p=Vector3d::Zero();
    Vector3d q=Vector3d::Zero();

    for(const auto& i:pc1)
    {
        p+=i;
    }

    for(const auto& j:pc2)
    {
        q+=j;
    }

    p = p/pc1.size();
    q = q/pc2.size();

    // calculate the W = XY^T

    Matrix<double,3,Dynamic> X(3,pc1.size());
    for(int i=0;i<pc1.size();i++)
    {
        X.col(i) = pc1[i]-p;
    }

    Matrix<double,Dynamic,3> Y_T(pc2.size(),3);
    for(int j=0;j<pc2.size();j++)
    {
        Y_T.row(j) = pc2[j]-q;
        
    }

    Matrix3d M;
    M = X* Y_T;
    JacobiSVD<Matrix3d> svd(M,ComputeFullU | ComputeFullV);
    // std::cout << "U: \n" <<svd.matrixU()<< std::endl;
    // std::cout << "V: \n" << svd.matrixV() << std::endl;
    R = svd.matrixV() * svd.matrixU().transpose();
    if(R.determinant()< 0)
    {
        R = -R;
    }
    t = q - R*p;
}