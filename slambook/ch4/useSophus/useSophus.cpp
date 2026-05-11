#include <iostream>
#include <cmath>

using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <sophus/se3.h>
#include <sophus/so3.h>

int main()
{
    // Rotate 90 degrees around Z-axix
    Eigen::Matrix3d R = Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d(0, 0, 1)).toRotationMatrix();

    // Convert to Sophus SO3
    Sophus::SO3 SO3_R(R);
    Sophus::SO3 SO3_v(0, 0, M_PI/  2); // Rotate 90 degrees around Z-axis
    Eigen::Quaterniond q(R);
    Sophus::SO3 SO3_q(q);

    cout.precision(3);
    cout << "SO3 from Rotation Matrix:\n" << SO3_R.matrix() << endl;
    cout << "SO3 from Angle-Axis:\n" << SO3_v.matrix() << endl;  
    cout << "SO3 from Quaternion:\n" << SO3_q.matrix() << endl;

    // Use log() to get the Lie algebra (so3) from the SO3 group element
    Eigen::Vector3d so3 = SO3_R.log();
    cout << "so3 (Lie algebra of SO3):\n" << so3.transpose() << endl;
    // hat(so3) converts the vector back to a skew-symmetric matrix
    cout << "so3 hat (skew-symmetric matrix):\n" << Sophus::SO3::hat(so3) << endl;
    // vee() converts the skew-symmetric matrix back to a vector
    cout << "so3 vee (vector from skew-symmetric matrix):\n" <<
        Sophus::SO3::vee(Sophus::SO3::hat(so3)).transpose() << endl;

    // Update the SO3 element using a small update in the Lie algebra
    Eigen::Vector3d update_so3 = Eigen::Vector3d(1e-4, 0, 0); // Small update
    Sophus::SO3 SO3_updated = Sophus::SO3::exp(update_so3) * SO3_R; // Update the SO3 element
    cout << "Updated SO3 after applying small update:\n" << SO3_updated.matrix() << endl;

    Eigen::Vector3d t(1, 0, 0);
    Sophus::SE3 SE3_Rt(R, t); // SE3 element from R and translation
    Sophus::SE3 SE3_qt(q, t); // SE3 element from q and translation
    cout << "SE3 from Rotation Matrix and Translation:\n" << SE3_Rt.matrix() << endl;
    cout << "SE3 from Quaternion and Translation:\n" << SE3_qt.matrix() << endl;
    
    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    Vector6d se3 = SE3_Rt.log(); // Get the Lie algebra
    cout << "se3 (Lie algebra of SE3):\n" << se3.transpose() << endl;
    cout << "se3 hat (4x4 matrix):\n" << Sophus::SE3::hat(se3) << endl;
    cout << "se3 vee (vector from 4x4 matrix):\n"
        << Sophus::SE3::vee(Sophus::SE3::hat(se3)).transpose() << endl;


    Vector6d update_se3 = Vector6d(1e-4, 0, 0, 0, 0, 0); // Small update
    update_se3.setZero();
    update_se3(0, 0) = 1e-4; // Small update in the first component (rotation around x-axis)
    Sophus::SE3 SE3_updated = Sophus::SE3::exp(update_se3) * SE3_Rt; // Update the SE3 element
    cout << "Updated SE3 after applying small update:\n" << SE3_updated.matrix() << endl;

    return 0;
}