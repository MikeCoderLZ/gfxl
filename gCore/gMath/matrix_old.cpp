#include <stdexcept>
#include <cmath>

#include "./quaternion.hpp"
#include "./matrix.hpp"
#include "./vec.hpp"
#include "./op.hpp"

namespace gfx {

Mat::Mat( size_t nCols,
          size_t nRows )
{
    cols = nCols;
    rows = nRows;

    size_t i = 0;

    for( i = 0; i < nCols * nRows; ++i ){
        e.push_back(0.0f);
    }

}

Mat Mat::rotation4x4( Vec3 const& axis,
                      AngleD angle )
{
    double rads = angle.toRads();
    // The upper 3x3 matrix that represents the rotation.
    Mat upper_out = Mat::identity(3) * cos(rads)
                       + (1.0f - cos(rads)) * Mat::col(axis) * Mat::row(axis)
                       + Mat::cross_product(axis) * sin(rads);
    upper_out.homogenize();
    return upper_out;
}

Mat Mat::rotation3x3( Vec3 const& axis,
                      AngleD angle )
{
    double rads = angle.toRads();
    return Mat::identity(3) * cos(rads)
           + (1.0f - cos(rads)) * Mat::col(axis) * Mat::row(axis)
           + Mat::cross_product(axis) * sin(rads);
}

Mat Mat::rotation3x3( Qutn const& aQutn )
{
    double ii = aQutn(i) * aQutn(i);
    double ij = aQutn(i) * aQutn(j);
    double ik = aQutn(i) * aQutn(k);
    double im = aQutn(i) * aQutn(m);

    double jj = aQutn(j) * aQutn(j);
    double jk = aQutn(j) * aQutn(k);
    double jm = aQutn(j) * aQutn(m);

    double kk = aQutn(k) * aQutn(k);
    double km = aQutn(k) * aQutn(m);

    Mat out = Mat(3,3);

    out(0,0) = 0.5F - ( jj + kk );
    out(0,1) = ij + km;
    out(0,2) = ik - jm;

    out(1,0) = ij - km;
    out(1,1) = 0.5F - ( ii + kk );
    out(1,2) = jk + im;

    out(2,0) = ik + jm;
    out(2,1) = jk - im;
    out(2,2) = 0.5F - ( ii + jj );

    out = 2.0f * out;

    return out;
}

Mat Mat::rotation4x4( AngleD xAngle,
                      AngleD yAngle,
                      AngleD zAngle )
{
    Mat out = Mat::identity( 3 );
    
    double xRads = xAngle.toRads();
    double yRads = yAngle.toRads();
    double zRads = zAngle.toRads();

    if( xRads != 0.0f ){
        out = out * Mat::rotation3x3( Vec3( 1.0f, 0.0f, 0.0f), xAngle);
    }
    if( yRads != 0.0f ){
        out = out * Mat::rotation3x3( Vec3( 0.0f, 1.0f, 0.0f), yAngle);
    }
    if( zRads != 0.0f ){
        out = out * Mat::rotation3x3( Vec3( 0.0f, 0.0f, 1.0f), zAngle);
    }

    return out.homogenize();
}

Mat Mat::rotation4x4( Vec3 rads )
{
    Mat out = Mat::identity( 3 );

    if( rads[0] != 0.0f ){
        out = out * Mat::rotation3x3( Vec3( 1.0f, 0.0f, 0.0f), AngleD::inRads(rads[0]));
    }
    if( rads[1] != 0.0f ){
        out = out * Mat::rotation3x3( Vec3( 0.0f, 1.0f, 0.0f), AngleD::inRads(rads[1]));
    }
    if( rads[2] != 0.0f ){
        out = out * Mat::rotation3x3( Vec3( 0.0f, 0.0f, 1.0f), AngleD::inRads(rads[2]));
    }

    return out.homogenize();
}

Mat Mat::rotation4x4( Qutn const& aQutn )
{
    return Mat::rotation3x3( aQutn ).homogenize();
}

Mat Mat::rotation3x3( AngleD xAngle,
                      AngleD yAngle,
                      AngleD zAngle )
{
    Mat out = Mat::identity( 3 );

    double xRads = xAngle.toRads();
    double yRads = yAngle.toRads();
    double zRads = zAngle.toRads();
    
    if( xRads != 0.0f ){
        out = out * Mat::rotation3x3( Vec3( 1.0f, 0.0f, 0.0f), xAngle);
    }
    if( yRads != 0.0f ){
        out = out * Mat::rotation3x3( Vec3( 0.0f, 1.0f, 0.0f), yAngle);
    }
    if( zRads != 0.0f ){
        out = out * Mat::rotation3x3( Vec3( 0.0f, 0.0f, 1.0f), zAngle);
    }

    return out;
}

Mat Mat::translate( float x,
                    float y,
                    float z )
{
    Mat out = Mat::identity(4);

    out(3, 0) = x;
    out(3, 1) = y;
    out(3, 2) = z;

    return out;
}

Mat Mat::scale4x4( float x,
                   float y,
                   float z )
{
    Mat out = Mat::identity(4);

    out( 0, 0 ) = x;
    out( 1, 1 ) = y;
    out( 2, 2 ) = z;

    return out;
}

Mat Mat::identity( size_t dim )
{
    Mat out (dim, dim);

    size_t i = 0;
    size_t stride = dim + 1;

    for( i = 0; i < dim * dim; ++i ){
        if( i % stride ){
            out.e[i] = 0.0f;
        } else {
            out.e[i] = 1.0f;
        }
    }
    return out;
}

Mat Mat::scale4x4( Vec3 scale )
{
    Mat out = Mat::identity(4);

    out( 0, 0 ) = scale[0];
    out( 1, 1 ) = scale[1];
    out( 2, 2 ) = scale[2];

    return out;
}

Mat Mat::translate( Vec3 trans )
{
    Mat out = Mat::identity(4);

    out(3, 0) = trans[0];
    out(3, 1) = trans[1];
    out(3, 2) = trans[2];

    return out;
}


Mat Mat::upper_identity( size_t nCols,
                         size_t nRows )
{
    Mat out (nCols, nRows);

    size_t i = 0;
    size_t stride = nRows + 1;

    for( i = 0; i < nCols * nRows; ++i ){
        if( i % stride ){
            out.e[i] = 0.0f;
        } else {
            out.e[i] = 1.0f;
        }
    }
    return out;
}

Mat Mat::col( Vec3 const& vec )
{
    Mat out ( 1, 3 );

    out( 0, 0 ) = vec[0];
    out( 0, 1 ) = vec[1];
    out( 0, 2 ) = vec[2];

    return out;
}

Mat Mat::row( Vec3 const& vec )
{
    Mat out ( 3, 1 );

    out( 0, 0 ) = vec[0];
    out( 1, 0 ) = vec[1];
    out( 2, 0 ) = vec[2];

    return out;
}

Mat Mat::cross_product( Vec3 const& vec )
{
    Mat out (3, 3);

    out( 1, 0 ) = -vec[2];
    out( 2, 0 ) =  vec[1];
    out( 0, 1 ) =  vec[2];
    out( 2, 1 ) = -vec[0];
    out( 0, 2 ) = -vec[1];
    out( 1, 2 ) =  vec[0];

    return out;
}

Mat Mat::colVecs( Vec3 const& x,
                  Vec3 const& y,
                  Vec3 const& z )
{
    Mat out (3,3);
    
    out(0,0) = x[0];
    out(0,1) = x[1];
    out(0,2) = x[2];
    out(1,0) = y[0];
    out(1,1) = y[1];
    out(1,2) = y[2];
    out(2,0) = z[0];
    out(2,1) = z[1];
    out(2,2) = z[2];
    return out;
}

Mat Mat::rowVecs( Vec3 const& x,
                  Vec3 const& y,
                  Vec3 const& z )
{
    Mat out (3,3);
    
    out(0,0) = x[0];
    out(1,0) = x[1];
    out(2,0) = x[2];
    out(0,1) = y[0];
    out(1,1) = y[1];
    out(2,1) = y[2];
    out(0,2) = z[0];
    out(1,2) = z[1];
    out(2,2) = z[2];
    return out;
}

Mat Mat::perspective( double fovY,
                      double aspect,
                      double near,
                      double far )
{
    Mat out = Mat( 4, 4 );

    double invTopTan = 1.0 / tan( fovY * 0.5);
    double invRightTan = invTopTan / aspect;
    double invFLessN = 1.0 / ( far - near );

    out( 0, 0 ) = (float) invRightTan;
    out( 1, 1 ) = (float) invTopTan;
    out( 2, 2 ) = (float) -(far + near) * invFLessN;
    out( 3, 2 ) = (float) -(2.0*far*near) * invFLessN;
    out( 2, 3 ) = -1.0f;
    out( 3, 3 ) = 0.0f;

    return out;
}

size_t Mat::nCols() const
{
    return cols;
}

size_t Mat::nRows() const
{
    return rows;
}

size_t Mat::size() const
{
    return cols * rows;
}

float& Mat::operator()( size_t col,
                        size_t row )
{
    return e[ col * rows + row ]; 
}

float Mat::operator()( size_t col,
                       size_t row ) const
{
    return e[ col * rows + row ];
}

Mat Mat::operator*( Mat const& rhs )
{
    if( cols != rhs.rows ){
        throw std::invalid_argument("row, column mismatch on multiplication.");
    }

    size_t element = 0;
    size_t addend = 0;

    float sum = 0.0f;

    Mat out( this->rows, rhs.cols );

    for( element = 0; element < rows * rhs.cols; ++element ){
        for( addend = 0; addend < cols; ++addend ){
            sum += (*this)( addend, element % rows ) * rhs( element / rows, addend );
        }
        out.e[element] = sum;
        sum = 0.0f;
    }

    return out;
}

Mat Mat::operator+( Mat const& rhs )
{
    if( cols != rhs.cols || rows != rhs.rows ){
        throw std::invalid_argument("matrices not dimensionally similar on addition.");
    }

    std::vector<float>::size_type i = 0;
    std::vector<float>::size_type nElements = e.size();

    Mat out( cols, rows );

    for( i = 0; i < nElements; ++i ){
        out.e[i] = e[i] + rhs.e[i];
    }

    return out;
}

Mat Mat::operator-( Mat const& rhs )
{
    if( cols != rhs.cols || rows != rhs.rows ){
        throw std::invalid_argument("matrices not dimensionally similar on subtraction.");
    }

    std::vector<float>::size_type i = 0;
    std::vector<float>::size_type nElements = e.size();

    Mat out( cols, rows );

    for( i = 0; i < nElements; ++i ){
        out.e[i] = e[i] - rhs.e[i];
    }

    return out;
}

Mat& Mat::transpose()
{
   
    // we make a new std::vector to store the new matrix info
    std::vector<float> newElements;

    size_t i = 0;
    size_t nElements = cols * rows;
    
    for( i = 0; i < nElements; ++i ){
        newElements.push_back( (*this)( i % cols, i / cols ) );
    }

    // Replace the std::vector with the new transposed one
    this->e = newElements;

    // By flipping the dimensions, we change the indexing to
    // the transpose's indexing
    size_t tempCols = this->cols;
    this->cols = this->rows;
    this->rows = tempCols;

    return *this;
}

Mat& Mat::norm()
{
    size_t row = 0;
    size_t col = 0;

    double temp = 0.0;
    double invColMag = 0.0;

    for( col = 0; col < cols; ++col ){
        for( row = 0; row < rows; ++row ){
            temp = e[ col * rows + row];
            invColMag += temp * temp;
        }
        invColMag = 1.0 / sqrt( invColMag );
        for( row = 0; row < rows; ++row ){
            // Using '*=' here would prematuring truncate the operation by
            // truncating invColMag before the multiplication is done and
            // does not promote the element in question first.            
            e[ col * rows + row] = e[ col * rows + row] * invColMag;
        }
        invColMag = 0.0;
    }
    return (*this);
}

Mat& Mat::homogenize()
{
    size_t dim = 0;

    if( rows >= cols ){
        dim = rows + 1;
    } else {
        dim = cols + 1;
    }

    Mat out = Mat::identity( dim );
    size_t size = dim * dim;

    size_t i = 0;

    bool colOutside = false;
    bool rowOutside = false;

    for( i = 0; i < size; ++i ){
        colOutside = i / dim >= cols;
        rowOutside = i % dim >= rows;
        if( colOutside && rowOutside ){
            // current indices are both outside the original,
            // so we can stop
            break;
        } else if ( !(colOutside || rowOutside) ){
            // both indices are inside, so copy
            out.e[i] = (*this)( i / dim, i % dim );
        }
        // do nothing if only one index is outside
    }
    // Copy the elements
    this->e = out.e;
    // Set the dimensions
    this->cols = dim;
    this->rows = dim;

    return *this;
}

float* Mat::toArray()
{
    float* elements = new float [ this->size() ];

    std::vector<float>::iterator element;

    size_t i = 0;

    for( element = e.begin(); element < e.end(); ++element ){
        elements[i] = *element;
        ++i;
    }
    return elements;
}

std::ostream& operator<<( std::ostream& stream, Mat& src )
{
    size_t i = 0;
    size_t j = 0;

    for( i = 0; i < src.rows; ++i ){
        stream << "[ ";
        for( j = 0; j < src.cols; ++j ){
            stream << src.e[ j * src.rows + i ] << " ";
        }
        stream << "]";
        // this makes sure the formatting behaves like other types
        if( i + 1 != src.rows && j + 1 != src.cols ){
             stream << std::endl;
        }
    }
    return stream;
}

}
