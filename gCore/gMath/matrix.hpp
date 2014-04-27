#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <vector>
#include <iostream>
#include "./op.hpp"

namespace gfx {

class Vec4;
class Vec3;
class Vec2;
class Qutn;

/** The Mat class may switch over to returning references if it gets too big.
    Also, once the datatype module is fixed, this should switch to using
    raw_mappable. */

/**
 * Represents a two dimensional array of 32bt floats.  May be of any dimension,
 * though Vectors assume dimensions of 2, 3, or 4.
 *
 * This class makes heavy use of the named constructor pattern.
 */
class Mat {
    public:
        // Creates an identity matrix of dimension 4x4
        // change this to a 4x4 matrix of 0s
        Mat() : cols(4),
                rows(4)
                { int i = 16;
                  while( i ){
                      e.push_back( 0.0f );
                      --i;
                  }
                };
        // fill with zeroes
        Mat( size_t nCols,
             size_t nRows );
        static Mat rotation4x4( Vec3 const& axis,
                                AngleD angle );
        static Mat rotation3x3( Vec3 const& axis,
                                AngleD angle );
        static Mat rotation3x3( Qutn const& aQutn );
        static Mat rotation4x4( AngleD xAngle,        
                                AngleD yAngle,
                                AngleD zAngle );
        static Mat rotation4x4( Vec3 rads );
        static Mat rotation4x4( Qutn const& aQutn );
        static Mat rotation3x3( AngleD xAngle,
                                AngleD yAngle,
                                AngleD zAngle );
//        static Mat rotation2D( float rads );
        static Mat translate( float x,
                              float y,
                              float z );
        static Mat scale4x4( float x,
                             float y,
                             float z );
//        static Mat scale3x3( float x, float y, float z );
//        static Mat scale2D( float x, float y );
        static Mat translate( Vec3 trans );
        static Mat scale4x4( Vec3 scale );
//        static Mat scale3x3( Vec3 scale );
//        static Mat scale2D( Vec2 scale );
        static Mat identity( size_t dim );
        static Mat upper_identity( size_t nCols,
                                   size_t nRows );
// this will use i - ( nRows - nCols) in the test for ones instead
//      static Mat lower_identity( size_t nCols, size_t nRows );
//        static Mat fill( size_t nCols, size_t nRows, float fill );
        static Mat col( Vec3 const& vec );
        static Mat row( Vec3 const& vec );
        static Mat cross_product( Vec3 const& vec );
        static Mat colVecs( Vec3 const& x,
                            Vec3 const& y,
                            Vec3 const& z );
        static Mat rowVecs( Vec3 const& x,
                            Vec3 const& y,
                            Vec3 const& z );
//        static Mat colVecs( Vec4 const& x, Vec4 const& y );
//            etc.
//        static Mat rowVecs( Vec4 const& x, Vec4 const& y );
//            etc.
        static Mat perspective( double fovY,
                                double aspect,
                                double near,
                                double far );
//        static Mat orthographic( /* blah blah */ );

        size_t nCols() const;
        size_t nRows() const;
        size_t size() const;

//        Mat const rowspan( int top, int bottom );
//        Mat const colspan( int left, int right );
//        Vec4 const row4( int row );
//        Vec3 const row3( int row );
//        Vec2 const row2( int row );
//        Vec4 const col4( int col );
//        Vec3 const col3( int col );
//        Vec2 const col2( int col );
        float& operator()( size_t col,
                           size_t row );
        float operator()( size_t col,
                          size_t row ) const;
        Mat operator*( Mat const& rhs );
        Mat operator+( Mat const& rhs );
        Mat operator-( Mat const& rhs );

        friend Mat operator*( float lhs,
                              Mat const& rhs );
        friend Mat operator*( Mat const& lhs,
                              float rhs );
        friend class Transpose;

        Mat& transpose();
        Mat& norm();
        // Expands the matrix to the minmally dimensioned square matrix
        // that has one column or row more than the matrix originally had.
        Mat& homogenize();

        float* toArray();

        friend std::ostream& operator<<( std::ostream& stream,
                                         Mat& src );
    private:
        size_t cols;
        size_t rows;
        std::vector<float> e;
};

std::ostream& operator<<( std::ostream& stream,
                          Mat& src );

}

#endif
