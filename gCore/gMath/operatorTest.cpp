#include <iostream>
#include <cmath>

#include "../../UnitTest++_src/UnitTest++.h"
#include "./datatype.hpp"
#include "./op.hpp"

SUITE( NormTests )
{
    TEST( NormVec4 )
    {
        using namespace gfx;
        fvec4 avec4 ( 1.0f, 1.0f, 1.0f, 1.0f );
        fvec4 bvec4 = norm( avec4 );
        fvec4 cvec4 ( 0.5f, 0.5f, 0.5f, 0.5f );
        CHECK_EQUAL( cvec4, bvec4 );
    }
    
    TEST( NormVec3 )
    {
        using namespace gfx;
        fvec3 avec3 ( 2.0f, 1.0f, 2.0f );
        fvec3 bvec3 = norm( avec3 );
        fvec3 cvec3 ( 2.0/3.0, 1.0/3.0, 2.0/3.0 );
        CHECK_EQUAL( cvec3, bvec3 );
    }
    
    TEST( NormVec2 )
    {
        using namespace gfx;
        fvec2 avec2 ( 4.0f, 3.0f );
        fvec2 bvec2 = norm( avec2 );
        fvec2 cvec2 ( 4.0/5.0, 3.0/5.0 );
        CHECK_EQUAL( cvec2, bvec2 );
    }
    
    TEST( NormMat )
    {
        using namespace gfx;
        fmat amat( 2,2 );
        amat(0,0) = 4.0f;
        amat(0,1) = 3.0f;
        amat(1,0) = 1.0f;
        fmat bmat = norm( amat );
        fmat cmat( 2,2 );
        cmat(0,0) = 4.0/5.0;
        cmat(0,1) = 3.0/5.0;
        cmat(1,0) = 1.0;
        
        CHECK_EQUAL( cmat, bmat );
    }
    
    TEST( NormQutn )
    {
        using namespace gfx;
        fqutn aqutn ( 1.0f, 1.0f, 1.0f, 1.0f );
        fqutn bqutn = norm( aqutn );
        fqutn cqutn ( 0.5f, 0.5f, 0.5f, 0.5f );
        CHECK_EQUAL( cqutn, bqutn );
    }
}

SUITE( OrthogonalizeTests )
{
    TEST( OrthoVec3 )
    {
        using namespace gfx;
        fvec3 avec3 ( 1.0f, 0.0f, 0.0f );
        fvec3 bvec3 ( 3.0f, 4.0f, 0.0f );
        fvec3 cvec3 = ortho( avec3, bvec3 );
        fvec3 dvec3 ( 0.0f, 4.0f, 0.0f );
        CHECK_EQUAL( dvec3, cvec3 );        
    }
}

SUITE( OuterProductTests )
{
    TEST( OuterProductVec3 )
    {
        using namespace gfx;
        fvec3 avec3 ( 1.0f, 0.0f, 0.0f);
        fvec3 bvec3 ( 0.0f, 1.0f, 0.0f);
        fvec3 cvec3 = cross( avec3, bvec3 );
        fvec3 dvec3 ( 0.0f, 0.0f, 1.0f );
        CHECK_EQUAL( dvec3, cvec3 );
    }
}

SUITE( ThresholdTests )
{
    TEST( ThreshVec4 )
    {
        using namespace gfx;
        fvec4 avec4 ( 2.5f, -1.0f, 7.0f, -18.0f );
        fvec4 bvec4 ( 8.0f, 4.0f, -6.0f, 17.0f );
        fvec4 cvec4 = mix_th( avec4, bvec4, 0.4f );
        CHECK_EQUAL( avec4, cvec4 );
    }
    
    TEST( ThreshVec3 )
    {
        using namespace gfx;
        fvec3 avec3 ( 2.5f, -1.0f, 7.0f );
        fvec3 bvec3 ( 8.0f, 4.0f, -6.0f );
        fvec3 cvec3 = mix_th( avec3, bvec3, 0.4f );
        CHECK_EQUAL( avec3, cvec3 );
    }
    TEST( ThreshVec2 )
    {
        using namespace gfx;
        fvec2 avec2 ( 2.5f, -1.0f );
        fvec2 bvec2 ( 8.0f, 4.0f );
        fvec2 cvec2 = mix_th( avec2, bvec2, 0.4f );
        CHECK_EQUAL( avec2, cvec2 );
    }
    
    TEST( ThreshFloat )
    {
        using namespace gfx;
        float anum ( 2.5f );
        float bnum ( 8.0f );
        float cnum = mix_th( anum, bnum, 0.4f );
        CHECK_EQUAL( anum, cnum );
    }
}

