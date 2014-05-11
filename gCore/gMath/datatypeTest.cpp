#include <iostream>

//#include "type_op.hpp"
#include "../../UnitTest++_src/UnitTest++.h"
#include "datatype.hpp"
#include "swizzTest.hpp"

TEST( MatrixConstruction )
{
    std::cout << "MatrixConstruction" << std::endl;
    using namespace gfx;
    mat<float> amat(2,2);
    CHECK_EQUAL( amat.n_cols, 2u );
    CHECK_EQUAL( amat.n_rows, 2u );
    CHECK_EQUAL( amat.n_comp, 4u );
    mat<float> bmat(2,2);
    bmat(0,0) = 0.0f;
    bmat(0,1) = 0.0f;
    bmat(1,0) = 0.0f;
    bmat(1,1) = 0.0f;
    CHECK_EQUAL( amat, bmat );
}

TEST( MatrixFill )
{
    std::cout << "MatrixFill" << std::endl;
    using namespace gfx;
    mat<float> amat = mat<float>::fill( 2, 2, 4.5f );
    CHECK_EQUAL( amat.n_cols, 2u );
    CHECK_EQUAL( amat.n_rows, 2u );
    CHECK_EQUAL( amat.n_comp, 4u );
    mat<float> bmat(2,2);
    bmat(0,0) = 4.5f;
    bmat(0,1) = 4.5f;
    bmat(1,0) = 4.5f;
    bmat(1,1) = 4.5f;
    CHECK_EQUAL( amat, bmat );
}

TEST( MatrixIdentity )
{
    std::cout << "MatrixIdentity" << std::endl;
    using namespace gfx;
    mat<float> amat = mat<float>::identity( 2 );
    CHECK_EQUAL( amat.n_cols, 2u );
    CHECK_EQUAL( amat.n_rows, 2u );
    CHECK_EQUAL( amat.n_comp, 4u );
    mat<float> bmat(2,2);
    bmat(0,0) = 1.0f;
    bmat(0,1) = 0.0f;
    bmat(1,0) = 0.0f;
    bmat(1,1) = 1.0f;
    CHECK_EQUAL( amat, bmat );
}

TEST( MatrixAssignment )
{
    std::cout << "MatrixAssignment" << std::endl;
    using namespace gfx;
    mat<float> amat(2,2);
    mat<float> bmat(2,2);
    bmat(0,0) = 14.5f;
    bmat(0,1) = -7.01f;
    bmat(1,0) = 100.5f;
    bmat(1,1) = -234.52f;
    CHECK( amat != bmat );
    amat = bmat;
    CHECK_EQUAL( amat, bmat );
    CHECK_EQUAL( amat.n_comp, bmat.n_comp );
    mat<float> cmat = amat;
    bmat(0,1) = 67.3f;
    CHECK( amat != bmat );
    CHECK_EQUAL( amat, cmat ); // no side effects
}

TEST( MatrixLookup )
{
    std::cout << "MatrixLookup" << std::endl;
    using namespace gfx;
    mat<float> amat(2,2);
    amat(0,0) = 23.0f;
    amat(0,1) = 438.4f;
    amat(1,0) = -0.00231f;
    amat(1,1) = -2.98f;
    CHECK_EQUAL( amat(0,0), 23.0f );
    CHECK_EQUAL( amat(0,1), 438.4f );
    CHECK_EQUAL( amat(1,0), -0.00231f );
    CHECK_EQUAL( amat(1,1), -2.98f );
}

TEST( MatrixAddition )
{
    std::cout << "MatrixAddition" << std::endl;
    using namespace gfx;
    mat<float> amat(2,2);
    //mat<float> bmat(2,2);
    //bmat(0,0) = 14.5f;
    //bmat(0,1) = -7.01f;
    //bmat(1,0) = 100.5f;
    //bmat(1,1) = -234.52f;
    //CHECK( amat != bmat );
    std::cout << amat << std::endl;
    mat<float> cmat;
    std::cout << "The error starts here" << std::endl;
    std::cout << "amat.n_cols: " << amat.n_cols; 
    std::cout << " amat.n_rows: " << amat.n_rows;
    std::cout << " amat.n_comp: " << amat.n_rows << std::endl;
    
    std::cout << "cmat.n_cols: " << cmat.n_cols; 
    std::cout << " cmat.n_rows: " << cmat.n_rows;
    std::cout << " cmat.n_comp: " << cmat.n_rows << std::endl;
    
    cmat = amat;
    std::cout << "Not here." << std::endl;
    //cmat = amat + bmat;
    //CHECK_EQUAL( cmat, bmat );
}

TEST( Matrix2Construction )
{
    std::cout << "Matrix2Construction" << std::endl;
    using namespace gfx;
    fmat2 amat2;
    fmat2 bmat2( 0.0f, 0.0f,
                 0.0f, 0.0f );
    CHECK_EQUAL( amat2, bmat2 );
}

TEST( Matrix2Identity )
{
    std::cout << "Matrix2Identity" << std::endl;
    using namespace gfx;
    fmat2 amat2 = fmat2::identity();
    fmat2 bmat2( 1.0f, 0.0f,
                 0.0f, 1.0f );
    CHECK_EQUAL( amat2, bmat2 );
}

TEST( Matrix3Construction )
{
    std::cout << "Matrix3Construction" << std::endl;
    using namespace gfx;
    fmat3 amat3;
    fmat3 bmat3( 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f );
    CHECK_EQUAL( amat3, bmat3 );
}

TEST( Matrix3Identity )
{
    std::cout << "Matrix3Identity" << std::endl;
    using namespace gfx;
    fmat3 amat3 = fmat3::identity();
    fmat3 bmat3( 1.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 1.0f );
    CHECK_EQUAL( amat3, bmat3 );
}

TEST( Matrix4Construction )
{
    std::cout << "Matrix4Construction" << std::endl;
    using namespace gfx;
    fmat4 amat4;
    fmat4 bmat4( 0.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 0.0f );
    CHECK_EQUAL( amat4, bmat4 );
}

TEST( Matrix4Identity )
{
    std::cout << "Matrix4Identity" << std::endl;
    using namespace gfx;
    fmat4 amat4 = fmat4::identity();
    fmat4 bmat4( 1.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f );
    CHECK_EQUAL( amat4, bmat4 );
}

int main( int argc, char** argv )
{
    return UnitTest::RunAllTests();
}
