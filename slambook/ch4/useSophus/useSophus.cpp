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
    Sophus::SO3 SO3_v(0, 0, M_PI/  2); // Rotate 90 degrees around X-axis
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

    return 0;
}