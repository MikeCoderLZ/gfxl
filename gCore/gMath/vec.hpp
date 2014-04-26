#ifndef VEC_HPP
#define VEC_HPP

#include <iostream>
#include "../gUtility/utility.hpp"

/**
 * This header declares the interface for the vector clas, gfx::Vec.  Along
 * with the operator classes, gfx::Vec is one of the most complicated bits of
 * code in this collection so far.
 *
 * Here's a less techie explanation than you'll find in the comments:
 *
 * Modern shading languages deal in linear algebra to make lighting and
 * rendering algorithms easier to write.  One feature of these languages
 * that does just that is the "component swizzle", whereby a vector type's
 * components can be accessed via suffixed parameters:
 *
 * // Two, four component vectors
 * float4 a_vector (1.0, 2.0, 0.0, 3.0);
 * float4 b_vector (0.0, 0.5, 1.0, 0.0);
 *
 * a_vector.x; // value of 1.0
 *
 * Swizzles can also be used to create an expression with a vector type value:
 *
 * b_vector.xy; // value of <0.0, 0.5>
 *
 * And they don't care about the order:
 *
 * a_vector.yzzx; // value of <2.0, 0.0, 0.0, 1.0>
 *
 * That was the major problem I wanted to tackle with this vector class: how
 * to implement swizzle functionality in C++.
 *
 * Now it gets wordy.
 *
 * The solution creates a hierarchy of swizzle classes that runs counter
 * to one's intuition.  The swizzle class for the fourth component is the
 * base class and the other swizzles derive from it.  the vector types themselves
 * can take swizzle objects as arguments in an overloaded functional operator.
 * The number of arguments in the operator indicates the number of components of
 * the returned vector and the number of components of this vector indicates
 * the type of swizzle that can be used.
 *
 * So a Vec2 can use Vec2Swizzles to construct Vec2's, Vec3's, and Vec4's.
 *
 * However, the swizzles are not something that the user is meant to play with;
 * being able to alter the swizzles themselves would make the code unreadable.
 * So in order to simulate the presence of a "feature", the ability to make
 * instances of swizzles is restricted to a factory class whose implementation
 * _and_ definition exists only in the implementation file of this header, vec.cpp.
 * The valid swizzles ( x,y,z,w; u,v,s,t; r,g,b,a; i,j,k,m ) are declared here and then
 * given values by the factory class in the implementation file.  Finally, the
 * default initialization of a Swizzle contains a value that will cause an
 * exception if it is ever used.
 *
 * In the end, all that insanity gets you this:
 *
 * Vec2 aVec (2.0f, 1.5f);
 *
 * Vec3 bVec = aVec(x, y, x);
 *
 * std::cout << bVec << std::endl; // prints "<2.0f, 1.5f, 2.0f>"
 *
 * The comments below are more technical and dry, so I hope that gets the idea
 * across.
 * */

