#include <iostream>
#include <cmath>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

int main(int argc, char* argv[])
{
    Eigen::Matrix3d rotationMatrix = Eigen::Matrix3d::Identity();
    Eigen::AngleAxisd rotationVector(M_PI / 4, Eigen::Vector3d(0, 0, 1));

    std::cout.precision(3);
    std::cout << "rotation matrix = \n " << rotationVector.matrix() << "\n";

    rotationMatrix = rotationVector.toRotationMatrix();

    Eigen::Vector3d v(1, 0, 0);
    /* Coordinates rotated with angle axis rotation  */
    Eigen::Vector3d vRotated = rotationVector * v;
    
    std::cout << "(1, 0, 0) after rotation (by angle axis) = " << vRotated.transpose() << "\n";

    /* Coordinates rotated with rotation matrix */
    vRotated = rotationMatrix * v;
    std::cout << "(1, 0, 0) after rotation (by matrix) = " << vRotated.transpose() << "\n";

    /* Euler angle: convert rotation matrix directly to euler angles */
    /* ZYX order, ie roll pitch yaw */
    Eigen::Vector3d eulerAngles = rotationMatrix.eulerAngles(2, 1, 0);
    std::cout << "yaw pitch roll = " << eulerAngles.transpose() << "\n";

    /* Euclidean transformation matrix using Eigen::Isometry */
    /* It's a 4x4 matrix */
    Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
    /* Rotate according to rotationVector */
    T.rotate(rotationVector);
    /* Set the translation vector to (1, 3, 4) */
    T.pretranslate(Eigen::Vector3d(1, 3, 4));

    /* Use the transformation matrix for coordinate transformation */
    /* Equivalent to `R * v + t` */
    Eigen::Vector3d vTransformed = T * v;
    std::cout << "vTransformed = " << vTransformed.transpose() << "\n";

    /* For affine and projective transformations, use Eigen::Affine3d and Eigen::Projective3d */

    /* Quaternion */
    /* You can assign AngleAxis directly to Quaternions and vice verse */
    Eigen::Quaterniond q = Eigen::Quaterniond(rotationVector);
    std::cout << "quaternion from rotation vector = " << q.coeffs().transpose() << "\n";
    /* Note that the order of coeffs is (x, y, z, w), w is the real part, 
        and the first three are imaginary parts */

    /* We can also assign rotation matrix to it */
    q = Eigen::Quaterniond(rotationMatrix);
    std::cout << "quaternions from rotation matrix = " << q.coeffs().transpose() << "\n";

    /* Rotate a vector with a quaternion and use overloaded multiplication */
    /* Note that the math is $q v q^{-1}$ */
    vRotated = q * v;
    std::cout << "(1, 0, 0) after rotation = " << vRotated.transpose() << "\n";

    /* Expressed by regular vector multiplication, it should be calculated as follows */
    std::cout << "should be equal to " << (q * Eigen::Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().transpose() << "\n";

    return 0;
}