#include <iostream>
#include <cmath>

#include "./matrix.hpp"
#include "./vec.hpp"
#include "./op.hpp"

int main( int argc, char** argv )
{
    using namespace gfx;

    Mat mat1;
    Mat mat2 = Mat::upper_identity( 2, 3 );
    Mat mat3 = Mat::identity( 4 );
    Mat mat4 = Mat::identity( 4 );

    mat3(0,1) = 2.0f;
    mat3(3,2) = 1.5f;

    Vec3 vec3_1 ( 0.5f, 0.25f, -1.0f );
    Vec4 vec4_1 ( 0.5f,1.0f,1.5f,1.0f );

    using std::cout;
    using std::endl;

    cout << "Running Mat class diagnostic tests." << endl;
    cout << "4x4 Zero matrix." << endl;
    cout << mat1 << endl;
    cout << "4x4 Identity matrix." << endl;
    cout << mat4 << endl;
    cout << "Element at (2,2)." << endl;
    cout << mat4( 2, 2 ) << endl;
    cout << "Changed to 5." << endl;
    mat4( 2, 2 ) = 5.0f;
    cout << mat4( 2, 2 ) << endl;
    cout << mat4 << endl;
    cout << "Another 4x4." << endl;
    cout << mat3 << endl;
    cout << "The product of those two matrices." << endl;
    Mat mat5 = mat4 * mat3;
    cout << mat5 << endl;
    cout << "The sum of those two matrices." << endl;
    Mat mat6 = mat4 + mat3;
    cout << mat6 << endl;
    cout << "The difference of those two matrices." << endl;
    Mat mat7 = mat4 - mat3;
    cout << mat7 << endl;
    cout << "The first matrix times -3." << endl;
    Mat matScalar = -3.0f * mat4;
    cout << matScalar << endl;
    cout << "Second of those matrices times the vector <0.5,1,1.5,1>, <0.5,2,3,1>." << endl;
    Vec4 product = mat3 * vec4_1;
    cout << product << endl;
    cout << "Same thing, but the vector is swizzled in the call to <-0.5,-1,-1.5,-1>, <-0.5,-2,-3,-1>." << endl;
    Vec4 product2 = mat3 * vec4_1(-x,-y,-z,-w);
    cout << product2 << endl;
    cout << "Assymetric 2x3 matrix, upper diagonal with ones." << endl;
    cout << mat2 << endl;
    cout << "Some vaules changed." << endl;
    mat2( 0,0 ) = 2.0f;
    mat2( 0,2 ) = -1.0f;
    cout << mat2 << endl;
    cout << "That matrix transposed in place with return used as the output operand." << endl;
    cout << mat2.transpose() << endl;
    cout << "And to make sure the transposition stuck, print it again." << endl;
    cout << mat2 << endl;
    cout << "Now the copying version returns the original multipled by -1." << endl;
    Mat matTranspose = transpose( mat2 ) * -1.0f;
    cout << matTranspose << endl;
    cout << "Now we make that homogenous in place; the first is the matrix itself, the second is the return." << endl;
    Mat testMat = matTranspose.homogenize();
    cout << matTranspose << endl << endl;
    cout << testMat << endl;
    cout << "Forcing exception on multiplication." << endl;
    try {
        mat2 * mat3;
    } catch(std::exception& e){
        cout << "caught exception: " << e.what() << endl;
    }
    cout << "The cross product matrix of the vector <0.5,0.25,-1>." << endl;
    Mat crossMat = Mat::cross_product( vec3_1 );
    cout << crossMat << endl;
    cout << "The rotation matrix for rotating 45 degrees on x using the explicit formula." << endl;
    Vec3 xAxis (1.0f, 0.0f, 0.0f);
    Mat rotXMat = Mat::identity(3) * cos( M_PI_4 )
                     + (1.0f - cos( M_PI_4 )) * Mat::col(xAxis)*Mat::row(xAxis)
                     + Mat::cross_product( xAxis ) * sin( M_PI_4 );
    cout << rotXMat << endl;
    cout << "And via the named constructor with a column normalization." << endl;
    rotXMat = norm(Mat::rotation3x3( xAxis, AngleD::inRads(M_PI_4 )));
    cout << rotXMat << endl;
    cout << "And again with an in-place column normalization." << endl;
    rotXMat = Mat::rotation3x3( xAxis, AngleD::inRads(M_PI_4) ).norm();
    cout << rotXMat << endl;
    cout << "Now homogenize it with the external function." << endl;
    Mat h_rotXMat = homogenize( rotXMat );
    cout << h_rotXMat << endl;
    cout << "This time we make the 4x4 rotation matrix." << endl;
    rotXMat = Mat::rotation4x4( xAxis, AngleD::inRads(M_PI_4) ).norm();
    cout << rotXMat << endl;
    cout << "And again, but this time specifing the Euler angles as < 45, 90, 0 > degrees." << endl;
    rotXMat = Mat::rotation4x4( AngleD::inRads(M_PI_4), AngleD::inRads(M_PI_2), AngleD::inRads(0.0) );
    cout << rotXMat << endl;
    cout << "Tests complete." << endl;

    return 0;
}
