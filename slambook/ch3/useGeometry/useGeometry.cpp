#include <iostream>
#include <cmath>
using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>

int main()
{
    // Eigen/Geometry 模块提供了各种旋转和平移的表示方法，以下是一些常用的类型：
    // 3D Rotation Matrix (3x3)
    Eigen::Matrix3d R = Eigen::Matrix3d::Identity(); // Rotation matrix

    // Rotation Vector (Angle-Axis)
    Eigen::AngleAxisd rotation_vector(M_PI / 4, Eigen::Vector3d(0, 0, 1)); // Rotate 45 degrees around Z-axis
    cout.precision(3);
    R = rotation_vector.toRotationMatrix(); // Convert to rotation matrix
    cout << "Rotation Matrix from Angle-Axis:\n" << R << endl;

    // Use AngleAxis to rotate a vector
    Eigen::Vector3d v(1, 0, 0); // Original vector
    Eigen::Vector3d v_rotated = rotation_vector * v; // Rotate the vector
    cout << "Rotated Vector with Angle-Axis:\n" << v_rotated.transpose() << endl;

    v_rotated = R * v; // Rotate the vector using the rotation matrix
    cout << "Rotated Vector with Rotation Matrix:\n" << v_rotated.transpose() << endl;

    // Euler Angles (ZYX order)
    Eigen::Vector3d euler_angles = R.eulerAngles(2, 1, 0); // ZYX order
    cout << "Euler Angles (ZYX) in degrees:\n" << (euler_angles * 180.0 / M_PI).transpose() << endl;

    // Euler Transformation using Eigen::Isometry
    Eigen::Isometry3d T = Eigen::Isometry3d::Identity(); // Identity transformation, actually a 4x4 matrix
    T.rotate(rotation_vector); // Apply rotation
    cout << "Transformation Matrix (Isometry) before translation:\n" << T.matrix() << endl;
    
    T.pretranslate(Eigen::Vector3d(1, 2, 3)); // Apply the translation
    cout << "Transformation Matrix (Isometry) after translation:\n" << T.matrix() << endl;

    // Quaternion
    Eigen::Quaterniond q = Eigen::Quaterniond(rotation_vector); // Convert Angle-Axis to Quaternion
    cout << "Quaternion (w, x, y, z):\n" << q.coeffs().transpose() << endl; // Note: coeffs order is (x, y, z, w)

    v_rotated = q * v; // Rotate the vector using the quaternion
    cout << "Rotated Vector with Quaternion:\n" << v_rotated.transpose() << endl;

    return 0;
}