SUITE( LinearTests )
{
    TEST( LinearVec4 )
    {
        using namespace gfx;
        fvec4 avec4 ( 3.0f, -1.0f, 9.0f, -18.0f );
        fvec4 bvec4 ( 8.0f, 4.0f, -6.0f, 17.0f );
        fvec4 cvec4 = mix_ln( avec4, bvec4, 0.4f );
        fvec4 dvec4 ( 5.0f, 1.0f, 3.0f, -4.0f );
        CHECK_EQUAL( dvec4, cvec4 );
    }
    
    TEST( LinearVec3 )
    {
        using namespace gfx;
        fvec3 avec3 ( 3.0f, -1.0f, 9.0f );
        fvec3 bvec3 ( 8.0f, 4.0f, -6.0f );
        fvec3 cvec3 = mix_ln( avec3, bvec3, 0.4f );
        fvec3 dvec3 ( 5.0f, 1.0f, 3.0f );
        CHECK_EQUAL( dvec3, cvec3 );
    }
    TEST( LinearVec2 )
    {
        using namespace gfx;
        fvec2 avec2 ( 3.0f, -1.0f );
        fvec2 bvec2 ( 8.0f, 4.0f );
        fvec2 cvec2 = mix_ln( avec2, bvec2, 0.4f );
        fvec2 dvec2 ( 5.0f, 1.0f );
        CHECK_EQUAL( dvec2, cvec2 );
    }
    
    TEST( LinearFloat )
    {
        using namespace gfx;
        float anum ( 3.0f );
        float bnum ( 8.0f );
        float cnum = mix_ln( anum, bnum, 0.4f );
        CHECK_EQUAL( 5.0f, cnum );
    }
}

SUITE( CubicTests )
{
    TEST( CubicVec4 )
    {
        using namespace gfx;
        fvec4 avec4 ( 3.0f, -1.0f, 9.0f, -18.0f );
        fvec4 bvec4 ( 8.0f, 4.0f, -6.0f, 17.0f );
        fvec4 cvec4 = mix_cb( avec4, bvec4, 0.25f );
        fvec4 dvec4 ( 3.78125f, -0.21875f, 6.65625f, -12.53125f );
        CHECK_EQUAL( dvec4, cvec4 );
    }
    
    TEST( CubicVec3 )
    {
        using namespace gfx;
        fvec3 avec3 ( 3.0f, -1.0f, 9.0f );
        fvec3 bvec3 ( 8.0f, 4.0f, -6.0f );
        fvec3 cvec3 = mix_cb( avec3, bvec3, 0.25f );
        fvec3 dvec3 ( 3.78125f, -0.21875f, 6.65625f );
        CHECK_EQUAL( dvec3, cvec3 );
    }
    TEST( CubicVec2 )
    {
        using namespace gfx;
        fvec2 avec2 ( 3.0f, -1.0f );
        fvec2 bvec2 ( 8.0f, 4.0f );
        fvec2 cvec2 = mix_cb( avec2, bvec2, 0.25f );
        fvec2 dvec2 ( 3.78125f, -0.21875f );
        CHECK_EQUAL( dvec2, cvec2 );
    }
    
    TEST( CubicFloat )
    {
        using namespace gfx;
        float anum ( 3.0f );
        float bnum ( 8.0f );
        float cnum = mix_cb( anum, bnum, 0.25f );
        CHECK_EQUAL( 3.78125f, cnum );
    }
}

SUITE( DotTests )
{
    TEST( DotVec4 )
    {
        using namespace gfx;
        fvec4 avec4 ( 3.0f, -1.0f, 9.0f, -18.0f );
        fvec4 bvec4 ( 8.0f, 4.0f, -6.0f, 17.0f );
        float anum = dot( avec4, bvec4 );
        float bnum ( -340.0f );
        CHECK_EQUAL( bnum, anum );
    }
    
    TEST( DotVec3 )
    {
        using namespace gfx;
        fvec3 avec3 ( 3.0f, -1.0f, 9.0f );
        fvec3 bvec3 ( 8.0f, 4.0f, -6.0f );
        float anum = dot( avec3, bvec3 );
        float bnum ( -34.0f );
        CHECK_EQUAL( bnum, anum );
    }
    TEST( DotVec2 )
    {
        using namespace gfx;
        fvec2 avec2 ( 3.0f, -1.0f );
        fvec2 bvec2 ( 8.0f, 4.0f );
        float anum = dot( avec2, bvec2 );
        float bnum ( 20.0f );
        CHECK_EQUAL( bnum, anum );
    }

}