namespace gfx {

/* Swizzles need to be recognized by any function that takes vectors as its
 * operands as unit vectors along that swizzle's axis.  That enchances the
 * feel of a feature.
 */

/**
 * A class implemented in the cpp file; no other translation unit knows about
 * its details. Its purpose is to serve as the sole generator of swizzle
 * objects since it contains the only code allowed access to the useful
 * constructors of the swizzle classes.
 */
class SwizzleFactory;

class Vec2;
class Vec3;
class Vec4;
class Qutn;

/**
 * A vector component swizzler for four-component vectors.  Swizzlers allow
 * indexing of components by name instead of integers.  They also allow
 * indexing to return a vector of lower or even higher order by taking
 * components and indicating how they are rearranged.
 *
 * This swizzler is for four component vectors; all the other swizzlers are
 * derived from it.  Since we cannot add actual language features, we need
 * to simulate them by using tricks such as inheritance to catch compiler
 * errors.  Deriving the swizzlers for the lower components (x and y, for
 * instance) means that a Vec2 can restrict swizzles to only one that apply
 * to its components and not those of a Vec4.  If the hierarchy worked the
 * other way, which seems like the logical choice, a Vec2 would try to use
 * a swizzle for the 4th component if given it, which would result in very
 * bad things.
 *
 * Since the intention is to use named constants so that code reads like
 * " aVec( x, y, z); ", we want to restrict construction of the swizzles
 * to module controlled code, not user code.  The SwizzleFactory does this
 * since it is the only class that has access to the constructors of the
 * swizzles that can actually set the internal values needed to index
 * correctly.
 *
 * Negating a swizzle is possible and indicates that the indexing should flip
 * the sign of any components it accesses.
 *
 * The subscript operator does not anywhere have the ability to use swizzles
 * for the reason that it confuses the two indexing methods.Some types that
 * use indexing may have arbitrary size, at which point the purposeful swizzles
 * do not apply in any rational way.  Furthermore, subscript indexing is
 * integer based, and where it has been implemented negative indices mean that
 * the indexing should start from the end of the components; making a decision
 * between that and flipping the sign of the value indexed makes the interface
 * inconsistent and unpredictable.
 *
 * At some point, I will add versions of functions that take a vector as
 * one of the operands which recognize the swizzles as represenative of
 * the unit axes of their names.  This enhances the feeling of a "feature".
 * Also, I want to change the names of the classes so that the error messages
 * on compilation are more readable.
 *
 * Swizz4 can index any of four components, but only the constants
 * 'w', 'a', 'q', and 'm' are instances of the class.
 */
class Swizz4 {
    public:
        Swizz4() : index(0) {};
        friend Swizz4 operator-( Swizz4 const& rhs );
        friend class Vec2;
        friend class Vec3;
        friend class Vec4;
        friend class Qutn;
        friend class SwizzleFactory;
    private:
        Swizz4( int index );
    protected:
        int index;
};

Swizz4 operator-(Swizz4 const& rhs);

/**
 * The swizzle class for Vec3's.  The constants 'z', 'b', 'p', and 'k' are
 * instances of this swizzle.
 */
class Swizz3 : public Swizz4 {
    public:
        Swizz3() {};
        friend Swizz3 operator-( Swizz3 const& rhs );
        friend class Vec2;
        friend class Vec3;
        friend class Vec4;
        friend class Qutn;
        friend class SwizzleFactory;
    private:
        Swizz3( int index );
};

Swizz3 operator-(Swizz3 const& rhs);

/**
 * A swizzle for Vec2's.  'x', 'y', 'r', 'g', 's', 't', 'i', and 'j' are the
 * instances of this swizzle.
 */
class Swizz2 : public Swizz3 {
    public:
        Swizz2() {};
        friend Swizz2 operator-( Swizz2 const& rhs );
        friend class Vec2;
        friend class Vec3;
        friend class Vec4;
        friend class Qutn;
        friend class SwizzleFactory;
    private:
        Swizz2( int index );
};

Swizz2 operator-(Swizz2 const& rhs);

// Classical Components
extern Swizz2 const x;
extern Swizz2 const y;
extern Swizz3 const z;
extern Swizz4 const w;
// Texture Coordinates
extern Swizz2 const s;
extern Swizz2 const t;
extern Swizz3 const p;
extern Swizz4 const q;
// Color Coordinates
extern Swizz2 const r;
extern Swizz2 const g;
extern Swizz3 const b;
extern Swizz4 const a;
// Hamiltonian Coordinates
//( quaternions use these and they are the source names of the internal fields in all
//  vector classes )
extern Swizz2 const i;
extern Swizz2 const j;
extern Swizz3 const k;
extern Swizz4 const m;

/**
 * A two component vector.  Subscripting uses integer indexing, while
 * parenthetical access uses swizzles.  Currently cannot construct
 * vectors of a higher order than itself.  Supports stream output.
 *
 * Default values are <0.0f, 0.0f>.
 */
class Vec2 {
    public:
        Vec2() : c0(0.0f),
                 c1(0.0f) {};
        Vec2( float x0,
              float x1 );
        Vec2( float fill );
        float& operator[]( int index );
        float operator[]( int index ) const;
        float& operator()( Swizz2 const& comp );
        float operator()( Swizz2 const& comp ) const;
        Vec2 operator()( Swizz2 const& x0,
                         Swizz2 const& x1 ) const;
        Vec3 operator()( Swizz2 const& x0,
                         Swizz2 const& x1,
                         Swizz2 const& x2 ) const;
        Vec4 operator()( Swizz2 const& x0,
                         Swizz2 const& x1,
                         Swizz2 const& x2,
                         Swizz2 const& x3 ) const;
        Vec2 operator+( Vec2 const& rhs ) const;
        Vec2 operator-( Vec2 const& rhs ) const;
        Vec2 operator*( Vec2 const& rhs ) const;
        Vec2 operator/( Vec2 const& rhs ) const;

