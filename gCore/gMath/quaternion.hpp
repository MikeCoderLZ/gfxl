#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <cstddef>
#include <ostream>
#include "./vec.hpp"
#include "./op.hpp"

namespace gfx {

class Mat;

  class Qutn {
      public:
          Qutn() : c0(0.0f),
                   c1(0.0f),
                   c2(0.0f),
                   c3(1.0f) {};
          Qutn( float fill );
          Qutn( float q0,
                float q1,
                float q2,
                float q3 );
          static Qutn pure( Vec3 const& point );
//          static Qutn axisAngle( Vec3 const& axis,
//                                 double rads );
          static Qutn axisAngle( Vec3 const& axis,
                                 AngleD angle );
          static Qutn rotationMat( Mat const& aMat );
          float& operator[]( size_t index );
          float operator[]( size_t index ) const;
          float& operator()( Swizz4 const& comp );
          float operator()( Swizz4 const& comp ) const;
          Qutn operator+( Qutn const& rhs ) const;
          Qutn operator-( Qutn const& rhs ) const;
          Qutn operator*( Qutn const& rhs ) const;
          Qutn operator/( Qutn const& rhs ) const;
          friend Qutn operator-( Qutn const& rhs );
          friend std::ostream& operator<<( std::ostream& out, Qutn const& rhs );
          Qutn& norm();
      private:
          float c0;
          float c1;
          float c2;
          float c3;
  };

  Qutn operator-( Qutn const& rhs );
  std::ostream& operator<<( std::ostream& out, Qutn const& rhs );

}
// end namespace GFX

#endif