SUITE( MagTests )
{
    TEST( MagVec4 )
    {
        using namespace gfx;
        fvec4 avec4 ( 3.0f, -1.0f, 9.0f, -18.0f );
        float anum = mag( avec4 );
        float bnum ( sqrt(9.0f + 1.0f + 81.0f + 324.0f ) );
        CHECK_EQUAL( bnum, anum );
    }
    
    TEST( MagVec3 )
    {
        using namespace gfx;
        fvec3 avec3 ( 3.0f, -1.0f, 9.0f );
        float anum = mag( avec3 );
        float bnum ( sqrt(9.0f + 1.0f + 81.0f ) );
        CHECK_EQUAL( bnum, anum );
    }
    TEST( MagVec2 )
    {
        using namespace gfx;
        fvec2 avec2 ( 3.0f, -1.0f );
        float anum = mag( avec2 );
        float bnum ( sqrt( 9.0f + 1.0f ) );
        CHECK_EQUAL( bnum, anum );
    }

}

SUITE( InvMagTests )
{
    TEST( InvMagVec4 )
    {
        using namespace gfx;
        fvec4 avec4 ( 3.0f, -1.0f, 9.0f, -18.0f );
        float anum = inv_mag( avec4 );
        float bnum ( 1.0f / sqrt(9.0f + 1.0f + 81.0f + 324.0f ) );
        CHECK_EQUAL( bnum, anum );
    }
    
    TEST( InvMagVec3 )
    {
        using namespace gfx;
        fvec3 avec3 ( 3.0f, -1.0f, 9.0f );
        float anum = inv_mag( avec3 );
        float bnum ( 1.0f / sqrt(9.0f + 1.0f + 81.0f ) );
        CHECK_EQUAL( bnum, anum );
    }
    TEST( InvMagVec2 )
    {
        using namespace gfx;
        fvec2 avec2 ( 3.0f, -1.0f );
        float anum = inv_mag( avec2 );
        float bnum ( 1.0f / sqrt( 9.0f + 1.0f ) );
        CHECK_EQUAL( bnum, anum );
    }

}

SUITE( TransposeTests )
{
    TEST( TransposeMat )
        {
            using namespace gfx;
            fmat amat(2,2);
            amat(0,0) = 14.5f;
            amat(0,1) = -7.01f;
            amat(1,0) = 100.5f;
            amat(1,1) = -234.52f;
            fmat bmat = transpose( amat );
            fmat cmat(2,2);
            cmat(0,0) = 14.5f;
            cmat(0,1) = 100.5f;
            cmat(1,0) = -7.01f;
            cmat(1,1) = -234.52f;
            
            CHECK_EQUAL( cmat, bmat );
        }
}

SUITE( HomogenizeTests )
{
    TEST( HomogenizeMat )
        {
            using namespace gfx;
            fmat amat(2,2);
            amat(0,0) = 14.5f;
            amat(0,1) = -7.01f;
            amat(1,0) = 100.5f;
            amat(1,1) = -234.52f;
            fmat bmat = homogenize( amat );
            fmat cmat(3,3);
            cmat(0,0) = 14.5f;
            cmat(0,1) = -7.01f;
            cmat(0,2) = 0.0f;
            cmat(1,0) = 100.5f;
            cmat(1,1) = -234.52f;
            cmat(1,2) = 0.0f;
            cmat(2,0) = 0.0f;
            cmat(2,1) = 0.0f;
            cmat(2,2) = 1.0f;
            
            CHECK_EQUAL( cmat, bmat );
        }
}

SUITE( ClipTests )
{
    TEST( ClipRngFloat )
    {
        using namespace gfx;
        float anum (25.1f);
        float bnum ( clip_rng( anum, 1.5f, 20.0f) );
        CHECK_EQUAL( 20.0f, bnum );
        float cnum ( clip_rng( anum, 30.0f, 50.0f) );
        CHECK_EQUAL( 30.0f, cnum );
    }
}

int main( int argc, char** argv )
{
    return UnitTest::RunAllTests();
}