        Vec2& norm();

        friend type::Layout const& type::info<gfx::Vec2>();
        friend std::ostream& operator<<( std::ostream& out,
                                         Vec2 const& rhs );
    private:
        static type::Layout layout = type::Vec2;
        float c0;
        float c1;
};

std::ostream& operator<<( std::ostream& out,
                          Vec2 const& rhs );

/**
 * A three component vector.  Subscripting uses integer indexing, while
 * parenthetical access uses swizzles.  Currently cannont construct
 * vectors of a higher order than itself.  Supports stream output.
 *
 * Default values are <0.0f, 0.0f, 0.0f>.
 */

class Vec3 {

    public:
        Vec3() : c0(0.0f),
                 c1(0.0f),
                 c2(0.0f) {};
        Vec3( Vec3 const& src );
        Vec3( float x0,
              float x1,
              float x2 );
        Vec3( float fill );
        float& operator[]( int index );
        float operator[]( int index ) const;
        float& operator()( Swizz3 const& comp );
        float operator()( Swizz3 const& comp ) const;
        Vec2 operator()( Swizz3 const& x0,
                         Swizz3 const& x1 ) const;
        Vec3 operator()( Swizz3 const& x0,
                         Swizz3 const& x1,
                         Swizz3 const& x2 ) const;
        Vec4 operator()( Swizz3 const& x0,
                         Swizz3 const& x1,
                         Swizz3 const& x2,
                         Swizz3 const& x3 ) const;
        Vec3 operator+( Vec3 const& rhs ) const;
        Vec3 operator-( Vec3 const& rhs ) const;
        Vec3 operator*( Vec3 const& rhs ) const;
        Vec3 operator/( Vec3 const& rhs ) const;

        Vec3& norm();
        friend type::Layout const& type::info<gfx::Vec3>();
        friend class Vec4;
        friend std::ostream& operator<<( std::ostream& out,
                                         Vec3 const& rhs );
    private:
        static type::Layout layout = type::Vec3;
        float c0;
        float c1;
        float c2;
};

std::ostream& operator<<( std::ostream& out,
                          Vec3 const& rhs );

/**
 * A four component vector.  Subscripting uses integer indexing, while
 * parenthetical access uses swizzles.  Currently cannot construct
 * vectors of a higher order than itself.  Supports stream output.
 *
 * Default values are <0.0f, 0.0f>.
 */

class Vec4 {

    public:
        Vec4() : c0(0.0f),
                 c1(0.0f),
                 c2(0.0f),
                 c3(0.0f) {};
        Vec4( float x0,
              float x1,
              float x2,
              float x3 );
        Vec4( float fill );
        float& operator[]( int index );
        float operator[]( int index ) const;
        float& operator()( Swizz4 const& comp );
        float operator()( Swizz4 const& comp ) const;
        Vec2 operator()( Swizz4 const& x0,
                         Swizz4 const& x1 ) const;
        Vec3 operator()( Swizz4 const& x0,
                         Swizz4 const& x1,
                         Swizz4 const& x2 ) const;
        Vec4 operator()( Swizz4 const& x0,
                         Swizz4 const& x1,
                         Swizz4 const& x2,
                         Swizz4 const& x3 ) const;
        Vec4 operator+( Vec4 const& rhs ) const;
        Vec4 operator-( Vec4 const& rhs ) const;
        Vec4 operator*( Vec4 const& rhs ) const;
        Vec4 operator/( Vec4 const& rhs ) const;

        Vec4& norm();

        friend type::Layout const& type::info<gfx::Vec4>();
        friend std::ostream& operator<<( std::ostream& out,
                                         Vec4 const& rhs );
    private:
        static type::Layout layout = type::Vec4;
        float c0;
        float c1;
        float c2;
        float c3;
};

std::ostream& operator<<( std::ostream& out,
                          Vec4 const& rhs );

}

#endif
