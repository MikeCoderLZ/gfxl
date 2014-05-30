#include <iostream>

//#include "type_op.hpp"
#include "../../UnitTest++_src/UnitTest++.h"
#include "datatype.hpp"
#include "constant.hpp"
//#include "swizzTest.hpp"

SUITE( RawMapTests )
{
    TEST( RawMapConstruction )
    {
        using namespace gfx;
        raw_map amap( 10 );
        CHECK_EQUAL( 10u, amap.n_bytes );
    }

    TEST( RawMapCopyAssignment )
    {
        using namespace gfx;
        raw_map amap( 10 );
        raw_map bmap = amap;
        CHECK_EQUAL( 10u, bmap.n_bytes );
        amap[0] = 0;
        bmap[0] = 8;
        CHECK( amap[0] != bmap[0] ); // no side effects
    }
}

SUITE( ScalarTests )
{
    TEST( ScalarConstruction )
    {
        using namespace gfx;
        float32 anum;
        CHECK_EQUAL( 0.0f, anum );
    }

    TEST( ScalarCopyAssignment )
    {
        using namespace gfx;
        float32 anum(5.0f);
        float32 bnum = anum;
        CHECK_EQUAL( anum, bnum );
    }
    
    TEST( ScalarAssignment )
    {
        using namespace gfx;
        float32 anum(5.0f);
        float32 bnum;
        bnum = anum;
        CHECK_EQUAL( anum, bnum );
        bnum = -10.0f;
        CHECK_EQUAL( -10.0f, bnum );
        anum = anum;
        CHECK_EQUAL( 5.0f, anum );
    }

    TEST( ScalarAddition )
    {
        using namespace gfx;
        float32 anum(5.0f);
        float32 bnum(4.0f);
        CHECK_EQUAL( 9.0f, anum + bnum );
        CHECK_EQUAL( 9.0f, anum + 4.0f );
        CHECK_EQUAL( 9.0f, 5.0f + bnum );
    }

    TEST( ScalarSubtraction )
    {
        using namespace gfx;
        float32 anum(5.0f);
        float32 bnum(4.0f);
        CHECK_EQUAL( 1.0f, anum - bnum );
        CHECK_EQUAL( 1.0f, anum - 4.0f );
        CHECK_EQUAL( 1.0f, 5.0f - bnum );
    }

    TEST( ScalarMultiplication )
    {
        using namespace gfx;
        float32 anum(5.0f);
        float32 bnum(4.0f);
        CHECK_EQUAL( 20.0f, anum * bnum );
        CHECK_EQUAL( 20.0f, anum * 4.0f );
        CHECK_EQUAL( 20.0f, 5.0f * bnum );
    }

    TEST( ScalarDivision )
    {
        using namespace gfx;
        float32 anum(8.0f);
        float32 bnum(4.0f);
        CHECK_EQUAL( 2.0f, anum / bnum );
        CHECK_EQUAL( 2.0f, anum / 4.0f );
        CHECK_EQUAL( 2.0f, 8.0f / bnum );
    }

    TEST( ScalarMapping )
    {
        using namespace gfx;
        union mock_data {
            float   value;
            unsigned char   bytes[sizeof(float)];
        };

        float32 anum(8.0f);
        raw_map anum_map = anum.to_map();
        mock_data test_bytes = { 8.0f };
        
        size_t i = sizeof(float);
        
        while(i) {
            --i;
            CHECK_EQUAL( test_bytes.bytes[i], anum_map[i] );
        }   
    }
}

SUITE( Vec2Tests )
{
    TEST( Vec2Construction )
    {
        using namespace gfx;
        vec2 avec2;
        vec2 bvec2( 0.0f, 0.0f );
        CHECK_EQUAL( avec2, bvec2 );
    }

    TEST( Vec2FillConstruction )
    {
        using namespace gfx;
        vec2 avec2( 1.0f );
        vec2 bvec2( 1.0f, 1.0f );
        CHECK_EQUAL( avec2, bvec2 );
    }

    TEST( Vec2CopyAssignment )
    {
        using namespace gfx;
        vec2 avec2( 1.0f, -4.5f );
        vec2 bvec2 = avec2;
        CHECK_EQUAL( avec2, bvec2 );
        bvec2(x) = -2.5f;
        CHECK( avec2(x) != bvec2(x) );
        CHECK( avec2(y) != bvec2(x) );
        // no side effects
    }

    TEST( Vec2Assignment )
    {
        using namespace gfx;
        vec2 avec2( 1.0f, -4.5f );
        vec2 bvec2( -2.4f, 67.8f );
        CHECK( avec2 != bvec2 );
        avec2 = bvec2;
        CHECK_EQUAL( avec2, bvec2 );
        
        avec2(x) = -2.5f;
        CHECK( bvec2(x) != avec2(x) );
        CHECK( bvec2(y) != avec2(x) );
    }

    TEST( Vec2LookupComponent )
    {
        using namespace gfx;
        vec2 avec2( 1.0f, -4.5f );
        CHECK_EQUAL( 1.0f, avec2(x) );
        CHECK_EQUAL( -4.5f, avec2(y) );
        CHECK_EQUAL( 1.0f, avec2[0] );
        CHECK_EQUAL( -4.5f, avec2[1] );
        avec2(y) = 5.6f;
        CHECK_EQUAL( 5.6f, avec2(y) );
        CHECK_EQUAL( 5.6f, avec2[1] );
        avec2[0] = -4.2f;
        CHECK_EQUAL( -4.2f, avec2(x) );
        CHECK_EQUAL( -4.2f, avec2[0] );
        
        float a = 0.0f;
        CHECK_EQUAL( 0.0f, a );
        
        try {
            a = avec2[3];
        } catch (std::out_of_range e) {
            CHECK_EQUAL( e.what(), "index out of range on vec2_t lookup" );
        }
        
        try {
            a = avec2[-3];
        } catch (std::out_of_range e) {
            CHECK_EQUAL( e.what(), "index out of range on vec2_t lookup" );
        }
    }

    TEST( Vec2LookupConstruction )
    {
        using namespace gfx;
        vec2 avec2( 1.0f, -4.5f );
        vec2 bvec2( 1.0f, 1.0f );
        vec2 bvec2_cn = avec2(x,x);
        vec3 cvec3( 1.0f, 1.0f, -4.5f );
        vec3 cvec3_cn = avec2(x,x,y);
        vec4 dvec4( -4.5f, 1.0f, -1.0f, -4.5f);
        vec4 dvec4_cn = avec2(y,x,-x,y);
        
        CHECK_EQUAL( bvec2, bvec2_cn );
        CHECK_EQUAL( cvec3, cvec3_cn );
        CHECK_EQUAL( dvec4, dvec4_cn );
        
        bvec2_cn(y) = 5.6f;
        CHECK( 5.6f != avec2(x) );
        CHECK( 5.6f != avec2(y) );
        
        cvec3_cn(y) = 5.6f;
        CHECK( 5.6f != avec2(x) );
        CHECK( 5.6f != avec2(y) );
        
        dvec4_cn(y) = 5.6f;
        CHECK( 5.6f != avec2(x) );
        CHECK( 5.6f != avec2(y) );
    }

    TEST( Vec2Addition )
    {
        using namespace gfx;
        vec2 avec2( 1.0f, -4.5f );
        vec2 bvec2( 1.0f, 1.0f );
        vec2 cvec2( 2.0f, -3.5f );
        vec2 dvec2 = avec2 + bvec2;
        CHECK_EQUAL( cvec2, dvec2 );
    }

    TEST( Vec2Subtraction )
    {
        using namespace gfx;
        vec2 avec2( 1.0f, -4.5f );
        vec2 bvec2( 1.0f, 1.0f );
        vec2 cvec2( 0.0f, -5.5f );
        vec2 dvec2 = avec2 - bvec2;
        CHECK_EQUAL( cvec2, dvec2 );
    }

    TEST( Vec2Multiplication )
    {
        using namespace gfx;
        vec2 avec2( 1.0f, -4.5f );
        vec2 bvec2( 1.0f, 1.0f );
        vec2 cvec2( 1.0f, -4.5f );
        vec2 dvec2 = avec2 * bvec2;
        CHECK_EQUAL( cvec2, dvec2 );
    }

    TEST( Vec2Division )
    {
        using namespace gfx;
        vec2 avec2( 1.0f, -4.5f );
        vec2 bvec2( 2.0f, 2.0f );
        vec2 cvec2( 0.5f, -2.25f );
        vec2 dvec2 = avec2 / bvec2;
        CHECK_EQUAL( cvec2, dvec2 );
    }

    TEST( Vec2Mapping )
    {
        using namespace gfx;
        union mock_data {
            float           values[2];
            unsigned char   bytes[sizeof(float) * 2];
        };

        vec2 avec2(8.0f, -2.0f);
        raw_map avec2_map = avec2.to_map();
        mock_data test_bytes = { {8.0f, -2.0f} };
        
        size_t i = sizeof(float) * 2;
        
        while(i) {
            --i;
            CHECK_EQUAL( test_bytes.bytes[i], avec2_map[i] );
        } 
    }
    
    TEST( Vec2Normalize )
    {
        using namespace gfx;
        vec2 avec2 ( 2.0f, -1.0f );
        vec2 bvec2 (  2.0f / sqrt( 5.0f ),
                      -1.0f / sqrt( 5.0f ) );
        avec2.norm();
        CHECK_EQUAL( bvec2, avec2 );
    }
}

SUITE( Vec3Tests )
{
    TEST( Vec3Construction )
    {
        using namespace gfx;
        vec3 avec3;
        vec3 bvec3( 0.0f, 0.0f, 0.0f );
        CHECK_EQUAL( avec3, bvec3 );
    }

    TEST( Vec3FillConstruction )
    {
        using namespace gfx;
        vec3 avec3( 1.0f );
        vec3 bvec3( 1.0f, 1.0f, 1.0f );
        CHECK_EQUAL( avec3, bvec3 );
    }

    TEST( Vec3CopyAssignment )
    {
        using namespace gfx;
        vec3 avec3( 1.0f, -4.5f, 2.0f );
        vec3 bvec3 = avec3;
        CHECK_EQUAL( avec3, bvec3 );
        bvec3(x) = -2.5f;
        CHECK( avec3(x) != bvec3(x) );
        CHECK( avec3(y) != bvec3(x) );
        CHECK( avec3(z) != bvec3(x) );
        // no side effects
    }

    TEST( Vec3Assignment )
    {
        using namespace gfx;
        vec3 avec3( 1.0f, -4.5f, 2.0f );
        vec3 bvec3( -2.4f, 67.8f, 4.0f );
        CHECK( avec3 != bvec3 );
        avec3 = bvec3;
        CHECK_EQUAL( avec3, bvec3 );
        
        avec3(x) = -2.5f;
        CHECK( bvec3(x) != avec3(x) );
        CHECK( bvec3(y) != avec3(x) );
        CHECK( bvec3(z) != avec3(x) );
    }

    TEST( Vec3LookupComponent )
    {
        using namespace gfx;
        vec3 avec3( 1.0f, -4.5f, 2.0f );
        CHECK_EQUAL( 1.0f, avec3(x) );
        CHECK_EQUAL( -4.5f, avec3(y) );
        CHECK_EQUAL( 2.0f, avec3(z) );
        CHECK_EQUAL( 1.0f, avec3[0] );
        CHECK_EQUAL( -4.5f, avec3[1] );
        CHECK_EQUAL( 2.0f, avec3[2] );
        avec3(z) = 5.6f;
        CHECK_EQUAL( 5.6f, avec3(z) );
        CHECK_EQUAL( 5.6f, avec3[2] );
        
        avec3[0] = 5.9f;
        CHECK_EQUAL( 5.9f, avec3(x) );
        CHECK_EQUAL( 5.9f, avec3[0] );
        
        float a = 0.0f;
        CHECK_EQUAL( 0.0f, a );
        
        try {
            a = avec3[3];
        } catch (std::out_of_range e) {
            CHECK_EQUAL( e.what(), "index out of range on vec3_t lookup" );
        }
        
        try {
            a = avec3[-3];
        } catch (std::out_of_range e) {
            CHECK_EQUAL( e.what(), "index out of range on vec3_t lookup" );
        }
    }

    TEST( Vec3LookupConstruction )
    {
        using namespace gfx;
        vec3 avec3( 1.0f, -4.5f, 2.0f );
        
        vec2 bvec2( 1.0f, 1.0f );
        vec2 bvec2_cn = avec3(x,x);
        vec3 cvec3( 1.0f, -2.0f, -4.5f );
        vec3 cvec3_cn = avec3(x,-z,y);
        vec4 dvec4( -4.5f, 2.0f, -1.0f, -4.5f);
        vec4 dvec4_cn = avec3(y,z,-x,y);
        
        CHECK_EQUAL( bvec2, bvec2_cn );
        CHECK_EQUAL( cvec3, cvec3_cn );
        CHECK_EQUAL( dvec4, dvec4_cn );
        
        bvec2_cn(y) = 5.6f;
        CHECK( 5.6f != avec3(x) );
        CHECK( 5.6f != avec3(y) );
        CHECK( 5.6f != avec3(z) );
        
        cvec3_cn(y) = 5.6f;
        CHECK( 5.6f != avec3(x) );
        CHECK( 5.6f != avec3(y) );
        CHECK( 5.6f != avec3(z) );
        
        dvec4_cn(y) = 5.6f;
        CHECK( 5.6f != avec3(x) );
        CHECK( 5.6f != avec3(y) );
        CHECK( 5.6f != avec3(z) );
    }

    TEST( Vec3Addition )
    {
        using namespace gfx;
        vec3 avec3( 1.0f, -4.5f, 2.0f );
        vec3 bvec3( 1.0f, 1.0f, 1.0f );
        vec3 cvec3( 2.0f, -3.5f, 3.0f );
        vec3 dvec3 = avec3 + bvec3;
        CHECK_EQUAL( cvec3, dvec3 );
    }

    TEST( Vec3Subtraction )
    {
        using namespace gfx;
        vec3 avec3( 1.0f, -4.5f, 2.0f );
        vec3 bvec3( 1.0f, 1.0f, 1.0f );
        vec3 cvec3( 0.0f, -5.5f, 1.0f );
        vec3 dvec3 = avec3 - bvec3;
        CHECK_EQUAL( cvec3, dvec3 );
    }

    TEST( Vec3Multiplication )
    {
        using namespace gfx;
        vec3 avec3( 1.0f, -4.5f, 2.0f );
        vec3 bvec3( 1.0f, 1.0f, 5.0f );
        vec3 cvec3( 1.0f, -4.5f, 10.0f );
        vec3 dvec3 = avec3 * bvec3;
        CHECK_EQUAL( cvec3, dvec3 );
    }

    TEST( Vec3Division )
    {
        using namespace gfx;
        vec3 avec3( 1.0f, -4.5f, 2.0f );
        vec3 bvec3( 2.0f, 2.0f, 5.0f );
        vec3 cvec3( 0.5f, -2.25f, 0.4f );
        vec3 dvec3 = avec3 / bvec3;
        CHECK_EQUAL( cvec3, dvec3 );
    }

    TEST( Vec3Mapping )
    {
        using namespace gfx;
        union mock_data {
            float           values[3];
            unsigned char   bytes[sizeof(float) * 3];
        };

        vec3 avec3(8.0f, -2.0f, 0.0f);
        raw_map avec3_map = avec3.to_map();
        mock_data test_bytes = { {8.0f, -2.0f, 0.0f} };
        
        size_t i = sizeof(float) * 3;
        
        while(i) {
            --i;
            CHECK_EQUAL( test_bytes.bytes[i], avec3_map[i] );
        } 
    }
    
    TEST( Vec3Normalize )
    {
        using namespace gfx;
        vec3 avec3 ( 2.0f, -1.0f, 15.0f );
        vec3 bvec3 (  2.0f / sqrt( 230.0f ),
                      -1.0f / sqrt( 230.0f ),
                      15.0f / sqrt( 230.0f ) );
        avec3.norm();
        CHECK_EQUAL( bvec3, avec3 );
    }
}

SUITE( Vec4Tests )
{
    TEST( Vec4Construction )
    {
        using namespace gfx;
        vec4 avec4;
        vec4 bvec4( 0.0f, 0.0f, 0.0f, 0.0f );
        CHECK_EQUAL( avec4, bvec4 );
    }

    TEST( Vec4FillConstruction )
    {
        using namespace gfx;
        vec4 avec4( 1.0f );
        vec4 bvec4( 1.0f, 1.0f, 1.0f, 1.0f );
        CHECK_EQUAL( avec4, bvec4 );
    }

    TEST( Vec4CopyAssignment )
    {
        using namespace gfx;
        vec4 avec4( 1.0f, -4.5f, 2.0f, -3.5f );
        vec4 bvec4 = avec4;
        CHECK_EQUAL( avec4, bvec4 );
        bvec4(x) = -2.5f;
        CHECK( avec4(x) != bvec4(x) );
        CHECK( avec4(y) != bvec4(x) );
        CHECK( avec4(z) != bvec4(x) );
        CHECK( avec4(w) != bvec4(x) );
        // no side effects
    }

    TEST( Vec4Assignment )
    {
        using namespace gfx;
        vec4 avec4( 1.0f, -4.5f, 2.0f, -3.5f );
        vec4 bvec4( -2.4f, 67.8f, 4.0f, 1.0f );
        CHECK( avec4 != bvec4 );
        avec4 = bvec4;
        CHECK_EQUAL( avec4, bvec4 );
        
        bvec4(x) = -2.5f;
        CHECK( avec4(x) != bvec4(x) );
        CHECK( avec4(y) != bvec4(x) );
        CHECK( avec4(z) != bvec4(x) );
        CHECK( avec4(w) != bvec4(x) );
    }

    TEST( Vec4LookupComponent )
    {
        using namespace gfx;
        vec4 avec4( 1.0f, -4.5f, 2.0f, -3.5f );
        CHECK_EQUAL( 1.0f, avec4(x) );
        CHECK_EQUAL( -4.5f, avec4(y) );
        CHECK_EQUAL( 2.0f, avec4(z) );
        CHECK_EQUAL( -3.5f, avec4(w) );
        
        CHECK_EQUAL( 1.0f, avec4[0] );
        CHECK_EQUAL( -4.5f, avec4[1] );
        CHECK_EQUAL( 2.0f, avec4[2] );
        CHECK_EQUAL( -3.5f, avec4[3] );
        
        avec4(w) = 5.6f;
        CHECK_EQUAL( 5.6f, avec4(w) );
        CHECK_EQUAL( 5.6f, avec4[3] );
        
        avec4[3] = -2.6f;
        CHECK_EQUAL( -2.6f, avec4(w) );
        CHECK_EQUAL( -2.6f, avec4[3] );
        
        float a = 0.0f;
        CHECK_EQUAL( 0.0f, a );
        try {
            a = avec4[7];
        } catch (std::out_of_range e) {
            CHECK_EQUAL( e.what(), "index out of range on vec4_t lookup" );
        }
        
        try {
            a = avec4[-3];
        } catch (std::out_of_range e) {
            CHECK_EQUAL( e.what(), "index out of range on vec4_t lookup" );
        }
    }

    TEST( Vec4LookupConstruction )
    {
        using namespace gfx;
        vec4 avec4( 1.0f, -4.5f, 2.0f, -3.5f );
        
        vec2 bvec2( 1.0f, -3.5f );
        vec2 bvec2_cn = avec4(x,w);
        vec3 cvec3( 1.0f, 3.5f, -4.5f );
        vec3 cvec3_cn = avec4(x,-w,y);
        vec4 dvec4( -4.5f, 2.0f, -1.0f, -3.5f);
        vec4 dvec4_cn = avec4(y,z,-x,w);
        
        CHECK_EQUAL( bvec2, bvec2_cn );
        CHECK_EQUAL( cvec3, cvec3_cn );
        CHECK_EQUAL( dvec4, dvec4_cn );
        
        bvec2_cn(y) = 5.6f;
        CHECK( 5.6f != avec4(x) );
        CHECK( 5.6f != avec4(y) );
        CHECK( 5.6f != avec4(z) );
        CHECK( 5.6f != avec4(w) );
        
        cvec3_cn(y) = 5.6f;
        CHECK( 5.6f != avec4(x) );
        CHECK( 5.6f != avec4(y) );
        CHECK( 5.6f != avec4(z) );
        CHECK( 5.6f != avec4(w) );
        
        dvec4_cn(y) = 5.6f;
        CHECK( 5.6f != avec4(x) );
        CHECK( 5.6f != avec4(y) );
        CHECK( 5.6f != avec4(z) );
        CHECK( 5.6f != avec4(w) );
    }

    TEST( Vec4Addition )
    {
        using namespace gfx;
        vec4 avec4( 1.0f, -4.5f, 2.0f, -3.5f );
        vec4 bvec4( 1.0f, 1.0f, 1.0f, -1.0f );
        vec4 cvec4( 2.0f, -3.5f, 3.0f, -4.5f );
        vec4 dvec4 = avec4 + bvec4;
        CHECK_EQUAL( cvec4, dvec4 );
    }

    TEST( Vec4Subtraction )
    {
        using namespace gfx;
        vec4 avec4( 1.0f, -4.5f, 2.0f, -3.5f );
        vec4 bvec4( 1.0f, 1.0f, 1.0f, -1.0f );
        vec4 cvec4( 0.0f, -5.5f, 1.0f, -2.5f );
        vec4 dvec4 = avec4 - bvec4;
        CHECK_EQUAL( cvec4, dvec4 );
    }

    TEST( Vec4Multiplication )
    {
        using namespace gfx;
        vec4 avec4( 1.0f, -4.5f, 2.0f, -3.5f );
        vec4 bvec4( 1.0f, 1.0f, 1.0f, -1.0f );
        vec4 cvec4( 1.0f, -4.5f, 2.0f, 3.5f );
        vec4 dvec4 = avec4 * bvec4;
        CHECK_EQUAL( cvec4, dvec4 );
    }

    TEST( Vec4Division )
    {
        using namespace gfx;
        vec4 avec4( 1.0f, -4.5f, 2.0f, -3.5f );
        vec4 bvec4( 2.0f, 2.0f, 5.0f, -2.0f );
        vec4 cvec4( 0.5f, -2.25f, 0.4f, 1.75f );
        vec4 dvec4 = avec4 / bvec4;
        CHECK_EQUAL( cvec4, dvec4 );
    }

    TEST( Vec4Mapping )
    {
        using namespace gfx;
        union mock_data {
            float           values[4];
            unsigned char   bytes[sizeof(float) * 4];
        };

        vec4 avec4(8.0f, -2.0f, 0.0f, 10.0f);
        raw_map avec4_map = avec4.to_map();
        mock_data test_bytes = { {8.0f, -2.0f, 0.0f, 10.0f} };
        
        size_t i = sizeof(float) * 4;
        
        while(i) {
            --i;
            CHECK_EQUAL( test_bytes.bytes[i], avec4_map[i] );
        } 
    }
    
    TEST( Vec4Normalize )
    {
        using namespace gfx;
        vec4 avec4 ( 2.0f, -1.0f, 15.0f, -5.0f );
        vec4 bvec4 (  2.0f / sqrt( 255.0f ),
                      -1.0f / sqrt( 255.0f ),
                      15.0f / sqrt( 255.0f ),
                      -5.0f / sqrt( 255.0f ) );
        avec4.norm();
        CHECK_EQUAL( bvec4, avec4 );
    }
}

SUITE( QutnTests )
{
    TEST( QutnConstruction )
    {
        using namespace gfx;
        qutn aqutn;
        qutn bqutn( 0.0f, 0.0f, 0.0f, 1.0f );
        CHECK_EQUAL( bqutn, aqutn );
    }

    TEST( QutnFillConstruction )
    {
        using namespace gfx;
        qutn aqutn( 1.0f );
        qutn bqutn( 1.0f, 1.0f, 1.0f, 1.0f );
        CHECK_EQUAL( bqutn, aqutn );
    }
    
    TEST( QutnPureConstruction )
    {
        using namespace gfx;
        vec3 avec3 ( 2.0f, 8.5f, 0.0f );
        qutn aqutn = qutn::pure( avec3 );
        qutn bqutn( 2.0f, 8.5f, 0.0f, 0.0f );
        CHECK_EQUAL( bqutn, aqutn );
    }
    
    TEST( QutnRotationMatrix )
    {
        using namespace gfx;
        vec3 axis( 1.0f, 0.0f, 0.0f );
        d_angle ang = d_angle::in_degs( 90.0f );
        mat3 amat3 = mat3::rotation( axis, ang );
        qutn aqutn = qutn::rotation( amat3 );
        qutn bqutn( lit<float>::inv_sqrt_two,
                    0.0f,
                    0.0f,
                    lit<float>::inv_sqrt_two );
        CHECK_EQUAL( bqutn, aqutn );
    }
    
    TEST( QutnRotationAxisAngle )
    {
        using namespace gfx;
        vec3 axis( 1.0f, 0.0f, 0.0f );
        d_angle ang = d_angle::in_degs( 90.0f );
        qutn aqutn = qutn::rotation( axis, ang );
        qutn bqutn( lit<float>::inv_sqrt_two,
                    0.0f,
                    0.0f,
                    lit<float>::inv_sqrt_two );
        CHECK_EQUAL( bqutn, aqutn );
    }

    TEST( QutnCopyAssignment )
    {
        using namespace gfx;
        qutn aqutn( 1.0f, -4.5f, 2.0f, -3.5f );
        qutn bqutn = aqutn;
        CHECK_EQUAL( bqutn, aqutn );
        bqutn(x) = -2.5f;
        CHECK( aqutn(x) != bqutn(x) );
        CHECK( aqutn(y) != bqutn(x) );
        CHECK( aqutn(z) != bqutn(x) );
        CHECK( aqutn(w) != bqutn(x) );
        // no side effects
    }

    TEST( QutnAssignment )
    {
        using namespace gfx;
        qutn aqutn( 1.0f, -4.5f, 2.0f, -3.5f );
        qutn bqutn( -2.4f, 67.8f, 4.0f, 1.0f );
        CHECK( aqutn != bqutn );
        aqutn = bqutn;
        CHECK_EQUAL( aqutn, aqutn );
        
        bqutn(x) = -2.5f;
        CHECK( aqutn(x) != bqutn(x) );
        CHECK( aqutn(y) != bqutn(x) );
        CHECK( aqutn(z) != bqutn(x) );
        CHECK( aqutn(w) != bqutn(x) );
    }

    TEST( QutnLookupComponent )
    {
        using namespace gfx;
        qutn aqutn( 1.0f, -4.5f, 2.0f, -3.5f );
        CHECK_EQUAL( 1.0f, aqutn(x) );
        CHECK_EQUAL( -4.5f, aqutn(y) );
        CHECK_EQUAL( 2.0f, aqutn(z) );
        CHECK_EQUAL( -3.5f, aqutn(w) );
        
        CHECK_EQUAL( 1.0f, aqutn[0] );
        CHECK_EQUAL( -4.5f, aqutn[1] );
        CHECK_EQUAL( 2.0f, aqutn[2] );
        CHECK_EQUAL( -3.5f, aqutn[3] );
        
        aqutn(w) = 5.6f;
        CHECK_EQUAL( 5.6f, aqutn(w) );
        CHECK_EQUAL( 5.6f, aqutn[3] );
        
        aqutn[3] = -2.6f;
        CHECK_EQUAL( -2.6f, aqutn(w) );
        CHECK_EQUAL( -2.6f, aqutn[3] );
        
        float a = 0.0f;
        CHECK_EQUAL( 0.0f, a );
        try {
            a = aqutn[7];
        } catch (std::out_of_range e) {
            CHECK_EQUAL( e.what(), "index out of range on qutn_t lookup" );
        }
        
        try {
            a = aqutn[-3];
        } catch (std::out_of_range e) {
            CHECK_EQUAL( e.what(), "index out of range on qutn_t lookup" );
        }
    }

    TEST( QutnAddition )
    {
        using namespace gfx;
        qutn aqutn( 1.0f, -4.5f, 2.0f, -3.5f );
        qutn bqutn( 1.0f, 1.0f, 1.0f, -1.0f );
        qutn cqutn( 2.0f, -3.5f, 3.0f, -4.5f );
        qutn dqutn = aqutn + bqutn;
        CHECK_EQUAL( cqutn, dqutn );
    }

    TEST( QutnSubtraction )
    {
        using namespace gfx;
        qutn aqutn( 1.0f, -4.5f, 2.0f, -3.5f );
        qutn bqutn( 1.0f, 1.0f, 1.0f, -1.0f );
        qutn cqutn( 0.0f, -5.5f, 1.0f, -2.5f );
        qutn dqutn = aqutn - bqutn;
        CHECK_EQUAL( cqutn, dqutn );
    }
    
    TEST( QutnNegation )
    {
        using namespace gfx;
        qutn aqutn( 1.0f, -4.5f, 2.0f, -3.5f );
        qutn bqutn( -1.0f, 4.5f, -2.0f, -3.5f );
        qutn cqutn = -aqutn;
        CHECK_EQUAL( bqutn, cqutn );
    }
    
    TEST( QutnMultiplication )
    {
        using namespace gfx;
        qutn aqutn( 1.0f, -4.5f, 2.0f, -3.5f );
        qutn bqutn( 1.0f, 1.0f, 1.0f, -1.0f );
        qutn cqutn( -11.0f, 2.0f, 0.0f, 5.0f );
        qutn dqutn = aqutn * bqutn;
        CHECK_EQUAL( cqutn, dqutn );
    }
    
    TEST( QutnNormalize )
    {
        using namespace gfx;
        qutn aqutn ( 2.0f, -1.0f, 15.0f, -5.0f );
        qutn bqutn (  2.0f / sqrt( 255.0f ),
                      -1.0f / sqrt( 255.0f ),
                      15.0f / sqrt( 255.0f ),
                      -5.0f / sqrt( 255.0f ) );
        aqutn.norm();
        CHECK_EQUAL( bqutn, aqutn );
    }    

    TEST( QutnMapping )
    {
        using namespace gfx;
        union mock_data {
            float           values[4];
            unsigned char   bytes[sizeof(float) * 4];
        };

        qutn aqutn(8.0f, -2.0f, 0.0f, 10.0f);
        raw_map aqutn_map = aqutn.to_map();
        mock_data test_bytes = { {8.0f, -2.0f, 0.0f, 10.0f} };
        
        size_t i = sizeof(float) * 4;
        
        while(i) {
            --i;
            CHECK_EQUAL( test_bytes.bytes[i], aqutn_map[i] );
        } 
    }
}

SUITE( MatrixTests )
{
    TEST( MatrixConstruction )
    {
        using namespace gfx;
        mat amat(2,2);
        CHECK_EQUAL( amat.n_cols(), 2u );
        CHECK_EQUAL( amat.n_rows(), 2u );
        CHECK_EQUAL( amat.n_comp(), 4u );
        mat bmat(2,2);
        bmat(0,0) = 0.0f;
        bmat(0,1) = 0.0f;
        bmat(1,0) = 0.0f;
        bmat(1,1) = 0.0f;
        CHECK_EQUAL( amat, bmat );
    }

    TEST( MatrixFill )
    {
        using namespace gfx;
        mat amat = mat::fill( 2, 2, 4.5f );
        CHECK_EQUAL( amat.n_cols(), 2u );
        CHECK_EQUAL( amat.n_rows(), 2u );
        CHECK_EQUAL( amat.n_comp(), 4u );
        mat bmat(2,2);
        bmat(0,0) = 4.5f;
        bmat(0,1) = 4.5f;
        bmat(1,0) = 4.5f;
        bmat(1,1) = 4.5f;
        CHECK_EQUAL( amat, bmat );
    }

    TEST( MatrixIdentity )
    {
        using namespace gfx;
        mat amat = mat::identity( 2 );
        CHECK_EQUAL( amat.n_cols(), 2u );
        CHECK_EQUAL( amat.n_rows(), 2u );
        CHECK_EQUAL( amat.n_comp(), 4u );
        mat bmat(2,2);
        bmat(0,0) = 1.0f;
        bmat(0,1) = 0.0f;
        bmat(1,0) = 0.0f;
        bmat(1,1) = 1.0f;
        CHECK_EQUAL( amat, bmat );
    }

    TEST( MatrixAssignment )
    {
        using namespace gfx;
        mat amat(2,2);
        mat bmat(2,2);
        bmat(0,0) = 14.5f;
        bmat(0,1) = -7.01f;
        bmat(1,0) = 100.5f;
        bmat(1,1) = -234.52f;
        CHECK( amat != bmat );
        amat = bmat;
        CHECK_EQUAL( amat, bmat );
        CHECK_EQUAL( amat.n_comp(), bmat.n_comp() );
        mat cmat = amat;
        bmat(0,1) = 67.3f;
        CHECK( amat != bmat );
        CHECK_EQUAL( amat, cmat ); // no side effects
    }

    TEST( MatrixLookup )
    {
        using namespace gfx;
        mat amat(2,2);
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
        using namespace gfx;
        mat amat(2,2);
        mat bmat(2,2);
        bmat(0,0) = 14.5f;
        bmat(0,1) = -7.01f;
        bmat(1,0) = 100.5f;
        bmat(1,1) = -234.52f;
        CHECK( amat != bmat );
        mat cmat(2,2);   
        cmat = amat + bmat;
        CHECK_EQUAL( cmat, bmat );
    }

    TEST( MatrixSubtraction )
    {
        using namespace gfx;
        mat amat(2,2);
        mat bmat(2,2);
        bmat(0,0) = 14.5f;
        bmat(0,1) = -7.01f;
        bmat(1,0) = 100.5f;
        bmat(1,1) = -234.52f;
        CHECK( amat != bmat );
        mat cmat;   
        cmat = amat - bmat;
        bmat(0,0) = -14.5f;
        bmat(0,1) = 7.01f;
        bmat(1,0) = -100.5f;
        bmat(1,1) = 234.52f;
        CHECK_EQUAL( cmat, bmat );
    }

    TEST( MatrixMultiplication )
    {
        using namespace gfx;
        mat amat = mat::identity(2);
        mat bmat(2,2);
        bmat(0,0) = 14.5f;
        bmat(0,1) = -7.01f;
        bmat(1,0) = 100.5f;
        bmat(1,1) = -234.52f;
        CHECK( amat != bmat );
        mat cmat = amat * bmat;
        CHECK_EQUAL( cmat, bmat );
    }

    TEST( MatrixScalarMultiplication )
    {
        using namespace gfx;
        mat amat(2,2);
        amat(0,0) = 14.5f;
        amat(0,1) = -7.01f;
        amat(1,0) = 100.5f;
        amat(1,1) = -234.52f;
        mat cmat = amat * 2.0f;
        amat(0,0) = 29.0f;
        amat(0,1) = -14.02f;
        amat(1,0) = 201.0f;
        amat(1,1) = -469.04f;
        CHECK_EQUAL( cmat, amat );
        cmat = 2.0f * amat;
        amat(0,0) = 58.0f;
        amat(0,1) = -28.04f;
        amat(1,0) = 402.0f;
        amat(1,1) = -938.08f;
        CHECK_EQUAL( cmat, amat );
        
        float32 anum( 2.0f );
        amat(0,0) = 14.5f;
        amat(0,1) = -7.01f;
        amat(1,0) = 100.5f;
        amat(1,1) = -234.52f;
        cmat = amat * anum;
        amat(0,0) = 29.0f;
        amat(0,1) = -14.02f;
        amat(1,0) = 201.0f;
        amat(1,1) = -469.04f;
        CHECK_EQUAL( cmat, amat );
        cmat = anum * amat;
        amat(0,0) = 58.0f;
        amat(0,1) = -28.04f;
        amat(1,0) = 402.0f;
        amat(1,1) = -938.08f;
        CHECK_EQUAL( cmat, amat );
    }

    TEST( MatrixScalarDivision )
    {
        using namespace gfx;
        mat amat(2,2);
        amat(0,0) = 14.5f;
        amat(0,1) = -7.01f;
        amat(1,0) = 100.5f;
        amat(1,1) = -234.52f;
        mat cmat = amat / 2.0f;
        amat(0,0) = 7.25f;
        amat(0,1) = -3.505f;
        amat(1,0) = 50.25f;
        amat(1,1) = -117.26f;
        CHECK_EQUAL( cmat, amat );
        
        float32 anum( 2.0f );
        amat(0,0) = 14.5f;
        amat(0,1) = -7.01f;
        amat(1,0) = 100.5f;
        amat(1,1) = -234.52f;
        cmat = amat / anum;
        amat(0,0) = 7.25f;
        amat(0,1) = -3.505f;
        amat(1,0) = 50.25f;
        amat(1,1) = -117.26f;
        CHECK_EQUAL( cmat, amat );
    }

    TEST( MatrixTransposition )
    {
        using namespace gfx;
        mat amat(2,2);
        amat(0,0) = 14.5f;
        amat(0,1) = -7.01f;
        amat(1,0) = 100.5f;
        amat(1,1) = -234.52f;
        mat cmat(2,2);
        cmat(0,0) = 14.5f;
        cmat(0,1) = 100.5f;
        cmat(1,0) = -7.01f;
        cmat(1,1) = -234.52f;
        amat.transpose();
        CHECK_EQUAL( cmat, amat );
    }

    TEST( MatMapping )
    {
        using namespace gfx;
        union mock_data {
            float           values[4];
            unsigned char   bytes[sizeof(float) * 4];
        };

        mat amat(2,2);
        amat(0,0) = 8.0f;
        amat(0,1) = -2.0f;
        amat(1,0) = 0.0f;
        amat(1,1) = 10.0f;
        raw_map amat_map = amat.to_map();
        mock_data test_bytes = { {8.0f, -2.0f, 0.0f, 10.0f} };
        
        size_t i = sizeof(float) * 4;
        
        while(i) {
            --i;
            CHECK_EQUAL( test_bytes.bytes[i], amat_map[i] );
        } 
    }
}

SUITE( Matrix2Tests )
{
    TEST( Matrix2Construction )
    {
        using namespace gfx;
        mat2 amat2;
        mat2 bmat2( 0.0f, 0.0f,
                    0.0f, 0.0f );
        CHECK_EQUAL( amat2, bmat2 );
    }

    TEST( Matrix2CopyAssignment )
    {
        using namespace gfx;
        mat2 bmat2( 5.0f, -1.0f,
                    97.0f, 2.0f );
        mat2 amat2 = bmat2;
        CHECK_EQUAL( amat2, bmat2 );
        amat2(0,1) = 6.523f;
        CHECK( bmat2(0,0) != amat2(0,1) );
        CHECK( bmat2(0,1) != amat2(0,1) );
        CHECK( bmat2(1,0) != amat2(0,1) );
        CHECK( bmat2(1,1) != amat2(0,1) ); // no side effects
    }

    TEST( Matrix2Identity )
    {
        using namespace gfx;
        mat2 amat2 = mat2::identity();
        mat2 bmat2( 1.0f, 0.0f,
                    0.0f, 1.0f );
        CHECK_EQUAL( amat2, bmat2 );
    }

    TEST( Matrix2RowVectors )
    {
        using namespace gfx;
        vec2 bvec2( 5.0f, -1.0f );
        vec2 cvec2( 97.0f, 2.0f );
        mat2 amat2 = mat2::row_vectors( bvec2, cvec2 );
        mat2 bmat2( 5.0f, -1.0f,
                    97.0f, 2.0f );
        CHECK_EQUAL( amat2, bmat2 );
    }

    TEST( Matrix2ColumnVectors )
    {
        using namespace gfx;
        vec2 bvec2( 5.0f, -1.0f );
        vec2 cvec2( 97.0f, 2.0f );
        mat2 amat2 = mat2::column_vectors( bvec2, cvec2 );
        mat2 bmat2( 5.0f, 97.0f,
                    -1.0f, 2.0f );
        CHECK_EQUAL( amat2, bmat2 );
    }

    TEST( Matrix2Scale )
    {
        using namespace gfx;
        mat2 amat2 = mat2::scale( 5.0f, -1.0f );
        vec2 avec2( 5.0f, -1.0f );
        mat2 bmat2 = mat2::scale( avec2 );
        mat2 cmat2( 5.0f, 0.0f,
                    0.0f, -1.0f );
        CHECK_EQUAL( amat2, bmat2 );
        CHECK_EQUAL( bmat2, cmat2 );
        CHECK_EQUAL( amat2, cmat2 );
    }
    
    TEST( Matrix2Rotation )
    {
        using namespace gfx;
        mat2 amat2 = mat2::rotation( d_angle::in_degs( 90 ) );
        mat2 bmat2 ( 0.0f, -1.0f,
                      1.0f,  0.0f );
        CHECK_EQUAL( bmat2, amat2 );
    }

    TEST( Matrix2Lookup )
    {
        using namespace gfx;
        mat2 amat2;
        amat2(0,0) = 4.7f;
        amat2(0,1) = -5.3f;
        mat2 bmat2( 4.7f, 0.0f,
                    -5.3f, 0.0f );
        CHECK_EQUAL( amat2, bmat2 );
        CHECK_EQUAL( amat2(0,0), 4.7f );
        CHECK_EQUAL( amat2(0,1), -5.3f );
    }
    
    TEST( Matrix2ColumnLookup )
    {
        using namespace gfx;
        mat2 amat2( 4.7f, 0.0f,
                    -5.3f, 0.0f );
        vec2 avec2( 4.7f, -5.3f );
        
        vec2 bvec2 = amat2[0];
        CHECK_EQUAL( avec2, bvec2 );
        
        avec2(x) = 10.2f;
        amat2[0] = avec2;
        
        CHECK_EQUAL( avec2[0], amat2(0,0) );
        CHECK_EQUAL( avec2[1], amat2(0,1) );
        CHECK_EQUAL( avec2, amat2[0] );
        avec2(x) = 11.2f;
        CHECK( avec2(x) != amat2(0,0) );
    }

    TEST( Matrix2Addition )
    {
        using namespace gfx;
        mat2 amat2( 0.0f, 4.7f,
                    0.0f, -5.3f );
        mat2 bmat2(  4.7f, 0.0f,
                    -5.3f, 0.0f );
        CHECK( amat2 != bmat2 );
        mat2 cmat2 = amat2 + bmat2;
        mat2 dmat2(  4.7f, 4.7f,
                    -5.3f, -5.3f );
        CHECK_EQUAL( cmat2, dmat2 );
        cmat2(1,1) = 2.4f;
        CHECK( amat2(0,0) != cmat2(1,1) );
        CHECK( amat2(0,1) != cmat2(1,1) );
        CHECK( amat2(1,0) != cmat2(1,1) );
        CHECK( amat2(1,1) != cmat2(1,1) );
        CHECK( bmat2(0,0) != cmat2(1,1) );
        CHECK( bmat2(0,1) != cmat2(1,1) );
        CHECK( bmat2(1,0) != cmat2(1,1) );
        CHECK( bmat2(1,1) != cmat2(1,1) ); // no side effects
    }

    TEST( Matrix2Negation )
    {
        using namespace gfx;
        mat2 amat2( 0.0f, 4.7f,
                    0.0f, -5.3f );
        mat2 bmat2( 0.0f, -4.7f,
                    0.0f, 5.3f );
        mat2 cmat2 = -amat2;
        CHECK_EQUAL( cmat2, bmat2 );
        cmat2(1,1) = 2.4f;
        CHECK( amat2(0,0) != cmat2(1,1) );
        CHECK( amat2(0,1) != cmat2(1,1) );
        CHECK( amat2(1,0) != cmat2(1,1) );
        CHECK( amat2(1,1) != cmat2(1,1) ); // no side effects
    }

    TEST( Matrix2Subtraction )
    {
        using namespace gfx;
        mat2 amat2( 0.0f, 4.7f,
                    0.0f, -5.3f );
        mat2 bmat2(  4.7f, 0.0f,
                    -5.3f, 0.0f );
        CHECK( amat2 != bmat2 );
        mat2 cmat2 = amat2 - bmat2;
        mat2 dmat2( -4.7f, 4.7f,
                    5.3f, -5.3f );
        CHECK_EQUAL( cmat2, dmat2 );
        cmat2(1,1) = 2.4f;
        CHECK( amat2(0,0) != cmat2(1,1) );
        CHECK( amat2(0,1) != cmat2(1,1) );
        CHECK( amat2(1,0) != cmat2(1,1) );
        CHECK( amat2(1,1) != cmat2(1,1) );
        CHECK( bmat2(0,0) != cmat2(1,1) );
        CHECK( bmat2(0,1) != cmat2(1,1) );
        CHECK( bmat2(1,0) != cmat2(1,1) );
        CHECK( bmat2(1,1) != cmat2(1,1) ); // no side effects
    }

    TEST( Matrix2Multiplication )
    {
        using namespace gfx;
        mat2 amat2 = mat2::identity();
        mat2 bmat2( 14.5f, 100.5f,
                    -7.01f, -234.52f );
        CHECK( amat2 != bmat2 );
        mat2 cmat2 = amat2 * bmat2;
        CHECK_EQUAL( cmat2, bmat2 );
        cmat2(1,1) = 2.4f;
        CHECK( amat2(0,0) != cmat2(1,1) );
        CHECK( amat2(0,1) != cmat2(1,1) );
        CHECK( amat2(1,0) != cmat2(1,1) );
        CHECK( amat2(1,1) != cmat2(1,1) ); // no side effects
        CHECK( bmat2(0,0) != cmat2(1,1) );
        CHECK( bmat2(0,1) != cmat2(1,1) );
        CHECK( bmat2(1,0) != cmat2(1,1) );
        CHECK( bmat2(1,1) != cmat2(1,1) ); // no side effects
        mat2 dmat2( -2.0f, 1.0f,
                    4.0f, 0.0f );
        mat2 emat2( 3.0f, 0.2f,
                    -1.0f, 100.0f );
        cmat2 = dmat2 * emat2;
        mat2 mat2( -7.0f, 99.6f,
                    12.0f, 0.8f );
        CHECK_EQUAL( cmat2, mat2 );
        cmat2(1,1) = 2.4f;
        CHECK( dmat2(0,0) != cmat2(1,1) );
        CHECK( dmat2(0,1) != cmat2(1,1) );
        CHECK( dmat2(1,0) != cmat2(1,1) );
        CHECK( dmat2(1,1) != cmat2(1,1) ); // no side effects
        CHECK( emat2(0,0) != cmat2(1,1) );
        CHECK( emat2(0,1) != cmat2(1,1) );
        CHECK( emat2(1,0) != cmat2(1,1) );
        CHECK( emat2(1,1) != cmat2(1,1) ); // no side effects
    }
    
    TEST( Matrix2Mult3x2 )
    {
        using namespace gfx;
        mat2 amat2 = mat2::identity();
        mat3x2 amat3x2( 14.5f,   100.5f,   5.0f,
                      -7.01f, -234.52f, -2.0f );
        mat3x2 bmat3x2 = amat2 * amat3x2;
        CHECK_EQUAL( amat3x2, bmat3x2 );
    }
    
    TEST( Matrix2Mult4x2 )
    {
        using namespace gfx;
        mat2 amat2 = mat2::identity();
        mat4x2 amat4x2( 14.5f,   100.5f,   5.0f, 7.0f,
                        -7.01f, -234.52f, -2.0f, 11.0f );
        mat4x2 bmat4x2 = amat2 * amat4x2;
        CHECK_EQUAL( amat4x2, bmat4x2 );
    }
    
    TEST( Matrix2VectorMultiplication )
    {
        using namespace gfx;
        mat2 amat2 = mat2::identity();
        mat2 bmat2( 2.0f, 100.0f,
                    -7.0f, -10.0f );
        vec2 avec2( 2.0f, 1.0f );
        vec2 bvec2 = amat2 * avec2;
        CHECK_EQUAL( avec2, bvec2 );
        bvec2 = avec2 * amat2;
        CHECK_EQUAL( avec2, bvec2 );
        
        vec2 cvec2( 104.0f, -24.0f );
        bvec2 = bmat2 * avec2;
        CHECK_EQUAL( cvec2, bvec2 );

        vec2 dvec2( -3.0f, 190.0f );
        bvec2 = avec2 * bmat2;
        CHECK_EQUAL( dvec2, bvec2 );
    }

    TEST( Matrix2ScalarMultiplication )
    {
        using namespace gfx;
        mat2 amat2( 14.5f, 100.5f,
                    -7.01f, -234.52f );
        mat2 bmat2( 29.0f, 201.0f,
                    -14.02f, -469.04f );
        mat2 cmat2 = amat2 * 2.0f;
        CHECK_EQUAL( cmat2, bmat2 );
        cmat2(1,1) = 2.4f;
        CHECK( amat2(0,0) != cmat2(1,1) );
        CHECK( amat2(0,1) != cmat2(1,1) );
        CHECK( amat2(1,0) != cmat2(1,1) );
        CHECK( amat2(1,1) != cmat2(1,1) ); // no side effects
        
        cmat2 = 2.0f * amat2;
        CHECK_EQUAL( cmat2, bmat2 );
        cmat2(1,1) = 2.4f;
        CHECK( amat2(0,0) != cmat2(1,1) );
        CHECK( amat2(0,1) != cmat2(1,1) );
        CHECK( amat2(1,0) != cmat2(1,1) );
        CHECK( amat2(1,1) != cmat2(1,1) ); // no side effects
    }

    TEST( Matrix2ScalarDivision )
    {
        using namespace gfx;
        mat2 amat2( 29.0f, 201.0f,
                    -14.02f, -469.04f );
        mat2 bmat2( 14.5f, 100.5f,
                    -7.01f, -234.52f );
        mat2 cmat2 = amat2 / 2.0f;
        CHECK_EQUAL( cmat2, bmat2 );
        cmat2(1,1) = 2.4f;
        CHECK( amat2(0,0) != cmat2(1,1) );
        CHECK( amat2(0,1) != cmat2(1,1) );
        CHECK( amat2(1,0) != cmat2(1,1) );
        CHECK( amat2(1,1) != cmat2(1,1) ); // no side effects
    }

    TEST( Matrix2InPlaceFill )
    {
        using namespace gfx;
        mat2 amat2;
        mat2 bmat2( 2.5f, 2.5f,
                    2.5f, 2.5f );
        amat2.fill( 2.5f );
        CHECK_EQUAL( amat2, bmat2 );
        // make sure a reference is returned
        amat2.fill(3.0f)(0,0) = 2.1f;
        mat2 cmat2( 2.1f, 3.0f,
                    3.0f, 3.0f );
        CHECK_EQUAL( amat2, cmat2 );
    }

    TEST( Matrix2InPlaceTranspose )
    {
        using namespace gfx;
        mat2 amat2( 3.4f, -0.3f,
                    2.4f, -1.0f );
        mat2 bmat2( 3.4f, 2.4f,
                    -0.3f, -1.0f );
        amat2.transpose();
        CHECK_EQUAL( amat2, bmat2 );
        // make sure a reference is returned
        amat2.transpose()(0,0) = 2.1f;
        mat2 cmat2( 2.1f, -0.3f,
                    2.4f, -1.0f );
        CHECK_EQUAL( amat2, cmat2 );
    }

    TEST( Matrix2RowLookup )
    {
        using namespace gfx;
        mat2 amat2( 3.4f, -0.3f,
                    2.4f, -1.0f );
        vec2 avec2( -10.0f, 4.5f );
        mat2 bmat2( 3.4f, -0.3f,
                    -10.0f, 4.5f );
        amat2.row( 1, avec2 );
        CHECK_EQUAL( amat2, bmat2 );
        // make sure a reference is returned
        mat2 cmat2(  -20.1f, 3.1f,
                    -10.0f, 8.1f );
        vec2 bvec2( -20.1f, 3.1f );
        amat2.row( 0, bvec2 )( 1, 1 ) = 8.1f;
        CHECK_EQUAL( amat2, cmat2 );
        
        vec2 cvec2 = amat2.row(0);
        CHECK_EQUAL( cvec2, bvec2 );
    }

    TEST( Matrix2ColumnAccess )
    {
        using namespace gfx;
        mat2 amat2( 3.4f, -0.3f,
                    2.4f, -1.0f );
        vec2 avec2( -10.0f, 4.5f );
        mat2 bmat2( 3.4f, -10.0f,
                    2.4f, 4.5f );
        amat2.column( 1, avec2 );
        CHECK_EQUAL( amat2, bmat2 );
        // make sure a reference is returned
        mat2 cmat2(  -20.1f, -10.0f,
                    3.1f, 8.1f );
        vec2 bvec2( -20.1f, 3.1f );
        amat2.column( 0, bvec2 )( 1, 1 ) = 8.1f;
        CHECK_EQUAL( amat2, cmat2 );
        
        vec2 cvec2 = amat2.column(0);
        CHECK_EQUAL( cvec2, bvec2 );
    }

    TEST( Matrix2MultiRowAssignment )
    {
        using namespace gfx;
        mat2 amat2;
        mat2 bmat2( 3.4f, -0.3f,
                    2.4f, -1.0f );
        vec2 avec2( 3.4f, -0.3f );
        vec2 bvec2( 2.4f, -1.0f );
        amat2.rows( avec2, bvec2 );
        CHECK_EQUAL( amat2, bmat2 );
    }

    TEST( Matrix2MultiColumnAssignment )
    {
        using namespace gfx;
        mat2 amat2;
        mat2 bmat2( 3.4f, -0.3f,
                    2.4f, -1.0f );
        vec2 avec2( 3.4f, 2.4f );
        vec2 bvec2( -0.3f, -1.0f );
        amat2.columns( avec2, bvec2 );
        CHECK_EQUAL( amat2, bmat2 );
    }

    TEST( Matrix2Mapping )
    {
        using namespace gfx;
        union mock_data {
            float           values[4];
            unsigned char   bytes[sizeof(float) * 4];
        };

        mat2 amat2( 8.0f,  0.0f,
                    -2.0f, 10.0f );
        raw_map amat2_map = amat2.to_map();
        mock_data test_bytes = { {8.0f, -2.0f, 0.0f, 10.0f} };
        
        size_t i = sizeof(float) * 4;
        
        while(i) {
            --i;
            CHECK_EQUAL( test_bytes.bytes[i], amat2_map[i] );
        } 
    }
}

SUITE( Matrix3Tests )
{
    TEST( Matrix3Construction )
    {
        using namespace gfx;
        mat3 amat3;
        mat3 bmat3( 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f );
        CHECK_EQUAL( amat3, bmat3 );
    }

    TEST( Matrix3CopyAssignment )
    {
        using namespace gfx;
        mat3 bmat3( 5.0f, -1.0f, 6.0f,
                    97.0f, 2.0f, 3.2f,
                    -8.0f, 3.4f, 1.0f );
        mat3 amat3 = bmat3;
        CHECK_EQUAL( amat3, bmat3 );
        amat3(1,1) = 6.523f;
        CHECK( bmat3(0,0) != amat3(1,1) );
        CHECK( bmat3(0,1) != amat3(1,1) );
        CHECK( bmat3(0,2) != amat3(1,1) );
        CHECK( bmat3(1,0) != amat3(1,1) );
        CHECK( bmat3(1,1) != amat3(1,1) );
        CHECK( bmat3(1,2) != amat3(1,1) );
        CHECK( bmat3(2,0) != amat3(1,1) );
        CHECK( bmat3(2,1) != amat3(1,1) );
        CHECK( bmat3(2,2) != amat3(1,1) ); // no side effects
    }

    TEST( Matrix3Identity )
    {
        using namespace gfx;
        mat3 amat3 = mat3::identity();
        mat3 bmat3( 1.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 1.0f );
        CHECK_EQUAL( amat3, bmat3 );
    }

    TEST( Matrix3RowVectors )
    {
        using namespace gfx;
        vec3 avec3( 5.0f, -1.0f, 6.7f );
        vec3 bvec3( 97.0f, 2.0f, 2.3f );
        vec3 cvec3( -5.6f, 12.0f, 4.5f );
        mat3 amat3 = mat3::row_vectors( avec3, bvec3, cvec3 );
        mat3 bmat3(  5.0f, -1.0f, 6.7f,
                    97.0f,  2.0f, 2.3f,
                    -5.6f, 12.0f, 4.5f );
        CHECK_EQUAL( amat3, bmat3 );
    } 

    TEST( Matrix3ColumnVectors )
    {
        using namespace gfx;
        vec3 avec3( 5.0f, -1.0f, 6.7f );
        vec3 bvec3( 97.0f, 2.0f, 2.3f );
        vec3 cvec3( -5.6f, 12.0f, 4.5f );
        mat3 amat3 = mat3::column_vectors( avec3, bvec3, cvec3 );
        mat3 bmat3(  5.0f, 97.0f, -5.6f,
                    -1.0f,  2.0f, 12.0f,
                    6.7f,  2.3f,  4.5f );
        CHECK_EQUAL( amat3, bmat3 );
    }
    
    TEST( Matrix3Square )
    {
        using namespace gfx;
        vec3 avec3( 3.0f, 4.0f, -2.0f );
        mat3 amat3 = mat3::square( avec3 );
        mat3 bmat3(  9.0f, 12.0f, -6.0f,
                     12.0f, 16.0f, -8.0f,
                     -6.0f, -8.0f,  4.0f );
        CHECK_EQUAL( bmat3, amat3 );
    }

    TEST( Matrix3Scale )
    {
        using namespace gfx;
        mat3 amat3 = mat3::scale( 5.0f, -1.0f, 4.0f );
        vec3 avec3( 5.0f, -1.0f, 4.0f );
        mat3 bmat3 = mat3::scale( avec3 );
        mat3 cmat3( 5.0f,  0.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,
                    0.0f,  0.0f, 4.0f );
        CHECK_EQUAL( amat3, bmat3 );
        CHECK_EQUAL( bmat3, cmat3 );
        CHECK_EQUAL( amat3, cmat3 );
        
        amat3 = mat3::scale( 5.0f, -1.0f );
        vec2 avec2( 5.0f, -1.0f );
        bmat3 = mat3::scale( avec2 );
        cmat3 = mat3( 5.0f,  0.0f, 0.0f,
                       0.0f, -1.0f, 0.0f,
                       0.0f,  0.0f, 1.0f );
        CHECK_EQUAL( amat3, bmat3 );
        CHECK_EQUAL( bmat3, cmat3 );
        CHECK_EQUAL( amat3, cmat3 );
    }
    
    TEST( Matrix3Translate )
    {
        using namespace gfx;
        mat3 amat3 = mat3::translate( 5.0f, -1.0f );
        vec2 avec2( 5.0f, -1.0f );
        mat3 bmat3 = mat3::translate( avec2 );
        mat3 cmat3( 1.0f, 0.0f,  5.0f,
                     0.0f, 1.0f, -1.0f,
                     0.0f, 0.0f,  1.0f  );
        CHECK_EQUAL( cmat3, amat3 );
        CHECK_EQUAL( cmat3, bmat3 );
        CHECK_EQUAL( amat3, bmat3 );
    }
    
    TEST( Matrix3CrossProduct )
    {
        using namespace gfx;
        vec3 avec3( 3.0f, 4.0f, -2.0f );
        mat3 amat3 = mat3::cross_product( avec3 );
        mat3 bmat3(  0.0f, 2.0f,  4.0f,
                     -2.0f, 0.0f, -3.0f,
                     -4.0f, 3.0f,  0.0f );
        CHECK_EQUAL( bmat3, amat3 );
    }
    
    TEST( Matrix3Rotation )
    {
        using namespace gfx;
        vec3 axis( 1.0f, 0.0f, 0.0f );
        d_angle angx = d_angle::in_degs( 90.0f );
        mat3 amat3 = mat3::rotation( axis, angx );
        mat3 bmat3 = mat3::rotation( angx,
                                       d_angle::in_degs( 0.0 ),
                                       d_angle::in_degs( 0.0 ) );
        mat3 cmat3 = mat3::rotation( qutn::rotation( axis, angx ) );
        mat3 dmat3(  1.0f, 0.0f,  0.0f,
                      0.0f, 0.0f, -1.0f,
                      0.0f, 1.0f,  0.0f );
        CHECK_EQUAL( dmat3, amat3 );
        CHECK_EQUAL( dmat3, bmat3 );
        CHECK_EQUAL( dmat3, cmat3 );
    }

    TEST( Matrix3Lookup )
    {
        using namespace gfx;
        mat3 amat3;
        amat3(0,0) = 4.7f;
        amat3(0,2) = -5.3f;
        mat3 bmat3( 4.7f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f,
                    -5.3f, 0.0f, 0.0f );
        CHECK_EQUAL( amat3, bmat3 );
        CHECK_EQUAL( amat3(0,0), 4.7f );
        CHECK_EQUAL( amat3(0,2), -5.3f );
    }
    
    TEST( Matrix3ColumnLookup )
    {
        using namespace gfx;
        mat3 amat3( 4.7f, 0.0f, 0.0f,
                    -5.3f, 0.0f, 0.0f,
                     1.5f, 0.0f, 0.0f );
        vec3 avec3( 4.7f, -5.3f, 1.5f );
        
        vec3 bvec3 = amat3[0];
        CHECK_EQUAL( avec3, bvec3 );
        
        avec3(z) = 10.2f;
        amat3[0] = avec3;
        
        CHECK_EQUAL( avec3[0], amat3(0,0) );
        CHECK_EQUAL( avec3[1], amat3(0,1) );
        CHECK_EQUAL( avec3[2], amat3(0,2) );
        CHECK_EQUAL( avec3, amat3[0] );
        avec3(x) = 11.2f;
        CHECK( avec3(x) != amat3(0,0) );
    }

    TEST( Matrix3Addition )
    {
        using namespace gfx;
        mat3 amat3( 0.0f,  4.7f, 56.7f,
                    0.0f, -0.2f,  6.4f,
                    0.0f, -5.3f, 12.1f );
        mat3 bmat3(   4.7f, 0.0f, 0.0f,
                    13.1f, 0.0f, 0.0f,
                    -5.3f, 0.0f, 0.0f );
        CHECK( amat3 != bmat3 );
        mat3 cmat3 = amat3 + bmat3;
        mat3 dmat3(  4.7f,  4.7f, 56.7f,
                    13.1f, -0.2f,  6.4f,
                    -5.3f, -5.3f, 12.1f );
        CHECK_EQUAL( cmat3, dmat3 );
        cmat3(1,1) = 2.4f;
        CHECK( amat3(0,0) != cmat3(1,1) );
        CHECK( amat3(0,1) != cmat3(1,1) );
        CHECK( amat3(0,2) != cmat3(1,1) );
        CHECK( amat3(1,0) != cmat3(1,1) );
        CHECK( amat3(1,1) != cmat3(1,1) );
        CHECK( amat3(1,2) != cmat3(1,1) );
        CHECK( amat3(2,0) != cmat3(1,1) );
        CHECK( amat3(2,1) != cmat3(1,1) );
        CHECK( amat3(2,2) != cmat3(1,1) ); 
        CHECK( bmat3(0,0) != cmat3(1,1) );
        CHECK( bmat3(0,1) != cmat3(1,1) );
        CHECK( bmat3(0,2) != cmat3(1,1) );
        CHECK( bmat3(1,0) != cmat3(1,1) );
        CHECK( bmat3(1,1) != cmat3(1,1) );
        CHECK( bmat3(1,2) != cmat3(1,1) );
        CHECK( bmat3(2,0) != cmat3(1,1) );
        CHECK( bmat3(2,1) != cmat3(1,1) );
        CHECK( bmat3(2,2) != cmat3(1,1) );  // no side effects
    }

    TEST( Matrix3Negation )
    {
        using namespace gfx;
        mat3 amat3( 0.0f,  4.7f, 56.7f,
                    0.0f, -0.2f,  6.4f,
                    0.0f, -5.3f, 12.1f );
        mat3 bmat3( 0.0f, -4.7f, -56.7f,
                    0.0f,  0.2f,  -6.4f,
                    0.0f,  5.3f, -12.1f );
        mat3 cmat3 = -amat3;
        CHECK_EQUAL( cmat3, bmat3 );
        cmat3(1,1) = 2.4f;
        CHECK( amat3(0,0) != cmat3(1,1) );
        CHECK( amat3(0,1) != cmat3(1,1) );
        CHECK( amat3(0,2) != cmat3(1,1) );
        CHECK( amat3(1,0) != cmat3(1,1) );
        CHECK( amat3(1,1) != cmat3(1,1) );
        CHECK( amat3(1,2) != cmat3(1,1) );
        CHECK( amat3(2,0) != cmat3(1,1) );
        CHECK( amat3(2,1) != cmat3(1,1) );
        CHECK( amat3(2,2) != cmat3(1,1) ); 
        CHECK( bmat3(0,0) != cmat3(1,1) );
        CHECK( bmat3(0,1) != cmat3(1,1) );
        CHECK( bmat3(0,2) != cmat3(1,1) );
        CHECK( bmat3(1,0) != cmat3(1,1) );
        CHECK( bmat3(1,1) != cmat3(1,1) );
        CHECK( bmat3(1,2) != cmat3(1,1) );
        CHECK( bmat3(2,0) != cmat3(1,1) );
        CHECK( bmat3(2,1) != cmat3(1,1) );
        CHECK( bmat3(2,2) != cmat3(1,1) );  // no side effects
    }

    TEST( Matrix3Subtraction )
    {
        using namespace gfx;
        mat3 amat3( 0.0f,  4.7f, 56.7f,
                    0.0f, -0.2f,  6.4f,
                    0.0f, -5.3f, 12.1f );
        mat3 bmat3(   4.7f, 0.0f, 0.0f,
                    13.1f, 0.0f, 0.0f,
                    -5.3f, 0.0f, 0.0f );
        CHECK( amat3 != bmat3 );
        mat3 cmat3 = amat3 - bmat3;
        mat3 dmat3(  -4.7f,  4.7f, 56.7f,
                    -13.1f, -0.2f,  6.4f,
                    5.3f, -5.3f, 12.1f );
        CHECK_EQUAL( cmat3, dmat3 );
        cmat3(1,1) = 2.4f;
        CHECK( amat3(0,0) != cmat3(1,1) );
        CHECK( amat3(0,1) != cmat3(1,1) );
        CHECK( amat3(0,2) != cmat3(1,1) );
        CHECK( amat3(1,0) != cmat3(1,1) );
        CHECK( amat3(1,1) != cmat3(1,1) );
        CHECK( amat3(1,2) != cmat3(1,1) );
        CHECK( amat3(2,0) != cmat3(1,1) );
        CHECK( amat3(2,1) != cmat3(1,1) );
        CHECK( amat3(2,2) != cmat3(1,1) ); 
        CHECK( bmat3(0,0) != cmat3(1,1) );
        CHECK( bmat3(0,1) != cmat3(1,1) );
        CHECK( bmat3(0,2) != cmat3(1,1) );
        CHECK( bmat3(1,0) != cmat3(1,1) );
        CHECK( bmat3(1,1) != cmat3(1,1) );
        CHECK( bmat3(1,2) != cmat3(1,1) );
        CHECK( bmat3(2,0) != cmat3(1,1) );
        CHECK( bmat3(2,1) != cmat3(1,1) );
        CHECK( bmat3(2,2) != cmat3(1,1) );  // no side effects
    } 

    TEST( Matrix3Multiplication )
    {
        using namespace gfx;
        mat3 amat3 = mat3::identity();
        mat3 bmat3( 14.5f,   100.5f,   97.4f,
                    -7.01f, -234.52f, 837.4f,
                    67.0f,    83.7f,   -0.33f );
        CHECK( amat3 != bmat3 );
        mat3 cmat3 = amat3 * bmat3;
        CHECK_EQUAL( cmat3, bmat3 );
        cmat3(1,1) = 2.4f;
        CHECK( amat3(0,0) != cmat3(1,1) );
        CHECK( amat3(0,1) != cmat3(1,1) );
        CHECK( amat3(0,2) != cmat3(1,1) );
        CHECK( amat3(1,0) != cmat3(1,1) );
        CHECK( amat3(1,1) != cmat3(1,1) );
        CHECK( amat3(1,2) != cmat3(1,1) );
        CHECK( amat3(2,0) != cmat3(1,1) );
        CHECK( amat3(2,1) != cmat3(1,1) );
        CHECK( amat3(2,2) != cmat3(1,1) ); 
        CHECK( bmat3(0,0) != cmat3(1,1) );
        CHECK( bmat3(0,1) != cmat3(1,1) );
        CHECK( bmat3(0,2) != cmat3(1,1) );
        CHECK( bmat3(1,0) != cmat3(1,1) );
        CHECK( bmat3(1,1) != cmat3(1,1) );
        CHECK( bmat3(1,2) != cmat3(1,1) );
        CHECK( bmat3(2,0) != cmat3(1,1) );
        CHECK( bmat3(2,1) != cmat3(1,1) );
        CHECK( bmat3(2,2) != cmat3(1,1) );  // no side effects
        
        mat3 dmat3( -2.0f, 1.0f,  3.0f,
                    4.0f, 0.0f,  0.0f,
                    5.0f, 9.0f, -4.0f );
        mat3 emat3(   3.0f,   0.2f, -0.1f,
                    -1.0f, 100.0f, -0.5f,
                    10.0f,  -2.0f,  5.0f );
        cmat3 = dmat3 * emat3;
        mat3 mat3(  23.0f,  93.6f,  14.7f,
                    12.0f,   0.8f,  -0.4f,
                    -34.0f, 909.0f, -25.0f );
        CHECK_EQUAL( mat3, cmat3 );
        cmat3(1,1) = 2.4f;
        CHECK( dmat3(0,0) != cmat3(1,1) );
        CHECK( dmat3(0,1) != cmat3(1,1) );
        CHECK( dmat3(0,2) != cmat3(1,1) );
        CHECK( dmat3(1,0) != cmat3(1,1) );
        CHECK( dmat3(1,1) != cmat3(1,1) );
        CHECK( dmat3(1,2) != cmat3(1,1) );
        CHECK( dmat3(2,0) != cmat3(1,1) );
        CHECK( dmat3(2,1) != cmat3(1,1) );
        CHECK( dmat3(2,2) != cmat3(1,1) ); 
        CHECK( emat3(0,0) != cmat3(1,1) );
        CHECK( emat3(0,1) != cmat3(1,1) );
        CHECK( emat3(0,2) != cmat3(1,1) );
        CHECK( emat3(1,0) != cmat3(1,1) );
        CHECK( emat3(1,1) != cmat3(1,1) );
        CHECK( emat3(1,2) != cmat3(1,1) );
        CHECK( emat3(2,0) != cmat3(1,1) );
        CHECK( emat3(2,1) != cmat3(1,1) );
        CHECK( emat3(2,2) != cmat3(1,1) ); // no side effects
    }
    
    TEST( Matrix3Mult2x3 )
    {
        using namespace gfx;
        mat3 amat3 = mat3::identity();
        mat2x3 amat2x3( 14.5f,   100.5f, 
                        -7.01f, -234.52f,
                         5.0f,    -2.0f );
        mat2x3 bmat2x3 = amat3 * amat2x3;
        CHECK_EQUAL( amat2x3, bmat2x3 );
    }
    
    TEST( Matrix3Mult4x3 )
    {
        using namespace gfx;
        mat3 amat3 = mat3::identity();
        mat4x3 amat4x3( 14.5f,   100.5f,   2.0f, 654.0f,
                        -7.01f, -234.52f, 11.0f, -67.0f,
                         5.0f,    -2.0f,  -5.0f, 354.3f );
        mat4x3 bmat4x3 = amat3 * amat4x3;
        CHECK_EQUAL( amat4x3, bmat4x3 );
    }
    
    
    TEST( Matrix3VectorMultiplication )
    {
        using namespace gfx;
        mat3 amat3 = mat3::identity();
        mat3 bmat3( 2.0f, 100.0f,  1.0f,
                     4.0f,  15.0f, -1.0f,
                    -7.0f, -10.0f,  5.0f );
        vec3 avec3( 2.0f, 1.0f, -1.0f );
        vec3 bvec3 = amat3 * avec3;
        CHECK_EQUAL( avec3, bvec3 );
        bvec3 = avec3 * amat3;
        CHECK_EQUAL( avec3, bvec3 );
        
        vec3 cvec3( 103.0f, 24.0f, -29.0f );
        bvec3 = bmat3 * avec3;
        CHECK_EQUAL( cvec3, bvec3 );

        vec3 dvec3( 15.0f, 225.0f, -4.0f );
        bvec3 = avec3 * bmat3;
        CHECK_EQUAL( dvec3, bvec3 );
    }

    TEST( Matrix3ScalarMultiplication )
    {
        using namespace gfx;
        mat3 amat3( 14.5f,   100.5f,  20.0f,
                    -7.01f, -234.52f, 10.0f,
                    2.0f,     3.1f,  -5.1f );
        mat3 bmat3( 29.0f,   201.0f,  40.0f,
                    -14.02f, -469.04f, 20.0f,
                    4.0f,     6.2f, -10.2f );
        mat3 cmat3 = amat3 * 2.0f;
        CHECK_EQUAL( cmat3, bmat3 );
        cmat3(1,1) = 2.4f;
        CHECK( amat3(0,0) != cmat3(1,1) );
        CHECK( amat3(0,1) != cmat3(1,1) );
        CHECK( amat3(0,2) != cmat3(1,1) );
        CHECK( amat3(1,0) != cmat3(1,1) );
        CHECK( amat3(1,1) != cmat3(1,1) );
        CHECK( amat3(1,2) != cmat3(1,1) );
        CHECK( amat3(2,0) != cmat3(1,1) );
        CHECK( amat3(2,1) != cmat3(1,1) );
        CHECK( amat3(2,2) != cmat3(1,1) ); // no side effects
        
        cmat3 = 2.0f * amat3;
        CHECK_EQUAL( cmat3, bmat3 );
        cmat3(1,1) = 2.4f;
        CHECK( amat3(0,0) != cmat3(1,1) );
        CHECK( amat3(0,1) != cmat3(1,1) );
        CHECK( amat3(0,2) != cmat3(1,1) );
        CHECK( amat3(1,0) != cmat3(1,1) );
        CHECK( amat3(1,1) != cmat3(1,1) );
        CHECK( amat3(1,2) != cmat3(1,1) );
        CHECK( amat3(2,0) != cmat3(1,1) );
        CHECK( amat3(2,1) != cmat3(1,1) );
        CHECK( amat3(2,2) != cmat3(1,1) ); // no side effects
    }

    TEST( Matrix3ScalarDivision )
    {
        using namespace gfx;
        mat3 amat3( 29.0f,   201.0f,  40.0f,
                    -14.02f, -469.04f, 20.0f,
                    4.0f,     6.2f, -10.2f );
        mat3 bmat3( 14.5f,   100.5f,  20.0f,
                    -7.01f, -234.52f, 10.0f,
                    2.0f,     3.1f,  -5.1f );
        mat3 cmat3 = amat3 / 2.0f;
        CHECK_EQUAL( cmat3, bmat3 );
        cmat3(1,1) = 2.4f;
        CHECK( amat3(0,0) != cmat3(1,1) );
        CHECK( amat3(0,1) != cmat3(1,1) );
        CHECK( amat3(0,2) != cmat3(1,1) );
        CHECK( amat3(1,0) != cmat3(1,1) );
        CHECK( amat3(1,1) != cmat3(1,1) );
        CHECK( amat3(1,2) != cmat3(1,1) );
        CHECK( amat3(2,0) != cmat3(1,1) );
        CHECK( amat3(2,1) != cmat3(1,1) );
        CHECK( amat3(2,2) != cmat3(1,1) ); // no side effects
    }

    TEST( Matrix3InPlaceFill )
    {
        using namespace gfx;
        mat3 amat3;
        mat3 bmat3( 2.5f, 2.5f, 2.5f,
                    2.5f, 2.5f, 2.5f,
                    2.5f, 2.5f, 2.5f );
        amat3.fill( 2.5f );
        CHECK_EQUAL( amat3, bmat3 );
        // make sure a reference is returned
        amat3.fill(3.0f)(0,0) = 2.1f;
        mat3 cmat3( 2.1f, 3.0f, 3.0f,
                    3.0f, 3.0f, 3.0f,
                    3.0f, 3.0f, 3.0f );
        CHECK_EQUAL( amat3, cmat3 );
    }

    TEST( Matrix3InPlaceTranspose )
    {
        using namespace gfx;
        mat3 amat3( 3.4f, -0.3f,  17.0f,
                    8.3f,  6.1f,  -1.06f,
                    2.4f, -1.0f,   2.6f );
        mat3 bmat3(  3.4f,  8.3f,   2.4f,
                    -0.3f,  6.1f,  -1.0f,
                    17.0f, -1.06f,  2.6f );
        amat3.transpose();
        CHECK_EQUAL( amat3, bmat3 );
        // make sure a reference is returned
        amat3.transpose()(0,0) = 2.1f;
        mat3 cmat3( 2.1f, -0.3f,  17.0f,
                    8.3f,  6.1f,  -1.06f,
                    2.4f, -1.0f,   2.6f );
        CHECK_EQUAL( amat3, cmat3 );
    }

    TEST( Matrix3RowLookup )
    {
        using namespace gfx;
        mat3 amat3( 3.4f, -0.3f, 17.0f,
                    8.3f, 6.1f, -1.06f,
                    2.4f, -1.0f, 2.6f );
        vec3 avec3( -10.0f, 4.5f, 2.3f );
        mat3 bmat3( 3.4f, -0.3f, 17.0f,
                    -10.0f, 4.5f, 2.3f,
                    2.4f, -1.0f, 2.6f );
        amat3.row( 1, avec3 );
        CHECK_EQUAL( amat3, bmat3 );
        // make sure a reference is returned
        mat3 cmat3( -20.1f, 3.1f, 7.8f,
                    -10.0f, 8.1f, 2.3f,
                    2.4f, -1.0f, 2.6f );
        vec3 bvec3( -20.1f, 3.1f, 7.8f );
        amat3.row( 0, bvec3 )( 1, 1 ) = 8.1f;
        CHECK_EQUAL( amat3, cmat3 );
        
        vec3 cvec3 = amat3.row(0);
        CHECK_EQUAL( cvec3, bvec3 );
    }

    TEST( Matrix3ColumnAccess )
    {
        using namespace gfx;
        mat3 amat3( 3.4f, -0.3f, 17.0f,
                    8.3f, 6.1f, -1.06f,
                    2.4f, -1.0f, 2.6f );
        vec3 avec3( -10.0f, 4.5f, 2.3f );
        mat3 bmat3( 3.4f, -10.0f, 17.0f,
                    8.3f, 4.5f, -1.06f,
                    2.4f, 2.3f, 2.6f );
        amat3.column( 1, avec3 );
        CHECK_EQUAL( amat3, bmat3 );
        // make sure a reference is returned
        mat3 cmat3( -20.1f, -10.0f, 17.0f,
                    3.1f, 8.1f, -1.06f,
                    7.8f, 2.3f, 2.6f );
        vec3 bvec3( -20.1f, 3.1f, 7.8f );
        amat3.column( 0, bvec3 )( 1, 1 ) = 8.1f;
        CHECK_EQUAL( amat3, cmat3 );
        
        vec3 cvec3 = amat3.column(0);
        CHECK_EQUAL( cvec3, bvec3 );
    }

    TEST( Matrix3MultiRowAssignment )
    {
        using namespace gfx;
        mat3 amat3;
        mat3 bmat3( 3.4f, -0.3f, 17.0f,
                    8.3f, 6.1f, -1.06f,
                    2.4f, -1.0f, 2.6f );
        vec3 avec3( 3.4f, -0.3f, 17.0f );
        vec3 bvec3( 8.3f, 6.1f, -1.06f );
        vec3 cvec3( 2.4f, -1.0f, 2.6f );
        amat3.rows( avec3, bvec3, cvec3 );
        CHECK_EQUAL( amat3, bmat3 );
    }

    TEST( Matrix3MultiColumnAssignment )
    {
        using namespace gfx;
        mat3 amat3;
        mat3 bmat3( 3.4f, -0.3f, 17.0f,
                    8.3f, 6.1f, -1.06f,
                    2.4f, -1.0f, 2.6f );
        vec3 avec3( 3.4f, 8.3f, 2.4f );
        vec3 bvec3( -0.3f, 6.1f, -1.0f );
        vec3 cvec3( 17.0f, -1.06f, 2.6f );
        amat3.columns( avec3, bvec3, cvec3 );
        CHECK_EQUAL( amat3, bmat3 );
    }

    TEST( Matrix3Mapping )
    {
        using namespace gfx;
        union mock_data {
            float           values[9];
            unsigned char   bytes[sizeof(float) * 9];
        };

        mat3 amat3(  8.0f,  0.0f,  1.0f,
                    16.0f,  2.0f, -3.0f,
                    -2.0f, 10.0f,  5.5f );
        raw_map amat3_map = amat3.to_map();
        mock_data test_bytes = { { 8.0f, 16.0f, -2.0f,
                                0.0f,  2.0f, 10.0f,
                                1.0f, -3.0f,  5.5f } };
        
        size_t i = sizeof(float) * 9;
        
        while(i) {
            --i;
            CHECK_EQUAL( test_bytes.bytes[i], amat3_map[i] );
        } 
    }
}

SUITE( Matrix4Tests )
{
    TEST( Matrix4Construction )
    {
        using namespace gfx;
        mat4 amat4;
        mat4 bmat4( 0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f );
        CHECK_EQUAL( amat4, bmat4 );
    }

    TEST( Matrix4CopyAssignment )
    {
        using namespace gfx;
        mat4 bmat4(  5.0f, -1.0f, 6.0f, -1.0f,
                    97.0f,  2.0f, 3.2f,  7.1f,
                    -8.0f,  3.4f, 1.0f, -1.5f,
                    89.02f, 7.3f, 8.0f,  3.1f );
        mat4 amat4 = bmat4;
        CHECK_EQUAL( amat4, bmat4 );
        amat4(1,1) = 6.523f;
        CHECK( bmat4(0,0) != amat4(1,1) );
        CHECK( bmat4(0,1) != amat4(1,1) );
        CHECK( bmat4(0,2) != amat4(1,1) );
        CHECK( bmat4(0,3) != amat4(1,1) );
        CHECK( bmat4(1,0) != amat4(1,1) );
        CHECK( bmat4(1,1) != amat4(1,1) );
        CHECK( bmat4(1,2) != amat4(1,1) );
        CHECK( bmat4(1,3) != amat4(1,1) );
        CHECK( bmat4(2,0) != amat4(1,1) );
        CHECK( bmat4(2,1) != amat4(1,1) );
        CHECK( bmat4(2,2) != amat4(1,1) );
        CHECK( bmat4(2,3) != amat4(1,1) ); // no side effects
    }


    TEST( Matrix4Identity )
    {
        using namespace gfx;
        mat4 amat4 = mat4::identity();
        mat4 bmat4( 1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f );
        CHECK_EQUAL( amat4, bmat4 );
    }

    TEST( Matrix4RowVectors )
    {
        using namespace gfx;
        vec4 avec4(  5.0f, -1.0f,  6.7f,   1.0f );
        vec4 bvec4( 97.0f,  2.0f,  2.3f, -12.1f );
        vec4 cvec4( -5.6f, 12.0f,  4.5f,   0.045f );
        vec4 dvec4(  7.9f,  3.1f, -2.5f,  -1.037f );
        mat4 amat4 = mat4::row_vectors( avec4, bvec4, cvec4, dvec4 );
        mat4 bmat4(  5.0f, -1.0f,  6.7f,   1.0f,
                    97.0f,  2.0f,  2.3f, -12.1f,
                    -5.6f, 12.0f,  4.5f,   0.045f,
                    7.9f,  3.1f, -2.5f,  -1.037f );
        CHECK_EQUAL( amat4, bmat4 );
    }

    TEST( Matrix4ColumnVectors )
    {
        using namespace gfx;
        vec4 avec4(  5.0f, -1.0f,  6.7f,   1.0f );
        vec4 bvec4( 97.0f,  2.0f,  2.3f, -12.1f );
        vec4 cvec4( -5.6f, 12.0f,  4.5f,   0.045f );
        vec4 dvec4(  7.9f,  3.1f, -2.5f,  -1.037f );
        mat4 amat4 = mat4::column_vectors( avec4, bvec4, cvec4, dvec4 );
        mat4 bmat4(  5.0f,  97.0f, -5.6f,    7.9f,
                    -1.0f,   2.0f, 12.0f,    3.1f,
                    6.7f,   2.3f,  4.5f,   -2.5f,
                    1.0f, -12.1f,  0.045f, -1.037f );
        CHECK_EQUAL( amat4, bmat4 );
    }
    
    TEST( Matrix4Square )
    {
        using namespace gfx;
        vec4 avec4( 3.0f, 4.0f, -2.0f, 2.0f );
        mat4 amat4 = mat4::square( avec4 );
        mat4 bmat4(  9.0f, 12.0f, -6.0f,  6.0f,
                     12.0f, 16.0f, -8.0f,  8.0f,
                     -6.0f, -8.0f,  4.0f, -4.0f,
                      6.0f,  8.0f, -4.0f,  4.0f );
        CHECK_EQUAL( bmat4, amat4 );
    }

    TEST( Matrix4Scale )
    {
        using namespace gfx;
        mat4 amat4 = mat4::scale( 5.0f, -1.0f, 4.0f );
        vec3 avec3( 5.0f, -1.0f, 4.0f );
        mat4 bmat4 = mat4::scale( avec3 );
        mat4 cmat4( 5.0f,  0.0f, 0.0f, 0.0f,
                     0.0f, -1.0f, 0.0f, 0.0f,
                     0.0f,  0.0f, 4.0f, 0.0f,
                     0.0f,  0.0f, 0.0f, 1.0f );
        CHECK_EQUAL( amat4, bmat4 );
        CHECK_EQUAL( bmat4, cmat4 );
        CHECK_EQUAL( amat4, cmat4 );  
    }
    
    TEST( Matrix4Translate )
    {
        using namespace gfx;
        mat4 amat4 = mat4::translate( 5.0f, -1.0f, 4.0f );
        vec3 avec3( 5.0f, -1.0f, 4.0f );
        mat4 bmat4 = mat4::translate( avec3 );
        mat4 cmat4( 1.0f, 0.0f, 0.0f,  5.0f,
                     0.0f, 1.0f, 0.0f, -1.0f,
                     0.0f, 0.0f, 1.0f,  4.0f,
                     0.0f, 0.0f, 0.0f,  1.0f );
        CHECK_EQUAL( cmat4, amat4 );
        CHECK_EQUAL( cmat4, bmat4 );
        CHECK_EQUAL( amat4, bmat4 );
    }
    
    TEST( Matrix4CrossProduct )
    {
        using namespace gfx;
        vec3 avec3( 3.0f, 4.0f, -2.0f );
        mat4 amat4 = mat4::cross_product( avec3 );
        mat4 bmat4(  0.0f, 2.0f,  4.0f, 0.0f,
                     -2.0f, 0.0f, -3.0f, 0.0f,
                     -4.0f, 3.0f,  0.0f, 0.0f,
                      0.0f, 0.0f,  0.0f, 1.0f );
        CHECK_EQUAL( bmat4, amat4 );
    }
    
    TEST( Matrix4Perspective )
    {
        using namespace gfx;
        double fovY (1.0);
        double aspect (0.75);
        double near (0.01);
        double far (100);
        mat4 amat4 = mat4::perspective( fovY, aspect,
                                          near, far );
        mat4 bmat4( 2.4406502956f, 0.0f,           0.0f,        0.0f,
                     0.0f,          1.8304877217f,  0.0f,        0.0f,
                     0.0f,          0.0f,          -1.0002002f, -0.0200020002f,
                     0.0f,          0.0f,          -1.0f,        0.0f           );
        CHECK_EQUAL( bmat4, amat4 );
        
    }
    
    TEST( Matrix4Rotation )
    {
        using namespace gfx;
        vec3 axis( 1.0f, 0.0f, 0.0f );
        d_angle angx = d_angle::in_degs( 90.0f );
        mat4 amat4 = mat4::rotation( axis, angx );
        mat4 bmat4 = mat4::rotation( angx,
                                       d_angle::in_degs( 0.0 ),
                                       d_angle::in_degs( 0.0 ) );
        mat4 cmat4 = mat4::rotation( qutn::rotation(axis, angx ) );
        mat4 dmat4( 1.0f, 0.0f,  0.0f, 0.0f,
                     0.0f, 0.0f, -1.0f, 0.0f,
                     0.0f, 1.0f,  0.0f, 0.0f,
                     0.0f, 0.0f,  0.0f, 1.0f );
        CHECK_EQUAL( dmat4, amat4 );
        CHECK_EQUAL( dmat4, bmat4 );
        CHECK_EQUAL( dmat4, cmat4 );
    }

    TEST( Matrix4Lookup )
    {
        using namespace gfx;
        mat4 amat4;
        amat4(0,0) = 4.7f;
        amat4(0,3) = -5.3f;
        mat4 bmat4( 4.7f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 0.0f,
                    -5.3f, 0.0f, 0.0f, 0.0f );
        CHECK_EQUAL( amat4, bmat4 );
        CHECK_EQUAL( amat4(0,0), 4.7f );
        CHECK_EQUAL( amat4(0,3), -5.3f );
    }
    
    TEST( Matrix4ColumnLookup )
    {
        using namespace gfx;
        mat4 amat4( 4.7f, 0.0f, 0.0f, 0.0f,
                    -5.3f, 0.0f, 0.0f, 0.0f,
                     1.5f, 0.0f, 0.0f, 0.0f,
                     2.5f, 0.0f, 0.0f, 0.0f );
        vec4 avec4( 4.7f, -5.3f, 1.5f, 2.5f );
        
        vec4 bvec4 = amat4[0];
        CHECK_EQUAL( avec4, bvec4 );
        
        avec4(w) = 10.2f;
        amat4[0] = avec4;
        
        CHECK_EQUAL( avec4[0], amat4(0,0) );
        CHECK_EQUAL( avec4[1], amat4(0,1) );
        CHECK_EQUAL( avec4[2], amat4(0,2) );
        CHECK_EQUAL( avec4[3], amat4(0,3) );
        CHECK_EQUAL( avec4, amat4[0] );
        avec4(x) = 11.2f;
        CHECK( avec4(x) != amat4(0,0) );
    }

    TEST( Matrix4Addition )
    {
        using namespace gfx;
        mat4 amat4( 0.0f, 0.0f,  4.7f, 56.7f,
                    0.0f, 0.0f, -0.2f,  6.4f,
                    0.0f, 0.0f, 10.4f,  5.7f,
                    0.0f, 0.0f, -5.3f, 12.1f );
        mat4 bmat4(   4.7f,  2.4f, 0.0f, 0.0f,
                    13.1f,  1.6f, 0.0f, 0.0f,
                    3.9f, -2.6f, 0.0f, 0.0f,
                    -5.3f, -8.9f, 0.0f, 0.0f );
        CHECK( amat4 != bmat4 );
        mat4 cmat4 = amat4 + bmat4;
        mat4 dmat4(  4.7f,  2.4f,  4.7f, 56.7f,
                    13.1f,  1.6f, -0.2f,  6.4f,
                    3.9f, -2.6f, 10.4f,  5.7f,
                    -5.3f, -8.9f, -5.3f, 12.1f );
        CHECK_EQUAL( cmat4, dmat4 );
        cmat4(1,1) = 2.487f;
        CHECK( amat4(0,0) != cmat4(1,1) );
        CHECK( amat4(0,1) != cmat4(1,1) );
        CHECK( amat4(0,2) != cmat4(1,1) );
        CHECK( amat4(0,3) != cmat4(1,1) );
        CHECK( amat4(1,0) != cmat4(1,1) );
        CHECK( amat4(1,1) != cmat4(1,1) );
        CHECK( amat4(1,2) != cmat4(1,1) );
        CHECK( amat4(1,3) != cmat4(1,1) );
        CHECK( amat4(2,0) != cmat4(1,1) );
        CHECK( amat4(2,1) != cmat4(1,1) );
        CHECK( amat4(2,2) != cmat4(1,1) );
        CHECK( amat4(2,3) != cmat4(1,1) );
        CHECK( amat4(3,0) != cmat4(1,1) );
        CHECK( amat4(3,1) != cmat4(1,1) );
        CHECK( amat4(3,2) != cmat4(1,1) );
        CHECK( amat4(3,3) != cmat4(1,1) );
        CHECK( bmat4(0,0) != cmat4(1,1) );
        CHECK( bmat4(0,1) != cmat4(1,1) );
        CHECK( bmat4(0,2) != cmat4(1,1) );
        CHECK( bmat4(0,3) != cmat4(1,1) );
        CHECK( bmat4(1,0) != cmat4(1,1) );
        CHECK( bmat4(1,1) != cmat4(1,1) );
        CHECK( bmat4(1,2) != cmat4(1,1) );
        CHECK( bmat4(1,3) != cmat4(1,1) );
        CHECK( bmat4(2,0) != cmat4(1,1) );
        CHECK( bmat4(2,1) != cmat4(1,1) );
        CHECK( bmat4(2,2) != cmat4(1,1) );
        CHECK( bmat4(2,3) != cmat4(1,1) );
        CHECK( bmat4(3,0) != cmat4(1,1) );
        CHECK( bmat4(3,1) != cmat4(1,1) );
        CHECK( bmat4(3,2) != cmat4(1,1) );
        CHECK( bmat4(3,3) != cmat4(1,1) ); // no side effects
    }

    TEST( Matrix4Negation )
    {
        using namespace gfx;
        mat4 amat4( 0.0f,  4.7f, 56.7f, 16.2f,
                    0.0f, -0.2f,  6.4f, 67.1f,
                    0.0f,  5.3f, 10.3f, -3.1f,
                    0.0f, -5.3f, 12.1f,  0.0f );
        mat4 bmat4( 0.0f, -4.7f, -56.7f, -16.2f,
                    0.0f,  0.2f,  -6.4f, -67.1f,
                    0.0f, -5.3f, -10.3f,  3.1f,
                    0.0f,  5.3f, -12.1f,  0.0f );
        mat4 cmat4 = -amat4;
        CHECK_EQUAL( cmat4, bmat4 );
        cmat4(1,1) = 2.4f;
        CHECK( amat4(0,0) != cmat4(1,1) );
        CHECK( amat4(0,1) != cmat4(1,1) );
        CHECK( amat4(0,2) != cmat4(1,1) );
        CHECK( amat4(0,3) != cmat4(1,1) );
        CHECK( amat4(1,0) != cmat4(1,1) );
        CHECK( amat4(1,1) != cmat4(1,1) );
        CHECK( amat4(1,2) != cmat4(1,1) );
        CHECK( amat4(1,3) != cmat4(1,1) );
        CHECK( amat4(2,0) != cmat4(1,1) );
        CHECK( amat4(2,1) != cmat4(1,1) );
        CHECK( amat4(2,2) != cmat4(1,1) ); 
        CHECK( amat4(2,3) != cmat4(1,1) ); 
        CHECK( amat4(3,0) != cmat4(1,1) );
        CHECK( amat4(3,1) != cmat4(1,1) );
        CHECK( amat4(3,2) != cmat4(1,1) ); 
        CHECK( amat4(3,3) != cmat4(1,1) ); 
        CHECK( bmat4(0,0) != cmat4(1,1) );
        CHECK( bmat4(0,1) != cmat4(1,1) );
        CHECK( bmat4(0,2) != cmat4(1,1) );
        CHECK( bmat4(0,3) != cmat4(1,1) );
        CHECK( bmat4(1,0) != cmat4(1,1) );
        CHECK( bmat4(1,1) != cmat4(1,1) );
        CHECK( bmat4(1,2) != cmat4(1,1) );
        CHECK( bmat4(1,3) != cmat4(1,1) );
        CHECK( bmat4(2,0) != cmat4(1,1) );
        CHECK( bmat4(2,1) != cmat4(1,1) );
        CHECK( bmat4(2,2) != cmat4(1,1) );
        CHECK( bmat4(2,3) != cmat4(1,1) );
        CHECK( bmat4(3,0) != cmat4(1,1) );
        CHECK( bmat4(3,1) != cmat4(1,1) );
        CHECK( bmat4(3,2) != cmat4(1,1) );
        CHECK( bmat4(3,3) != cmat4(1,1) ); // no side effects
    }

    TEST( Matrix4Subtraction )
    {
        using namespace gfx;
        mat4 amat4( 0.0f, 0.0f,  4.7f, 56.7f,
                    0.0f, 0.0f, -0.2f,  6.4f,
                    0.0f, 0.0f, 10.4f,  5.7f,
                    0.0f, 0.0f, -5.3f, 12.1f );
        mat4 bmat4(   4.7f,  2.4f, 0.0f, 0.0f,
                    13.1f,  1.6f, 0.0f, 0.0f,
                    3.9f, -2.6f, 0.0f, 0.0f,
                    -5.3f, -8.9f, 0.0f, 0.0f );
        CHECK( amat4 != bmat4 );
        mat4 cmat4 = amat4 - bmat4;
        mat4 dmat4(  -4.7f, -2.4f,  4.7f, 56.7f,
                    -13.1f, -1.6f, -0.2f,  6.4f,
                    -3.9f,  2.6f, 10.4f,  5.7f,
                    5.3f,  8.9f, -5.3f, 12.1f );
        CHECK_EQUAL( cmat4, dmat4 );
        cmat4(1,1) = 2.487f;
        CHECK( amat4(0,0) != cmat4(1,1) );
        CHECK( amat4(0,1) != cmat4(1,1) );
        CHECK( amat4(0,2) != cmat4(1,1) );
        CHECK( amat4(0,3) != cmat4(1,1) );
        CHECK( amat4(1,0) != cmat4(1,1) );
        CHECK( amat4(1,1) != cmat4(1,1) );
        CHECK( amat4(1,2) != cmat4(1,1) );
        CHECK( amat4(1,3) != cmat4(1,1) );
        CHECK( amat4(2,0) != cmat4(1,1) );
        CHECK( amat4(2,1) != cmat4(1,1) );
        CHECK( amat4(2,2) != cmat4(1,1) );
        CHECK( amat4(2,3) != cmat4(1,1) );
        CHECK( amat4(3,0) != cmat4(1,1) );
        CHECK( amat4(3,1) != cmat4(1,1) );
        CHECK( amat4(3,2) != cmat4(1,1) );
        CHECK( amat4(3,3) != cmat4(1,1) );
        CHECK( bmat4(0,0) != cmat4(1,1) );
        CHECK( bmat4(0,1) != cmat4(1,1) );
        CHECK( bmat4(0,2) != cmat4(1,1) );
        CHECK( bmat4(0,3) != cmat4(1,1) );
        CHECK( bmat4(1,0) != cmat4(1,1) );
        CHECK( bmat4(1,1) != cmat4(1,1) );
        CHECK( bmat4(1,2) != cmat4(1,1) );
        CHECK( bmat4(1,3) != cmat4(1,1) );
        CHECK( bmat4(2,0) != cmat4(1,1) );
        CHECK( bmat4(2,1) != cmat4(1,1) );
        CHECK( bmat4(2,2) != cmat4(1,1) );
        CHECK( bmat4(2,3) != cmat4(1,1) );
        CHECK( bmat4(3,0) != cmat4(1,1) );
        CHECK( bmat4(3,1) != cmat4(1,1) );
        CHECK( bmat4(3,2) != cmat4(1,1) );
        CHECK( bmat4(3,3) != cmat4(1,1) ); // no side effects
    }

    TEST( Matrix4Multiplication )
    {
        using namespace gfx;
        mat4 amat4 = mat4::identity();
        mat4 bmat4( -2.0f, 1.0f,  3.0f,  4.0f,
                    4.0f, 0.0f,  0.0f, -7.0f,
                    5.0f, 9.0f, -4.0f, 12.0f,
                    0.0f, 5.5f,  9.0f, 15.0f );
        CHECK( amat4 != bmat4 );
        mat4 cmat4 = amat4 * bmat4;
        CHECK_EQUAL( cmat4, bmat4 );
        cmat4(1,1) = 2.487f;
        CHECK( amat4(0,0) != cmat4(1,1) );
        CHECK( amat4(0,1) != cmat4(1,1) );
        CHECK( amat4(0,2) != cmat4(1,1) );
        CHECK( amat4(0,3) != cmat4(1,1) );
        CHECK( amat4(1,0) != cmat4(1,1) );
        CHECK( amat4(1,1) != cmat4(1,1) );
        CHECK( amat4(1,2) != cmat4(1,1) );
        CHECK( amat4(1,3) != cmat4(1,1) );
        CHECK( amat4(2,0) != cmat4(1,1) );
        CHECK( amat4(2,1) != cmat4(1,1) );
        CHECK( amat4(2,2) != cmat4(1,1) );
        CHECK( amat4(2,3) != cmat4(1,1) );
        CHECK( amat4(3,0) != cmat4(1,1) );
        CHECK( amat4(3,1) != cmat4(1,1) );
        CHECK( amat4(3,2) != cmat4(1,1) );
        CHECK( amat4(3,3) != cmat4(1,1) );
        CHECK( bmat4(0,0) != cmat4(1,1) );
        CHECK( bmat4(0,1) != cmat4(1,1) );
        CHECK( bmat4(0,2) != cmat4(1,1) );
        CHECK( bmat4(0,3) != cmat4(1,1) );
        CHECK( bmat4(1,0) != cmat4(1,1) );
        CHECK( bmat4(1,1) != cmat4(1,1) );
        CHECK( bmat4(1,2) != cmat4(1,1) );
        CHECK( bmat4(1,3) != cmat4(1,1) );
        CHECK( bmat4(2,0) != cmat4(1,1) );
        CHECK( bmat4(2,1) != cmat4(1,1) );
        CHECK( bmat4(2,2) != cmat4(1,1) );
        CHECK( bmat4(2,3) != cmat4(1,1) );
        CHECK( bmat4(3,0) != cmat4(1,1) );
        CHECK( bmat4(3,1) != cmat4(1,1) );
        CHECK( bmat4(3,2) != cmat4(1,1) );
        CHECK( bmat4(3,3) != cmat4(1,1) );  // no side effects
        
        mat4 dmat4( -2.0f, 1.0f,  3.0f,  4.0f,
                    4.0f, 0.0f,  0.0f, -7.0f,
                    5.0f, 9.0f, -4.0f, 12.0f,
                    0.0f, 5.5f,  9.0f, 15.0f );
        mat4 emat4(   3.0f,   0.2f, -0.1f,  5.0f,
                    -1.0f, 100.0f, -0.5f, -4.5f,
                    10.0f,  -2.0f,  5.0f, 10.0f,
                    45.0f, 100.0f, -5.0f,  0.0f );
        cmat4 = dmat4 * emat4;
        mat4 mat4(  203.0f,  493.6f,  -5.3f,  15.5f,
                    -303.0f, -699.2f,  34.6f,  20.0f,
                    506.0f, 2109.0f, -85.0f, -55.5f,
                    759.5f, 2032.0f, -32.75f, 65.25f );
        CHECK_EQUAL( mat4, cmat4 );
        cmat4(1,1) = 2.487f;
        CHECK( amat4(0,0) != cmat4(1,1) );
        CHECK( amat4(0,1) != cmat4(1,1) );
        CHECK( amat4(0,2) != cmat4(1,1) );
        CHECK( amat4(0,3) != cmat4(1,1) );
        CHECK( amat4(1,0) != cmat4(1,1) );
        CHECK( amat4(1,1) != cmat4(1,1) );
        CHECK( amat4(1,2) != cmat4(1,1) );
        CHECK( amat4(1,3) != cmat4(1,1) );
        CHECK( amat4(2,0) != cmat4(1,1) );
        CHECK( amat4(2,1) != cmat4(1,1) );
        CHECK( amat4(2,2) != cmat4(1,1) );
        CHECK( amat4(2,3) != cmat4(1,1) );
        CHECK( amat4(3,0) != cmat4(1,1) );
        CHECK( amat4(3,1) != cmat4(1,1) );
        CHECK( amat4(3,2) != cmat4(1,1) );
        CHECK( amat4(3,3) != cmat4(1,1) );
        CHECK( bmat4(0,0) != cmat4(1,1) );
        CHECK( bmat4(0,1) != cmat4(1,1) );
        CHECK( bmat4(0,2) != cmat4(1,1) );
        CHECK( bmat4(0,3) != cmat4(1,1) );
        CHECK( bmat4(1,0) != cmat4(1,1) );
        CHECK( bmat4(1,1) != cmat4(1,1) );
        CHECK( bmat4(1,2) != cmat4(1,1) );
        CHECK( bmat4(1,3) != cmat4(1,1) );
        CHECK( bmat4(2,0) != cmat4(1,1) );
        CHECK( bmat4(2,1) != cmat4(1,1) );
        CHECK( bmat4(2,2) != cmat4(1,1) );
        CHECK( bmat4(2,3) != cmat4(1,1) );
        CHECK( bmat4(3,0) != cmat4(1,1) );
        CHECK( bmat4(3,1) != cmat4(1,1) );
        CHECK( bmat4(3,2) != cmat4(1,1) );
        CHECK( bmat4(3,3) != cmat4(1,1) ); // no side effects
    }
    
    TEST( Matrix4Mult2x4 )
    {
        using namespace gfx;
        mat4 amat4 = mat4::identity();
        mat2x4 amat2x4( 14.5f,   100.5f, 
                        -7.01f, -234.52f,
                         5.0f,    -2.0f,
                         7.0f,   -11.0f );
        mat2x4 bmat2x4 = amat4 * amat2x4;
        CHECK_EQUAL( amat2x4, bmat2x4 );
    }
    
    TEST( Matrix4Mult3x4 )
    {
        using namespace gfx;
        mat4 amat4 = mat4::identity();
        mat3x4 amat3x4( 14.5f,   100.5f,   2.0f,
                        -7.01f, -234.52f, 11.0f,
                         5.0f,    -2.0f,  -5.0f,
                       654.0f,   -67.0f, 354.3f );
        mat3x4 bmat3x4 = amat4 * amat3x4;
        CHECK_EQUAL( amat3x4, bmat3x4 );
    }
    
    TEST( Matrix4VectorMultiplication )
    {
        using namespace gfx;
        mat4 amat4 = mat4::identity();
        mat4 bmat4( 2.0f, 100.0f,  1.0f, 3.0f,
                     4.0f,  15.0f, -1.0f, -50.0f,
                     3.0f,   8.0f,  2.0f, -25.0f,
                    -7.0f, -10.0f,  5.0f, -1.0f );
        vec4 avec4( 2.0f, 1.0f, -1.0f, -2.0f );
        vec4 bvec4 = amat4 * avec4;
        CHECK_EQUAL( avec4, bvec4 );
        bvec4 = avec4 * amat4;
        CHECK_EQUAL( avec4, bvec4 );
        
        vec4 cvec4( 97.0f, 124.0f, 62.0f, -27.0f);
        bvec4 = bmat4 * avec4;
        CHECK_EQUAL( cvec4, bvec4 );

        vec4 dvec4( 19.0f, 227.0f, -11.0f, -17.0f );
        bvec4 = avec4 * bmat4;
        CHECK_EQUAL( dvec4, bvec4 );
    }

    TEST( Matrix4ScalarMultiplication )
    {
        using namespace gfx;
        mat4 amat4(  2.0f,  4.0f, 20.0f, 16.0f,
                    -8.0f, -6.0f, 10.0f, -4.0f,
                    -2.0f,  4.0f, 14.0f, 24.0f,
                    12.0f,  4.0f, -6.0f, 18.0f );
        mat4 bmat4(   4.0f,   8.0f,  40.0f, 32.0f,
                    -16.0f, -12.0f,  20.0f, -8.0f,
                    -4.0f,   8.0f,  28.0f, 48.0f,
                    24.0f,   8.0f, -12.0f, 36.0f );
        mat4 cmat4 = amat4 * 2.0f;
        CHECK_EQUAL( cmat4, bmat4 );
        cmat4(1,1) = 2.487f;
        CHECK( amat4(0,0) != cmat4(1,1) );
        CHECK( amat4(0,1) != cmat4(1,1) );
        CHECK( amat4(0,2) != cmat4(1,1) );
        CHECK( amat4(0,3) != cmat4(1,1) );
        CHECK( amat4(1,0) != cmat4(1,1) );
        CHECK( amat4(1,1) != cmat4(1,1) );
        CHECK( amat4(1,2) != cmat4(1,1) );
        CHECK( amat4(1,3) != cmat4(1,1) );
        CHECK( amat4(2,0) != cmat4(1,1) );
        CHECK( amat4(2,1) != cmat4(1,1) );
        CHECK( amat4(2,2) != cmat4(1,1) );
        CHECK( amat4(2,3) != cmat4(1,1) );
        CHECK( amat4(3,0) != cmat4(1,1) );
        CHECK( amat4(3,1) != cmat4(1,1) );
        CHECK( amat4(3,2) != cmat4(1,1) );
        CHECK( amat4(3,3) != cmat4(1,1) );
        CHECK( bmat4(0,0) != cmat4(1,1) );
        CHECK( bmat4(0,1) != cmat4(1,1) );
        CHECK( bmat4(0,2) != cmat4(1,1) );
        CHECK( bmat4(0,3) != cmat4(1,1) );
        CHECK( bmat4(1,0) != cmat4(1,1) );
        CHECK( bmat4(1,1) != cmat4(1,1) );
        CHECK( bmat4(1,2) != cmat4(1,1) );
        CHECK( bmat4(1,3) != cmat4(1,1) );
        CHECK( bmat4(2,0) != cmat4(1,1) );
        CHECK( bmat4(2,1) != cmat4(1,1) );
        CHECK( bmat4(2,2) != cmat4(1,1) );
        CHECK( bmat4(2,3) != cmat4(1,1) );
        CHECK( bmat4(3,0) != cmat4(1,1) );
        CHECK( bmat4(3,1) != cmat4(1,1) );
        CHECK( bmat4(3,2) != cmat4(1,1) );
        CHECK( bmat4(3,3) != cmat4(1,1) ); // no side effects
        
        cmat4 = 2.0f * amat4;
        CHECK_EQUAL( cmat4, bmat4 );
        cmat4(1,1) = 2.487f;
        CHECK( amat4(0,0) != cmat4(1,1) );
        CHECK( amat4(0,1) != cmat4(1,1) );
        CHECK( amat4(0,2) != cmat4(1,1) );
        CHECK( amat4(0,3) != cmat4(1,1) );
        CHECK( amat4(1,0) != cmat4(1,1) );
        CHECK( amat4(1,1) != cmat4(1,1) );
        CHECK( amat4(1,2) != cmat4(1,1) );
        CHECK( amat4(1,3) != cmat4(1,1) );
        CHECK( amat4(2,0) != cmat4(1,1) );
        CHECK( amat4(2,1) != cmat4(1,1) );
        CHECK( amat4(2,2) != cmat4(1,1) );
        CHECK( amat4(2,3) != cmat4(1,1) );
        CHECK( amat4(3,0) != cmat4(1,1) );
        CHECK( amat4(3,1) != cmat4(1,1) );
        CHECK( amat4(3,2) != cmat4(1,1) );
        CHECK( amat4(3,3) != cmat4(1,1) );
        CHECK( bmat4(0,0) != cmat4(1,1) );
        CHECK( bmat4(0,1) != cmat4(1,1) );
        CHECK( bmat4(0,2) != cmat4(1,1) );
        CHECK( bmat4(0,3) != cmat4(1,1) );
        CHECK( bmat4(1,0) != cmat4(1,1) );
        CHECK( bmat4(1,1) != cmat4(1,1) );
        CHECK( bmat4(1,2) != cmat4(1,1) );
        CHECK( bmat4(1,3) != cmat4(1,1) );
        CHECK( bmat4(2,0) != cmat4(1,1) );
        CHECK( bmat4(2,1) != cmat4(1,1) );
        CHECK( bmat4(2,2) != cmat4(1,1) );
        CHECK( bmat4(2,3) != cmat4(1,1) );
        CHECK( bmat4(3,0) != cmat4(1,1) );
        CHECK( bmat4(3,1) != cmat4(1,1) );
        CHECK( bmat4(3,2) != cmat4(1,1) );
        CHECK( bmat4(3,3) != cmat4(1,1) ); // no side effects
    }

    TEST( Matrix4ScalarDivision )
    {
        using namespace gfx;
        mat4 amat4(   4.0f,   8.0f,  40.0f, 32.0f,
                    -16.0f, -12.0f,  20.0f, -8.0f,
                    -4.0f,   8.0f,  28.0f, 48.0f,
                    24.0f,   8.0f, -12.0f, 36.0f );
        mat4 bmat4(  2.0f,  4.0f, 20.0f, 16.0f,
                    -8.0f, -6.0f, 10.0f, -4.0f,
                    -2.0f,  4.0f, 14.0f, 24.0f,
                    12.0f,  4.0f, -6.0f, 18.0f );
        mat4 cmat4 = amat4 / 2.0f;
        CHECK_EQUAL( cmat4, bmat4 );
        cmat4(1,1) = 2.487f;
        CHECK( amat4(0,0) != cmat4(1,1) );
        CHECK( amat4(0,1) != cmat4(1,1) );
        CHECK( amat4(0,2) != cmat4(1,1) );
        CHECK( amat4(0,3) != cmat4(1,1) );
        CHECK( amat4(1,0) != cmat4(1,1) );
        CHECK( amat4(1,1) != cmat4(1,1) );
        CHECK( amat4(1,2) != cmat4(1,1) );
        CHECK( amat4(1,3) != cmat4(1,1) );
        CHECK( amat4(2,0) != cmat4(1,1) );
        CHECK( amat4(2,1) != cmat4(1,1) );
        CHECK( amat4(2,2) != cmat4(1,1) );
        CHECK( amat4(2,3) != cmat4(1,1) );
        CHECK( amat4(3,0) != cmat4(1,1) );
        CHECK( amat4(3,1) != cmat4(1,1) );
        CHECK( amat4(3,2) != cmat4(1,1) );
        CHECK( amat4(3,3) != cmat4(1,1) );
        CHECK( bmat4(0,0) != cmat4(1,1) );
        CHECK( bmat4(0,1) != cmat4(1,1) );
        CHECK( bmat4(0,2) != cmat4(1,1) );
        CHECK( bmat4(0,3) != cmat4(1,1) );
        CHECK( bmat4(1,0) != cmat4(1,1) );
        CHECK( bmat4(1,1) != cmat4(1,1) );
        CHECK( bmat4(1,2) != cmat4(1,1) );
        CHECK( bmat4(1,3) != cmat4(1,1) );
        CHECK( bmat4(2,0) != cmat4(1,1) );
        CHECK( bmat4(2,1) != cmat4(1,1) );
        CHECK( bmat4(2,2) != cmat4(1,1) );
        CHECK( bmat4(2,3) != cmat4(1,1) );
        CHECK( bmat4(3,0) != cmat4(1,1) );
        CHECK( bmat4(3,1) != cmat4(1,1) );
        CHECK( bmat4(3,2) != cmat4(1,1) );
        CHECK( bmat4(3,3) != cmat4(1,1) ); // no side effects
    }

    TEST( Matrix4InPlaceFill )
    {
        using namespace gfx;
        mat4 amat4;
        mat4 bmat4( 2.5f, 2.5f, 2.5f, 2.5f,
                    2.5f, 2.5f, 2.5f, 2.5f,
                    2.5f, 2.5f, 2.5f, 2.5f,
                    2.5f, 2.5f, 2.5f, 2.5f );
        amat4.fill( 2.5f );
        CHECK_EQUAL( amat4, bmat4 );
        // make sure a reference is returned
        amat4.fill(3.0f)(0,0) = 2.1f;
        mat4 cmat4( 2.1f, 3.0f, 3.0f, 3.0f,
                    3.0f, 3.0f, 3.0f, 3.0f,
                    3.0f, 3.0f, 3.0f, 3.0f,
                    3.0f, 3.0f, 3.0f, 3.0f );
        CHECK_EQUAL( amat4, cmat4 );
    }

    TEST( Matrix4InPlaceTranspose )
    {
        using namespace gfx;
        mat4 amat4( 2.0f, 2.0f, 2.0f, 2.0f,
                    1.0f, 1.0f, 2.0f, 2.0f,
                    1.0f, 1.0f, 2.0f, 2.0f,
                    1.0f, 1.0f, 1.0f, 1.0f );
        
        mat4 bmat4(  2.0f, 1.0f, 1.0f, 1.0f,
                    2.0f, 1.0f, 1.0f, 1.0f,
                    2.0f, 2.0f, 2.0f, 1.0f,
                    2.0f, 2.0f, 2.0f, 1.0f );
        amat4.transpose();
        CHECK_EQUAL( amat4, bmat4 );
        // make sure a reference is returned
        amat4.transpose()(0,0) = 2.1f;
        mat4 cmat4( 2.1f, 2.0f, 2.0f, 2.0f,
                    1.0f, 1.0f, 2.0f, 2.0f,
                    1.0f, 1.0f, 2.0f, 2.0f,
                    1.0f, 1.0f, 1.0f, 1.0f );
        CHECK_EQUAL( amat4, cmat4 );
    }

    TEST( Matrix4RowLookup )
    {
        using namespace gfx;
        mat4 amat4;
        vec4 avec4( -10.0f, 10.0f, -10.0f, 10.0f );
        mat4 bmat4(   0.0f,  0.0f,   0.0f,  0.0f,
                    -10.0f, 10.0f, -10.0f, 10.0f,
                    0.0f,  0.0f,   0.0f,  0.0f,
                    0.0f,  0.0f,   0.0f,  0.0f );
        amat4.row( 1, avec4 );
        CHECK_EQUAL( amat4, bmat4 );
        // make sure a reference is returned
        mat4 cmat4( -20.0f, 20.0f, -20.0f, 20.0f,
                    -10.0f,  8.1f, -10.0f, 10.0f,
                    0.0f,  0.0f,   0.0f,  0.0f,
                    0.0f,  0.0f,   0.0f,  0.0f );
        vec4 bvec4( -20.0f, 20.0f, -20.0f, 20.0f );
        amat4.row( 0, bvec4 )( 1, 1 ) = 8.1f;
        CHECK_EQUAL( amat4, cmat4 );
        vec4 cvec4 = amat4.row(0);
        CHECK_EQUAL( cvec4, bvec4 );
    }

    TEST( Matrix4ColumnAccess )
    {
        using namespace gfx;
        mat4 amat4;
        vec4 avec4( -10.0f,  10.0f, -10.0f, 10.0f );
        mat4 bmat4( 0.0f, -10.0f, 0.0f, 0.0f,
                    0.0f,  10.0f, 0.0f, 0.0f,
                    0.0f, -10.0f, 0.0f, 0.0f,
                    0.0f,  10.0f, 0.0f, 0.0f );
        amat4.column( 1, avec4 );
        CHECK_EQUAL( amat4, bmat4 );
        // make sure a reference is returned
        mat4 cmat4( -20.0f, -10.0f, 0.0f, 0.0f,
                    20.0f,  8.1f, 0.0f, 0.0f,
                    -20.0f, -10.0f, 0.0f, 0.0f,
                    20.0f,  10.0f, 0.0f, 0.0f );
        vec4 bvec4( -20.0f, 20.0f, -20.0f, 20.0f );
        amat4.column( 0, bvec4 )( 1, 1 ) = 8.1f;
        CHECK_EQUAL( amat4, cmat4 );
        vec4 cvec4 = amat4.column(0);
        CHECK_EQUAL( cvec4, bvec4 );
    }

    TEST( Matrix4MultiRowAssignment )
    {
        using namespace gfx;
        mat4 amat4;
        mat4 bmat4(   5.0f, -10.0f, -5.0f,  15.0f,
                    -14.0f, -12.0f,  6.0f,   8.0f,
                    -5.0f,  10.0f,  5.0f, -15.0f,
                    14.0f,  12.0f, -6.0f,  -8.0f );
        vec4 avec4(   5.0f, -10.0f, -5.0f,  15.0f );
        vec4 bvec4( -14.0f, -12.0f,  6.0f,   8.0f );
        vec4 cvec4(  -5.0f,  10.0f,  5.0f, -15.0f );
        vec4 dvec4(  14.0f,  12.0f, -6.0f,  -8.0f );
        amat4.rows( avec4, bvec4, cvec4, dvec4 );
        CHECK_EQUAL( amat4, bmat4 );
    }

    TEST( Matrix4MultiColumnAssignment )
    {
        using namespace gfx;
        mat4 amat4;
        mat4 bmat4(   5.0f, -10.0f, -5.0f,  15.0f,
                    -14.0f, -12.0f,  6.0f,   8.0f,
                    -5.0f,  10.0f,  5.0f, -15.0f,
                    14.0f,  12.0f, -6.0f,  -8.0f );
        vec4 avec4(   5.0f, -14.0f,  -5.0f, 14.0f );
        vec4 bvec4( -10.0f, -12.0f,  10.0f, 12.0f );
        vec4 cvec4(  -5.0f,   6.0f,   5.0f, -6.0f );
        vec4 dvec4(  15.0f,   8.0f, -15.0f, -8.0f );
        amat4.columns( avec4, bvec4, cvec4, dvec4 );
        CHECK_EQUAL( amat4, bmat4 );
    }

    TEST( Matrix4Mapping )
    {
        using namespace gfx;
        union mock_data {
            float           values[16];
            unsigned char   bytes[sizeof(float) * 16];
        };

        mat4 amat4(  8.0f,  0.0f,  1.0f,    7.0f,
                    16.0f,  2.0f, -3.0f,   -4.2f,
                    6.0f,  2.2f, -5.0f, -100.0f,
                    -2.0f, 10.0f,  5.5f,    8.0f );
        raw_map amat4_map = amat4.to_map();
        mock_data test_bytes = { { 8.0f, 16.0f,   6.0f, -2.0f,
                                0.0f,  2.0f,   2.2f, 10.0f,
                                1.0f, -3.0f,  -5.0f,  5.5f,
                                7.0f, -4.2, -100.0f,  8.0f } };
        
        size_t i = sizeof(float) * 16;
        
        while(i) {
            --i;
            CHECK_EQUAL( test_bytes.bytes[i], amat4_map[i] );
        } 
    }
}

SUITE( Matrix2x3 )
{
    TEST( Mat2x3Construction )
    {
        using namespace gfx;
        mat2x3 amat2x3;
        CHECK_EQUAL( 0.0f, amat2x3(0,0) );
        CHECK_EQUAL( 0.0f, amat2x3(0,1) );
        CHECK_EQUAL( 0.0f, amat2x3(0,2) );
        
        CHECK_EQUAL( 0.0f, amat2x3(1,0) );
        CHECK_EQUAL( 0.0f, amat2x3(1,1) );
        CHECK_EQUAL( 0.0f, amat2x3(1,2) );
        
        CHECK_EQUAL( amat2x3.n_cols, 2u );
        CHECK_EQUAL( amat2x3.n_rows, 3u );
        CHECK_EQUAL( amat2x3.n_comp, 6u );
    }
    
    TEST( Mat2x3CopyConstruction )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        mat2x3 bmat2x3 = amat2x3;
        CHECK_EQUAL( amat2x3, bmat2x3 );
        bmat2x3(0,0) = -15.0f;
        // No side effects
        CHECK( amat2x3(0,0) != bmat2x3(0,0) );
    }
    
    TEST( Mat2x3ExplicitConstruction )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        mat2x3 bmat2x3;
        bmat2x3(0,0) =  4.7f;    bmat2x3(1,0) =  0.0f;
        bmat2x3(0,1) =  0.0f;    bmat2x3(1,1) =  1.0f;
        bmat2x3(0,2) = -5.3f;    bmat2x3(1,2) = 18.0f;
        CHECK_EQUAL( bmat2x3, amat2x3 );
    }
    
    TEST( Mat2x3FillConstruction )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f );
        mat2x3 bmat2x3;
        bmat2x3(0,0) = 4.7f;    bmat2x3(1,0) = 4.7f;
        bmat2x3(0,1) = 4.7f;    bmat2x3(1,1) = 4.7f;
        bmat2x3(0,2) = 4.7f;    bmat2x3(1,2) = 4.7f;
        CHECK_EQUAL( bmat2x3, amat2x3 );
    }
    
    TEST( Mat2x3ColumnConstruction )
    {
        using namespace gfx;
        vec3 col0 ( 4.7f, 0.0f, -5.3f );
        vec3 col1 ( 0.0f, 1.0f, 18.0f );
        mat2x3 amat2x3( col0, col1 );
        mat2x3 bmat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        CHECK_EQUAL( bmat2x3, amat2x3 );
    }
    
    TEST( Mat2x3UpperIdentity )
    {
        using namespace gfx;
        mat2x3 amat2x3 = mat2x3::upper_identity();
        mat2x3 bmat2x3( 1.0f, 0.0f,
                        0.0f, 1.0f,
                        0.0f, 0.0f );
        CHECK_EQUAL( bmat2x3, amat2x3 );
    }
    
    TEST( Mat2x3RowConstruction )
    {
        using namespace gfx;
        vec2 row0 (  4.7f,  0.0f );
        vec2 row1 (  0.0f,  1.0f );
        vec2 row2 ( -5.3f, 18.0f );
        mat2x3 amat2x3 =  mat2x3::row_vectors( row0, row1, row2 );
        mat2x3 bmat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        CHECK_EQUAL( bmat2x3, amat2x3 );
    }
    
    TEST( Mat2x3FuzzyEquality )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        mat2x3 bmat2x3 = amat2x3;
        CHECK_EQUAL( amat2x3, bmat2x3 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat2x3(0,0) += f_lit::delta * 0.5f;
        CHECK_EQUAL( amat2x3, bmat2x3 );
        // ...and a modification of exactly delta isn't...
        bmat2x3(1,0) = f_lit::delta;
        CHECK( amat2x3 != bmat2x3 );
        // ...and that a modification greater than
        // delta is not
        bmat2x3(1,0) = 0.0f;
        bmat2x3(1,0) += std::nextafter(f_lit::delta, 1.0f);
        CHECK( amat2x3 != bmat2x3 );
    }
    
    TEST( Mat2x3Inequality )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        mat2x3 bmat2x3 = amat2x3;
        CHECK_EQUAL( amat2x3, bmat2x3 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat2x3(0,0) += f_lit::delta * 0.5f;
        CHECK( false == ( amat2x3 < bmat2x3 ) );
        bmat2x3(0,0) = 4.7f;
        bmat2x3(0,0) -= f_lit::delta * 0.5f;
        CHECK( false == ( amat2x3 > bmat2x3 ) );
        // ...and a modification of exactly delta isn't
        bmat2x3(0,0) = 4.7f;
        bmat2x3(0,0) += f_lit::delta;
        bmat2x3(0,1) += f_lit::delta;
        bmat2x3(0,2) += f_lit::delta;
        bmat2x3(1,0) += f_lit::delta;
        bmat2x3(1,1) += f_lit::delta;
        bmat2x3(1,2) += f_lit::delta;
        CHECK( amat2x3 < bmat2x3 );
        bmat2x3 = amat2x3;
        bmat2x3(0,0) -= f_lit::delta;
        bmat2x3(0,1) -= f_lit::delta;
        bmat2x3(0,2) -= f_lit::delta;
        bmat2x3(1,0) -= f_lit::delta;
        bmat2x3(1,1) -= f_lit::delta;
        bmat2x3(1,2) -= f_lit::delta;
        CHECK( amat2x3 > bmat2x3 );
    }
    
    TEST( Mat2x3InequalityEquality ) // LOL, wot?
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        mat2x3 bmat2x3 = amat2x3;
        CHECK_EQUAL( amat2x3, bmat2x3 );
        CHECK( amat2x3 <= bmat2x3 );
        CHECK( amat2x3 >= bmat2x3 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat2x3(0,0) += f_lit::delta * 0.5f;
        CHECK(  amat2x3 <= bmat2x3 );
        bmat2x3(0,0) = 4.7f;
        bmat2x3(0,0) -= f_lit::delta * 0.5f;
        CHECK( amat2x3 >= bmat2x3 );
        // ...and a modification of exactly delta isn't
        bmat2x3(0,0) = 4.7f;
        bmat2x3(0,0) += f_lit::delta;
        bmat2x3(0,1) += f_lit::delta;
        bmat2x3(0,2) += f_lit::delta;
        bmat2x3(1,0) += f_lit::delta;
        bmat2x3(1,1) += f_lit::delta;
        bmat2x3(1,2) += f_lit::delta;
        CHECK( amat2x3 < bmat2x3 );
        bmat2x3 = amat2x3;
        bmat2x3(0,0) -= f_lit::delta;
        bmat2x3(0,1) -= f_lit::delta;
        bmat2x3(0,2) -= f_lit::delta;
        bmat2x3(1,0) -= f_lit::delta;
        bmat2x3(1,1) -= f_lit::delta;
        bmat2x3(1,2) -= f_lit::delta;
        CHECK( amat2x3 > bmat2x3 );
    }
    
    TEST( Mat2x3Addition )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f, 0.0f,
                        0.0f, 0.0f,
                       -5.3f, 0.0f );
        mat2x3 bmat2x3( 0.0f, 0.0f,
                        0.0f, 1.0f,
                        0.0f, 18.0f );
        mat2x3 cmat2x3 = amat2x3 + bmat2x3;
        mat2x3 dmat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        CHECK_EQUAL( cmat2x3, dmat2x3 );
    }
    
    TEST( Mat2x3Subtraction )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f, 0.0f,
                        0.0f, 0.0f,
                       -5.3f, 0.0f );
        mat2x3 bmat2x3( 0.0f, 0.0f,
                        0.0f, 1.0f,
                        0.0f, 18.0f );
        mat2x3 cmat2x3 = amat2x3 - bmat2x3;
        mat2x3 dmat2x3( 4.7f,   0.0f,
                        0.0f,  -1.0f,
                       -5.3f, -18.0f );
        CHECK_EQUAL( cmat2x3, dmat2x3 );
    }
    
    TEST( Mat2x3Negation )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        mat2x3 bmat2x3 = -amat2x3;
        mat2x3 cmat2x3( -4.7f,   0.0f,
                         0.0f,  -1.0f,
                         5.3f, -18.0f );
        CHECK_EQUAL( cmat2x3, bmat2x3 );
    }
    
    TEST( Mat2x3Mult3x2 )
    {
        using namespace gfx;
        mat3x2 amat3x2 ( 4.7f,  0.0f, -5.3f,
                         0.0f,  1.0f, 18.0f );
        mat2x3 amat2x3 (  1.0f, 0.0f,
                          0.0f, 1.0f,
                         10.0f, 5.0f );
        
        mat3 amat3 = amat2x3 * amat3x2;
        mat3 bmat3 (  4.7f, 0.0f, -5.3f,
                      0.0f, 1.0f, 18.0f,
                     47.0f, 5.0f, 37.0f );
        CHECK_EQUAL( bmat3, amat3 );
        
    }
    
    TEST( Mat2x3Mult4x2 )
    {
        using namespace gfx;
        mat4x2 amat4x2 ( 4.7f,  0.0f, -5.3f, 10.0f,
                         0.0f,  1.0f, 18.0f, -2.0f );
        mat2x3 amat2x3 (  1.0f, 0.0f,
                          0.0f, 1.0f,
                         10.0f, 5.0f );
        
        mat4x3 amat4x3 = amat2x3 * amat4x2;
        mat4x3 bmat4x3 (  4.7f, 0.0f, -5.3f, 10.0f,
                          0.0f, 1.0f, 18.0f, -2.0f,
                         47.0f, 5.0f, 37.0f, 90.0f );
        CHECK_EQUAL( bmat4x3, amat4x3 );
        
    }
    
    TEST( Mat2x3Mult2 )
    {
        using namespace gfx;
        mat2 amat2 ( 4.7f,  0.0f,
                     0.0f,  1.0f );
        mat2x3 amat2x3 (  1.0f, 0.0f,
                          0.0f, 1.0f,
                         10.0f, 5.0f );
        
        mat2x3 bmat2x3 = amat2x3 * amat2;
        mat2x3 cmat2x3 (  4.7f, 0.0f,
                          0.0f, 1.0f,
                         47.0f, 5.0f );
        CHECK_EQUAL( cmat2x3, bmat2x3 );
        
    }
    
    TEST( Mat2x3VectorPostMultiply )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        vec2 avec2 ( 1.0f, -1.0f );
        vec3 avec3 = amat2x3 * avec2;
        vec3 bvec3 ( 4.7f, -1.0f, -23.3f );
        CHECK_EQUAL( bvec3, avec3 );
    }
    
    TEST( Mat2x3VectorPreMultiply )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        vec3 avec3 ( 1.0f, -1.0f, 0.0f );
        vec2 avec2 = avec3 * amat2x3;
        vec2 bvec2 ( 4.7f, -1.0f );
        CHECK_EQUAL( bvec2, avec2 );
    }
    
    TEST( Mat2x3ScalarPostMultiply )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        float anum ( 2.0f );
        mat2x3 bmat2x3 = amat2x3 * anum;
        mat2x3 cmat2x3(  9.4f,  0.0f,
                         0.0f,  2.0f,
                       -10.6f, 36.0f );
        CHECK_EQUAL( cmat2x3, bmat2x3 );
    }
    
    TEST( Mat2x3ScalarPreMultiply )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        float anum ( 2.0f );
        mat2x3 bmat2x3 = anum * amat2x3;
        mat2x3 cmat2x3(  9.4f,  0.0f,
                         0.0f,  2.0f,
                       -10.6f, 36.0f );
        CHECK_EQUAL( cmat2x3, bmat2x3 );
    }
    
    TEST( Mat2x3ScalarPostDivide )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        float anum ( 2.0f );
        mat2x3 bmat2x3 = amat2x3 / anum;
        mat2x3 cmat2x3( 2.35f, 0.0f,
                        0.0f,  0.5f,
                       -2.65f, 9.0f );
        CHECK_EQUAL( cmat2x3, bmat2x3 );
    }
    
    TEST( Mat2x3Assignment )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        mat2x3 bmat2x3;
        bmat2x3 = amat2x3;
        CHECK_EQUAL( amat2x3, bmat2x3 );
    }
    
    TEST( Mat2x3Lookup )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        CHECK_EQUAL( amat2x3(0,0),  4.7f );
        CHECK_EQUAL( amat2x3(0,1),  0.0f );
        CHECK_EQUAL( amat2x3(0,2), -5.3f );
        CHECK_EQUAL( amat2x3(1,0),  0.0f );
        CHECK_EQUAL( amat2x3(1,1),  1.0f );
        CHECK_EQUAL( amat2x3(1,2), 18.0f );
        
        vec3 avec3 ( 4.7f, 0.0f, -5.3f );
        CHECK_EQUAL( avec3, amat2x3[0] );
        avec3(y) = 10.0f;
        amat2x3[0] = avec3;
        CHECK_EQUAL( avec3, amat2x3[0] );
        avec3(x) = 2.0f;
        CHECK( avec3 != amat2x3[0] );
        amat2x3[0][0] = 2.0f;
        CHECK_EQUAL( avec3, amat2x3[0] );
    }
    
    TEST( Mat2x3ColumnLookup )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        CHECK_EQUAL( amat2x3(0,0),  4.7f );
        CHECK_EQUAL( amat2x3(0,1),  0.0f );
        CHECK_EQUAL( amat2x3(0,2), -5.3f );
        CHECK_EQUAL( amat2x3(1,0),  0.0f );
        CHECK_EQUAL( amat2x3(1,1),  1.0f );
        CHECK_EQUAL( amat2x3(1,2), 18.0f );
        
        vec3 avec3 ( 4.7f, 0.0f, -5.3f );
        CHECK_EQUAL( avec3, amat2x3.column(0) );
        avec3(y) = 10.0f;
        amat2x3.column(0) = avec3;
        CHECK_EQUAL( avec3, amat2x3.column(0) );
        avec3(x) = 2.0f;
        CHECK( avec3 != amat2x3.column(0) );
        amat2x3.column(0)[0] = 2.0f;
        CHECK_EQUAL( avec3, amat2x3.column(0) );
    }
    
    TEST( Mat2x3ColumnAssignment )
    {
        using namespace gfx;
        vec3 avec3( 4.7f, 0.0f, -5.3f );
        vec3 bvec3( 0.0f, 1.0f, 18.0f );
        mat2x3 amat2x3;
        amat2x3.columns( avec3, bvec3 );
        mat2x3 bmat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        CHECK_EQUAL( bmat2x3, amat2x3 );
    }
    
    TEST( Mat2x3FillAssignment )
    {
        using namespace gfx;
        mat2x3 amat2x3;
        amat2x3.fill( 2.0f );
        mat2x3 bmat2x3( 2.0f, 2.0f,
                        2.0f, 2.0f,
                        2.0f, 2.0f );
        CHECK_EQUAL( bmat2x3, amat2x3 );
    }
    
    TEST( Mat2x3RowLookup )
    {
        using namespace gfx;
        mat2x3 amat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        vec2 avec2( 4.7f, 0.0f );
        vec2 bvec2( 0.0f, 1.0f );
        vec2 cvec2( -5.3f, 18.0f );

        CHECK_EQUAL( avec2, amat2x3.row(0) );
        CHECK_EQUAL( bvec2, amat2x3.row(1) );
        CHECK_EQUAL( cvec2, amat2x3.row(2) );
        avec2(y) = 10.0f;
        amat2x3.row(0) = avec2;
        CHECK_EQUAL( avec2, amat2x3.row(0) );
        avec2(x) = 2.0f;
        CHECK( avec2 != amat2x3.row(0) );
        amat2x3.row(0)[0] = 2.0f;
        CHECK_EQUAL( avec2, amat2x3.row(0) );
    }
    
    TEST( Mat2x3RowAssignment )
    {
        using namespace gfx;
        vec2 avec2( 4.7f, 0.0f );
        vec2 bvec2( 0.0f, 1.0f );
        vec2 cvec2( -5.3f, 18.0f );
        mat2x3 amat2x3;
        amat2x3.rows( avec2, bvec2, cvec2 );
        mat2x3 bmat2x3( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        CHECK_EQUAL( bmat2x3, amat2x3 );
    }
}

SUITE( Matrix3x2 )
{
    TEST( Mat3x2Construction )
    {
        using namespace gfx;
        mat3x2 amat3x2;
        CHECK_EQUAL( amat3x2(0,0), 0.0f );
        CHECK_EQUAL( amat3x2(0,1), 0.0f );
        
        CHECK_EQUAL( amat3x2(1,0), 0.0f );
        CHECK_EQUAL( amat3x2(1,1), 0.0f );
        
        CHECK_EQUAL( amat3x2(2,0), 0.0f );
        CHECK_EQUAL( amat3x2(2,1), 0.0f );
        
        CHECK_EQUAL( amat3x2.n_cols, 3u );
        CHECK_EQUAL( amat3x2.n_rows, 2u );
        CHECK_EQUAL( amat3x2.n_comp, 6u );
    }
    
    TEST( Mat3x2CopyConstruction )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        mat3x2 bmat3x2 = amat3x2;
        CHECK_EQUAL( amat3x2, bmat3x2 );
        bmat3x2(0,0) = -15.0f;
        // No side effects
        CHECK( amat3x2(0,0) != bmat3x2(0,0) );
    }
    
    TEST( Mat3x2ExplicitConstruction )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );                        
        mat3x2 bmat3x2;
        bmat3x2(0,0) =  4.7f;    bmat3x2(1,0) =  0.0f;    bmat3x2(2,0) = -5.3f;
        bmat3x2(0,1) =  0.0f;    bmat3x2(1,1) =  1.0f;    bmat3x2(2,1) = 18.0f;

        CHECK_EQUAL( bmat3x2, amat3x2 );
    }
    
    TEST( Mat3x2FillConstruction )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f );
        mat3x2 bmat3x2;
        bmat3x2(0,0) = 4.7f;    bmat3x2(1,0) = 4.7f;    bmat3x2(2,0) = 4.7f;
        bmat3x2(0,1) = 4.7f;    bmat3x2(1,1) = 4.7f;    bmat3x2(2,1) = 4.7f;
        CHECK_EQUAL( bmat3x2, amat3x2 );
    }
    
    TEST( Mat3x2ColumnConstruction )
    {
        using namespace gfx;
        vec2 col0 ( 4.7f, 0.0f );
        vec2 col1 ( 0.0f, 1.0f );
        vec2 col2 ( -5.3f, 18.0f );
        mat3x2 amat3x2( col0, col1, col2 );
        mat3x2 bmat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        CHECK_EQUAL( bmat3x2, amat3x2 );
    }
    
    TEST( Mat3x2LeftIdentity )
    {
        using namespace gfx;
        mat3x2 amat3x2 = mat3x2::left_identity();
        mat3x2 bmat3x2( 1.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f );
        CHECK_EQUAL( bmat3x2, amat3x2 );
    }
    
    TEST( Mat3x2RowConstruction )
    {
        using namespace gfx;
        vec3 row0 (  4.7f,  0.0f, -5.3f );
        vec3 row1 (  0.0f,  1.0f, 18.0f );

        mat3x2 amat3x2 =  mat3x2::row_vectors( row0, row1 );
        mat3x2 bmat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        CHECK_EQUAL( bmat3x2, amat3x2 );
    }
    
    TEST( Mat3x2FuzzyEquality )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        mat3x2 bmat3x2 = amat3x2;
        CHECK_EQUAL( amat3x2, bmat3x2 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat3x2(0,0) += f_lit::delta * 0.5f;
        CHECK_EQUAL( amat3x2, bmat3x2 );
        // ...and a modification of exactly delta isn't...
        bmat3x2(1,0) = f_lit::delta;
        CHECK( amat3x2 != bmat3x2 );
        // ...and that a modification greater than
        // delta is not
        bmat3x2(1,0) = 0.0f;
        bmat3x2(1,0) += std::nextafter(f_lit::delta, 1.0f);
        CHECK( amat3x2 != bmat3x2 );
    }
    
    TEST( Mat3x2Inequality )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        mat3x2 bmat3x2 = amat3x2;
        CHECK_EQUAL( amat3x2, bmat3x2 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat3x2(0,0) += f_lit::delta * 0.5f;
        CHECK( false == ( amat3x2 < bmat3x2 ) );
        bmat3x2(0,0) = 4.7f;
        bmat3x2(0,0) -= f_lit::delta * 0.5f;
        CHECK( false == ( amat3x2 > bmat3x2 ) );
        // ...and a modification of exactly delta isn't
        bmat3x2(0,0) = 4.7f;
        bmat3x2(0,0) += f_lit::delta;
        bmat3x2(0,1) += f_lit::delta;
        bmat3x2(1,0) += f_lit::delta;
        bmat3x2(1,1) += f_lit::delta;
        bmat3x2(2,0) += f_lit::delta;
        bmat3x2(2,1) += f_lit::delta;
        CHECK( amat3x2 < bmat3x2 );
        bmat3x2 = amat3x2;
        bmat3x2(0,0) -= f_lit::delta;
        bmat3x2(0,1) -= f_lit::delta;
        bmat3x2(1,0) -= f_lit::delta;
        bmat3x2(1,1) -= f_lit::delta;
        bmat3x2(2,0) -= f_lit::delta;
        bmat3x2(2,1) -= f_lit::delta;
        CHECK( amat3x2 > bmat3x2 );
    }
    
    TEST( Mat3x2InequalityEquality ) // LOL, wot?
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f );
        mat3x2 bmat3x2 = amat3x2;
        CHECK_EQUAL( amat3x2, bmat3x2 );
        CHECK( amat3x2 <= bmat3x2 );
        CHECK( amat3x2 >= bmat3x2 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat3x2(0,0) += f_lit::delta * 0.5f;
        CHECK(  amat3x2 <= bmat3x2 );
        bmat3x2(0,0) = 4.7f;
        bmat3x2(0,0) -= f_lit::delta * 0.5f;
        CHECK( amat3x2 >= bmat3x2 );
        // ...and a modification of exactly delta isn't
        bmat3x2(0,0) = 4.7f;
        bmat3x2(0,0) += f_lit::delta;
        bmat3x2(0,1) += f_lit::delta;
        bmat3x2(1,0) += f_lit::delta;
        bmat3x2(1,1) += f_lit::delta;
        bmat3x2(2,0) += f_lit::delta;
        bmat3x2(2,1) += f_lit::delta;
        CHECK( amat3x2 < bmat3x2 );
        bmat3x2 = amat3x2;
        bmat3x2(0,0) -= f_lit::delta;
        bmat3x2(0,1) -= f_lit::delta;
        bmat3x2(1,0) -= f_lit::delta;
        bmat3x2(1,1) -= f_lit::delta;
        bmat3x2(2,0) -= f_lit::delta;
        bmat3x2(2,1) -= f_lit::delta;
        CHECK( amat3x2 > bmat3x2 );
    }
    
    TEST( Mat3x2Addition )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f, 0.0f, -5.3f,
                        0.0f, 0.0f,  0.0f );
        mat3x2 bmat3x2( 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 18.0f );
        mat3x2 cmat3x2 = amat3x2 + bmat3x2;
        mat3x2 dmat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        CHECK_EQUAL( cmat3x2, dmat3x2 );
    }
    
    TEST( Mat3x2Subtraction )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f, 0.0f, -5.3f,
                        0.0f, 0.0f,  0.0f );
        mat3x2 bmat3x2( 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 18.0f );
        mat3x2 cmat3x2 = amat3x2 - bmat3x2;
        mat3x2 dmat3x2( 4.7f,   0.0f,  -5.3f,
                        0.0f,  -1.0f, -18.0f );
        CHECK_EQUAL( cmat3x2, dmat3x2 );
    }
    
    TEST( Mat3x2Negation )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        mat3x2 bmat3x2 = -amat3x2;
        mat3x2 cmat3x2( -4.7f,   0.0f,   5.3f,
                         0.0f,  -1.0f, -18.0f );
        CHECK_EQUAL( cmat3x2, bmat3x2 );
    }
    
    TEST( Mat3x2Mult2x3 )
    {
        using namespace gfx;
        mat3x2 amat3x2 ( 4.7f,  0.0f, -5.3f,
                         0.0f,  1.0f, 18.0f );
        mat2x3 amat2x3 (  1.0f, 0.0f,
                          0.0f, 1.0f,
                         10.0f, 5.0f );
        
        mat2 amat2 = amat3x2 * amat2x3;
        mat2 bmat2 ( -48.3f, -26.5,
                     180.0f, 91.0f );
        CHECK_EQUAL( bmat2, amat2 );
        
    }
    
    TEST( Mat3x2Mult4x3 )
    {
        using namespace gfx;
        mat3x2 amat3x2 ( 4.7f,  0.0f, 2.0f,
                         0.0f,  1.0f, 5.0f );
        mat4x3 amat4x3 (  4.7f, 0.0f, 2.0f, 10.0f,
                          0.0f, 1.0f, 5.0f, -2.0f,
                         -5.3f, 18.0f, -3.0f, 1.0f );
        
        mat4x2 amat4x2 = amat3x2 * amat4x3;
        mat4x2 bmat4x2 ( 11.49f, 36.0f,   3.4f, 49.0f,
                         -26.5f, 91.0f, -10.0f,  3.0f );
        CHECK_EQUAL( bmat4x2, amat4x2 );
        
    }
    
    TEST( Mat3x2Mult3 )
    {
        using namespace gfx;
        mat3x2 amat3x2 ( 4.7f,  0.0f, 2.0f,
                         0.0f,  1.0f, 5.0f );
        mat3 amat3 (  4.7f,  0.0f,  2.0f,
                      0.0f,  1.0f,  5.0f,
                     -5.3f, 18.0f, -3.0f );
        
        mat3x2 bmat3x2 = amat3x2 * amat3;
        mat3x2 cmat3x2 ( 11.49f, 36.0f,   3.4f,
                         -26.5f, 91.0f, -10.0f );
        CHECK_EQUAL( cmat3x2, bmat3x2 );
        
    }
    
    TEST( Mat3x2VectorPostMultiply )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        vec3 avec3 ( 1.0f, 0.0f, 10.0f );
        vec2 avec2 = amat3x2 * avec3;
        vec2 bvec2 ( -48.3f, 180.0f );
        CHECK_EQUAL( bvec2, avec2 );
    }
    
    TEST( Mat3x2VectorPreMultiply )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        vec2 avec2 ( 10.0f, 5.0f );
        vec3 avec3 = avec2 * amat3x2;
        vec3 bvec3 ( 47.0f, 5.0f, 37.0f );
        CHECK_EQUAL( bvec3, avec3 );
    }
    
    TEST( Mat3x2ScalarPostMultiply )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        float anum ( 2.0f );
        mat3x2 bmat3x2 = amat3x2 * anum;
        mat3x2 cmat3x2(  9.4f,  0.0f, -10.6f,
                         0.0f,  2.0f,  36.0f );
        CHECK_EQUAL( cmat3x2, bmat3x2 );
    }
    
    TEST( Mat3x2ScalarPreMultiply )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        float anum ( 2.0f );
        mat3x2 bmat3x2 = anum * amat3x2;
        mat3x2 cmat3x2(  9.4f,  0.0f, -10.6f,
                         0.0f,  2.0f,  36.0f );
        CHECK_EQUAL( cmat3x2, bmat3x2 );
    }
    
    TEST( Mat3x2ScalarPostDivide )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        float anum ( 2.0f );
        mat3x2 bmat3x2 = amat3x2 / anum;
        mat3x2 cmat3x2( 2.35f, 0.0f, -2.65f,
                        0.0f,  0.5f, 9.0f   );
        CHECK_EQUAL( cmat3x2, bmat3x2 );
    }
    
    TEST( Mat3x2Assignment )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        mat3x2 bmat3x2;
        bmat3x2 = amat3x2;
        CHECK_EQUAL( amat3x2, bmat3x2 );
    }
    
    TEST( Mat3x2Lookup )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        CHECK_EQUAL( amat3x2(0,0),  4.7f );
        CHECK_EQUAL( amat3x2(0,1),  0.0f );
        CHECK_EQUAL( amat3x2(1,0),  0.0f );
        CHECK_EQUAL( amat3x2(1,1),  1.0f );
        CHECK_EQUAL( amat3x2(2,0), -5.3f );
        CHECK_EQUAL( amat3x2(2,1), 18.0f );
        
        vec2 avec2 ( 4.7f, 0.0f );
        CHECK_EQUAL( avec2, amat3x2[0] );
        avec2(y) = 10.0f;
        amat3x2[0] = avec2;
        CHECK_EQUAL( avec2, amat3x2[0] );
        avec2(x) = 2.0f;
        CHECK( avec2 != amat3x2[0] );
        amat3x2[0][0] = 2.0f;
        CHECK_EQUAL( avec2, amat3x2[0] );
    }
    
    TEST( Mat3x2ColumnLookup )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        CHECK_EQUAL( amat3x2(0,0),  4.7f );
        CHECK_EQUAL( amat3x2(0,1),  0.0f );
        CHECK_EQUAL( amat3x2(1,0),  0.0f );
        CHECK_EQUAL( amat3x2(1,1),  1.0f );
        CHECK_EQUAL( amat3x2(2,0), -5.3f );
        CHECK_EQUAL( amat3x2(2,1), 18.0f );
        
        vec2 avec2 ( 4.7f, 0.0f );
        CHECK_EQUAL( avec2, amat3x2.column(0) );
        avec2(y) = 10.0f;
        amat3x2.column(0) = avec2;
        CHECK_EQUAL( avec2, amat3x2.column(0) );
        avec2(x) = 2.0f;
        CHECK( avec2 != amat3x2.column(0) );
        amat3x2.column(0)[0] = 2.0f;
        CHECK_EQUAL( avec2, amat3x2.column(0) );
    }
    
    TEST( Mat3x2ColumnAssignment )
    {
        using namespace gfx;
        vec2 avec2( 4.7f, 0.0f );
        vec2 bvec2( 0.0f, 1.0f );
        vec2 cvec2( -5.3f, 18.0f );
        mat3x2 amat3x2;
        amat3x2.columns( avec2, bvec2, cvec2 );
        mat3x2 bmat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        CHECK_EQUAL( bmat3x2, amat3x2 );
    }
    
    TEST( Mat3x2FillAssignment )
    {
        using namespace gfx;
        mat3x2 amat3x2;
        amat3x2.fill( 2.0f );
        mat3x2 bmat3x2( 2.0f, 2.0f, 2.0f,
                        2.0f, 2.0f, 2.0f );
        CHECK_EQUAL( bmat3x2, amat3x2 );
    }
    
    TEST( Mat3x2RowLookup )
    {
        using namespace gfx;
        mat3x2 amat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        vec3 avec3( 4.7f, 0.0f, -5.3f );
        vec3 bvec3( 0.0f, 1.0f, 18.0f );

        CHECK_EQUAL( avec3, amat3x2.row(0) );
        CHECK_EQUAL( bvec3, amat3x2.row(1) );
        avec3(y) = 10.0f;
        amat3x2.row(0) = avec3;
        CHECK_EQUAL( avec3, amat3x2.row(0) );
        avec3(x) = 2.0f;
        CHECK( avec3 != amat3x2.row(0) );
        amat3x2.row(0)[0] = 2.0f;
        CHECK_EQUAL( avec3, amat3x2.row(0) );
    }
    
    TEST( Mat3x2RowAssignment )
    {
        using namespace gfx;
        vec3 avec3( 4.7f, 0.0f, -5.3f );
        vec3 bvec3( 0.0f, 1.0f, 18.0f );
        mat3x2 amat3x2;
        amat3x2.rows( avec3, bvec3 );
        mat3x2 bmat3x2( 4.7f,  0.0f, -5.3f,
                        0.0f,  1.0f, 18.0f );
        CHECK_EQUAL( bmat3x2, amat3x2 );
    }
}



SUITE( Matrix2x4 )
{
    TEST( Mat2x4Construction )
    {
        using namespace gfx;
        mat2x4 amat2x4;
        CHECK_EQUAL( 0.0f, amat2x4(0,0) );
        CHECK_EQUAL( 0.0f, amat2x4(0,1) );
        CHECK_EQUAL( 0.0f, amat2x4(0,2) );
        CHECK_EQUAL( 0.0f, amat2x4(0,3) );
        
        CHECK_EQUAL( 0.0f, amat2x4(1,0) );
        CHECK_EQUAL( 0.0f, amat2x4(1,1) );
        CHECK_EQUAL( 0.0f, amat2x4(1,2) );
        CHECK_EQUAL( 0.0f, amat2x4(1,3) );
        
        CHECK_EQUAL( amat2x4.n_cols, 2u );
        CHECK_EQUAL( amat2x4.n_rows, 4u );
        CHECK_EQUAL( amat2x4.n_comp, 8u );
    }
    
    TEST( Mat2x4CopyConstruction )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        mat2x4 bmat2x4 = amat2x4;
        CHECK_EQUAL( amat2x4, bmat2x4 );
        bmat2x4(0,0) = -15.0f;
        // No side effects
        CHECK( amat2x4(0,0) != bmat2x4(0,0) );
    }
    
    TEST( Mat2x4ExplicitConstruction )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        mat2x4 bmat2x4;
        bmat2x4(0,0) =  4.7f;    bmat2x4(1,0) =  0.0f;
        bmat2x4(0,1) =  0.0f;    bmat2x4(1,1) =  1.0f;
        bmat2x4(0,2) = -5.3f;    bmat2x4(1,2) = 18.0f;
        bmat2x4(0,3) = 10.0f;    bmat2x4(1,3) = -2.0f;
        CHECK_EQUAL( bmat2x4, amat2x4 );
    }
    
    TEST( Mat2x4FillConstruction )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f );
        mat2x4 bmat2x4;
        bmat2x4(0,0) = 4.7f;    bmat2x4(1,0) = 4.7f;
        bmat2x4(0,1) = 4.7f;    bmat2x4(1,1) = 4.7f;
        bmat2x4(0,2) = 4.7f;    bmat2x4(1,2) = 4.7f;
        bmat2x4(0,3) = 4.7f;    bmat2x4(1,3) = 4.7f;
        CHECK_EQUAL( bmat2x4, amat2x4 );
    }
    
    TEST( Mat2x4ColumnConstruction )
    {
        using namespace gfx;
        vec4 col0 ( 4.7f, 0.0f, -5.3f, 10.0f );
        vec4 col1 ( 0.0f, 1.0f, 18.0f, -2.0f );
        mat2x4 amat2x4( col0, col1 );
        mat2x4 bmat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        CHECK_EQUAL( bmat2x4, amat2x4 );
    }
    
    TEST( Mat2x4UpperIdentity )
    {
        using namespace gfx;
        mat2x4 amat2x4 = mat2x4::upper_identity();
        mat2x4 bmat2x4( 1.0f, 0.0f,
                        0.0f, 1.0f,
                        0.0f, 0.0f,
                        0.0f, 0.0f );
        CHECK_EQUAL( bmat2x4, amat2x4 );
    }
    
    TEST( Mat2x4RowConstruction )
    {
        using namespace gfx;
        vec2 row0 (  4.7f,  0.0f );
        vec2 row1 (  0.0f,  1.0f );
        vec2 row2 ( -5.3f, 18.0f );
        vec2 row3 ( 10.0f, -2.0f );
        mat2x4 amat2x4 =  mat2x4::row_vectors( row0, row1, row2, row3 );
        mat2x4 bmat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        CHECK_EQUAL( bmat2x4, amat2x4 );
    }
    
    TEST( Mat2x4FuzzyEquality )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        mat2x4 bmat2x4 = amat2x4;
        CHECK_EQUAL( amat2x4, bmat2x4 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat2x4(0,0) += f_lit::delta * 0.5f;
        CHECK_EQUAL( amat2x4, bmat2x4 );
        // ...and a modification of exactly delta isn't...
        bmat2x4(1,0) = f_lit::delta;
        CHECK( amat2x4 != bmat2x4 );
        // ...and that a modification greater than
        // delta is not
        bmat2x4(1,0) = 0.0f;
        bmat2x4(1,0) += std::nextafter(f_lit::delta, 1.0f);
        CHECK( amat2x4 != bmat2x4 );
    }
    
    TEST( Mat2x4Inequality )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        mat2x4 bmat2x4 = amat2x4;
        CHECK_EQUAL( amat2x4, bmat2x4 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat2x4(0,0) += f_lit::delta * 0.5f;
        CHECK( false == ( amat2x4 < bmat2x4 ) );
        bmat2x4(0,0) = 4.7f;
        bmat2x4(0,0) -= f_lit::delta * 0.5f;
        CHECK( false == ( amat2x4 > bmat2x4 ) );
        // ...and a modification of exactly delta isn't
        bmat2x4(0,0) = 4.7f;
        bmat2x4(0,0) += f_lit::delta;
        bmat2x4(0,1) += f_lit::delta;
        bmat2x4(0,2) += f_lit::delta;
        bmat2x4(0,3) += f_lit::delta;
        bmat2x4(1,0) += f_lit::delta;
        bmat2x4(1,1) += f_lit::delta;
        bmat2x4(1,2) += f_lit::delta;
        bmat2x4(1,3) += f_lit::delta;
        CHECK( amat2x4 < bmat2x4 );
        bmat2x4 = amat2x4;
        bmat2x4(0,0) -= f_lit::delta;
        bmat2x4(0,1) -= f_lit::delta;
        bmat2x4(0,2) -= f_lit::delta;
        bmat2x4(0,3) -= f_lit::delta;
        bmat2x4(1,0) -= f_lit::delta;
        bmat2x4(1,1) -= f_lit::delta;
        bmat2x4(1,2) -= f_lit::delta;
        bmat2x4(1,3) -= f_lit::delta;
        CHECK( amat2x4 > bmat2x4 );
    }
    
    TEST( Mat2x4InequalityEquality ) // LOL, wot?
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        mat2x4 bmat2x4 = amat2x4;
        CHECK_EQUAL( amat2x4, bmat2x4 );
        CHECK( amat2x4 <= bmat2x4 );
        CHECK( amat2x4 >= bmat2x4 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat2x4(0,0) += f_lit::delta * 0.5f;
        CHECK(  amat2x4 <= bmat2x4 );
        bmat2x4(0,0) = 4.7f;
        bmat2x4(0,0) -= f_lit::delta * 0.5f;
        CHECK( amat2x4 >= bmat2x4 );
        // ...and a modification of exactly delta isn't
        bmat2x4(0,0) = 4.7f;
        bmat2x4(0,0) += f_lit::delta;
        bmat2x4(0,1) += f_lit::delta;
        bmat2x4(0,2) += f_lit::delta;
        bmat2x4(0,3) += f_lit::delta;
        bmat2x4(1,0) += f_lit::delta;
        bmat2x4(1,1) += f_lit::delta;
        bmat2x4(1,2) += f_lit::delta;
        bmat2x4(1,3) += f_lit::delta;
        CHECK( amat2x4 < bmat2x4 );
        bmat2x4 = amat2x4;
        bmat2x4(0,0) -= f_lit::delta;
        bmat2x4(0,1) -= f_lit::delta;
        bmat2x4(0,2) -= f_lit::delta;
        bmat2x4(0,3) -= f_lit::delta;
        bmat2x4(1,0) -= f_lit::delta;
        bmat2x4(1,1) -= f_lit::delta;
        bmat2x4(1,2) -= f_lit::delta;
        bmat2x4(1,3) -= f_lit::delta;
        CHECK( amat2x4 > bmat2x4 );
    }
    
    TEST( Mat2x4Addition )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f, 0.0f,
                        0.0f, 0.0f,
                       -5.3f, 0.0f,
                       10.0f, 0.0f );
        mat2x4 bmat2x4( 0.0f, 0.0f,
                        0.0f, 1.0f,
                        0.0f, 18.0f,
                        0.0f, -2.0f );
        mat2x4 cmat2x4 = amat2x4 + bmat2x4;
        mat2x4 dmat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        CHECK_EQUAL( cmat2x4, dmat2x4 );
    }
    
    TEST( Mat2x4Subtraction )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f, 0.0f,
                        0.0f, 0.0f,
                        -5.3f, 0.0f,
                       10.0f, 0.0f );
        mat2x4 bmat2x4( 0.0f, 0.0f,
                        0.0f, 1.0f,
                        0.0f, 18.0f,
                        0.0f, -2.0f );
        mat2x4 cmat2x4 = amat2x4 - bmat2x4;
        mat2x4 dmat2x4( 4.7f,   0.0f,
                        0.0f,  -1.0f,
                       -5.3f, -18.0f,
                        10.0f,  2.0f );
        CHECK_EQUAL( cmat2x4, dmat2x4 );
    }
    
    TEST( Mat2x4Negation )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        mat2x4 bmat2x4 = -amat2x4;
        mat2x4 cmat2x4( -4.7f,   0.0f,
                         0.0f,  -1.0f,
                         5.3f, -18.0f,
                        -10.0f, 2.0f );
        CHECK_EQUAL( cmat2x4, bmat2x4 );
    }
    
    TEST( Mat2x4Mult4x2 )
    {
        using namespace gfx;
        mat4x2 amat4x2 ( 4.7f,  0.0f, -5.3f, 10.0f,
                         0.0f,  1.0f, 18.0f, -2.0f );
        mat2x4 amat2x4 (  1.0f, 0.0f,
                          0.0f, 1.0f,
                         10.0f, 5.0f,
                         1.5f, -1.0f );
        
        mat4 amat4 = amat2x4 * amat4x2;
        mat4 bmat4 ( 4.7f, 0.0f, -5.3f, 10.0f,
                     0.0f, 1.0f, 18.0f, -2.0f,
                     47.0f, 5.0f, 37.0f, 90.0f,
                     7.05f, -1.0f, -25.95f, 17.0f );
        
        CHECK_EQUAL( bmat4, amat4 );
    }
    
    TEST( Mat2x4Mult3x2 )
    {
        using namespace gfx;
        mat2x4 amat2x4 ( 4.7f,  0.0f,
                         0.0f,  1.0f, 
                        -5.3f, 10.0f,
                        18.0f, -2.0f );
        mat3x2 amat3x2 ( 1.0f, 0.0f,  1.5f,
                         0.0f, 1.0f, -1.0f );
        
        mat3x4 amat3x4 = amat2x4 * amat3x2;
        mat3x4 bmat3x4 (  4.7f,  0.0f,   7.05,
                          0.0f,  1.0f,  -1.0f,
                         -5.3f, 10.0f, -17.95f,
                         18.0f, -2.0f,  29.0f  );
        
        CHECK_EQUAL( bmat3x4, amat3x4 );
    }
    
    TEST( Mat2x4Mult2 )
    {
        using namespace gfx;
        mat2x4 amat2x4 ( 4.7f,  0.0f,
                         0.0f,  1.0f, 
                        -5.3f, 10.0f,
                        18.0f, -2.0f );
        mat2 amat2 = mat2::identity();
        
        mat2x4 bmat2x4 = amat2x4 * amat2;
        
        CHECK_EQUAL( amat2x4, bmat2x4 );
    }
    
    TEST( Mat2x4VectorPostMultiply )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        vec2 avec2 ( 1.0f, -1.0f );
        vec4 avec4 = amat2x4 * avec2;
        vec4 bvec4 ( 4.7f, -1.0f, -23.3f, 12.0f );
        CHECK_EQUAL( bvec4, avec4 );
    }
    
    TEST( Mat2x4VectorPreMultiply )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        vec4 avec4 ( 1.0f, -1.0f, 0.0f, 10.0f );
        vec2 avec2 = avec4 * amat2x4;
        vec2 bvec2 ( 104.7f, -21.0f );
        CHECK_EQUAL( bvec2, avec2 );
    }
    
    TEST( Mat2x4ScalarPostMultiply )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f  );
        float anum ( 2.0f );
        mat2x4 bmat2x4 = amat2x4 * anum;
        mat2x4 cmat2x4(  9.4f,  0.0f,
                         0.0f,  2.0f,
                       -10.6f, 36.0f,
                        20.0f, -4.0f );
        CHECK_EQUAL( cmat2x4, bmat2x4 );
    }
    
    TEST( Mat2x4ScalarPreMultiply )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f  );
        float anum ( 2.0f );
        mat2x4 bmat2x4 = anum * amat2x4;
        mat2x4 cmat2x4(  9.4f,  0.0f,
                         0.0f,  2.0f,
                       -10.6f, 36.0f,
                        20.0f, -4.0f );
        CHECK_EQUAL( cmat2x4, bmat2x4 );
    }
    
    TEST( Mat2x4ScalarPostDivide )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        float anum ( 2.0f );
        mat2x4 bmat2x4 = amat2x4 / anum;
        mat2x4 cmat2x4( 2.35f, 0.0f,
                        0.0f,  0.5f,
                       -2.65f, 9.0f,
                        5.0f, -1.0f );
        CHECK_EQUAL( cmat2x4, bmat2x4 );
    }
    
    TEST( Mat2x4Assignment )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        mat2x4 bmat2x4;
        bmat2x4 = amat2x4;
        CHECK_EQUAL( amat2x4, bmat2x4 );
    }
    
    TEST( Mat2x4Lookup )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        CHECK_EQUAL( amat2x4(0,0),  4.7f );
        CHECK_EQUAL( amat2x4(0,1),  0.0f );
        CHECK_EQUAL( amat2x4(0,2), -5.3f );
        CHECK_EQUAL( amat2x4(0,3), 10.0f );
        CHECK_EQUAL( amat2x4(1,0),  0.0f );
        CHECK_EQUAL( amat2x4(1,1),  1.0f );
        CHECK_EQUAL( amat2x4(1,2), 18.0f );
        CHECK_EQUAL( amat2x4(1,3), -2.0f );
        
        vec4 avec4 ( 4.7f, 0.0f, -5.3f, 10.0f );
        CHECK_EQUAL( avec4, amat2x4[0] );
        avec4(y) = 10.0f;
        amat2x4[0] = avec4;
        CHECK_EQUAL( avec4, amat2x4[0] );
        avec4(x) = 2.0f;
        CHECK( avec4 != amat2x4[0] );
        amat2x4[0][0] = 2.0f;
        CHECK_EQUAL( avec4, amat2x4[0] );
    }
    
    TEST( Mat2x4ColumnLookup )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        CHECK_EQUAL( amat2x4(0,0),  4.7f );
        CHECK_EQUAL( amat2x4(0,1),  0.0f );
        CHECK_EQUAL( amat2x4(0,2), -5.3f );
        CHECK_EQUAL( amat2x4(0,3), 10.0f );
        CHECK_EQUAL( amat2x4(1,0),  0.0f );
        CHECK_EQUAL( amat2x4(1,1),  1.0f );
        CHECK_EQUAL( amat2x4(1,2), 18.0f );
        CHECK_EQUAL( amat2x4(1,3), -2.0f );
        
        vec4 avec4 ( 4.7f, 0.0f, -5.3f, 10.0f );
        CHECK_EQUAL( avec4, amat2x4.column(0) );
        avec4(y) = 10.0f;
        amat2x4.column(0) = avec4;
        CHECK_EQUAL( avec4, amat2x4.column(0) );
        avec4(x) = 2.0f;
        CHECK( avec4 != amat2x4.column(0) );
        amat2x4.column(0)[0] = 2.0f;
        CHECK_EQUAL( avec4, amat2x4.column(0) );
    }
    
    TEST( Mat2x4ColumnAssignment )
    {
        using namespace gfx;
        vec4 avec4( 4.7f, 0.0f, -5.3f, 10.0f );
        vec4 bvec4( 0.0f, 1.0f, 18.0f, -2.0f );
        mat2x4 amat2x4;
        amat2x4.columns( avec4, bvec4 );
        mat2x4 bmat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        CHECK_EQUAL( bmat2x4, amat2x4 );
    }
    
    TEST( Mat2x4FillAssignment )
    {
        using namespace gfx;
        mat2x4 amat2x4;
        amat2x4.fill( 2.0f );
        mat2x4 bmat2x4( 2.0f, 2.0f,
                        2.0f, 2.0f,
                        2.0f, 2.0f,
                        2.0f, 2.0f );
        CHECK_EQUAL( bmat2x4, amat2x4 );
    }
    
    TEST( Mat2x4RowLookup )
    {
        using namespace gfx;
        mat2x4 amat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        vec2 avec2( 4.7f, 0.0f );
        vec2 bvec2( 0.0f, 1.0f );
        vec2 cvec2( -5.3f, 18.0f );
        vec2 dvec2( 10.0f, -2.0f );

        CHECK_EQUAL( avec2, amat2x4.row(0) );
        CHECK_EQUAL( bvec2, amat2x4.row(1) );
        CHECK_EQUAL( cvec2, amat2x4.row(2) );
        CHECK_EQUAL( dvec2, amat2x4.row(3) );
        avec2(y) = 10.0f;
        amat2x4.row(0) = avec2;
        CHECK_EQUAL( avec2, amat2x4.row(0) );
        avec2(x) = 2.0f;
        CHECK( avec2 != amat2x4.row(0) );
        amat2x4.row(0)[0] = 2.0f;
        CHECK_EQUAL( avec2, amat2x4.row(0) );
    }
    
    TEST( Mat2x4RowAssignment )
    {
        using namespace gfx;
        vec2 avec2( 4.7f, 0.0f );
        vec2 bvec2( 0.0f, 1.0f );
        vec2 cvec2( -5.3f, 18.0f );
        vec2 dvec2( 10.0f, -2.0f );
        mat2x4 amat2x4;
        amat2x4.rows( avec2, bvec2, cvec2, dvec2 );
        mat2x4 bmat2x4( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        CHECK_EQUAL( bmat2x4, amat2x4 );
    }
}



SUITE( Matrix4x2 )
{
    TEST( Mat4x2Construction )
    {
        using namespace gfx;
        mat4x2 amat4x2;
        CHECK_EQUAL( amat4x2(0,0), 0.0f );
        CHECK_EQUAL( amat4x2(0,1), 0.0f );
        
        CHECK_EQUAL( amat4x2(1,0), 0.0f );
        CHECK_EQUAL( amat4x2(1,1), 0.0f );
        
        CHECK_EQUAL( amat4x2(2,0), 0.0f );
        CHECK_EQUAL( amat4x2(2,1), 0.0f );
        
        CHECK_EQUAL( amat4x2(3,0), 0.0f );
        CHECK_EQUAL( amat4x2(3,1), 0.0f );
        
        CHECK_EQUAL( 4u, amat4x2.n_cols );
        CHECK_EQUAL( 2u, amat4x2.n_rows );
        CHECK_EQUAL( 8u, amat4x2.n_comp );
    }
    
    TEST( Mat4x2CopyConstruction )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        mat4x2 bmat4x2 = amat4x2;
        CHECK_EQUAL( amat4x2, bmat4x2 );
        bmat4x2(0,0) = -15.0f;
        // No side effects
        CHECK( amat4x2(0,0) != bmat4x2(0,0) );
    }

    TEST( Mat4x2ExplicitConstruction )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );                        
        mat4x2 bmat4x2;
        bmat4x2(0,0) =  4.7f;    bmat4x2(1,0) =  0.0f;
        bmat4x2(2,0) = -5.3f;    bmat4x2(3,0) = 10.0f;
        
        bmat4x2(0,1) =  0.0f;    bmat4x2(1,1) =  1.0f;
        bmat4x2(2,1) = 18.0f;    bmat4x2(3,1) = -2.0f;

        CHECK_EQUAL( bmat4x2, amat4x2 );
    }
    
    TEST( Mat4x2FillConstruction )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f );
        mat4x2 bmat4x2;
        bmat4x2(0,0) = 4.7f;    bmat4x2(1,0) = 4.7f;
        bmat4x2(2,0) = 4.7f;    bmat4x2(3,0) = 4.7f;
        
        bmat4x2(0,1) = 4.7f;    bmat4x2(1,1) = 4.7f;
        bmat4x2(2,1) = 4.7f;    bmat4x2(3,1) = 4.7f;
        CHECK_EQUAL( bmat4x2, amat4x2 );
    }
    
    TEST( Mat4x2ColumnConstruction )
    {
        using namespace gfx;
        vec2 col0 ( 4.7f, 0.0f );
        vec2 col1 ( 0.0f, 1.0f );
        vec2 col2 ( -5.3f, 18.0f );
        vec2 col3 ( 10.0f, -2.0f );
        mat4x2 amat4x2( col0, col1, col2, col3 );
        mat4x2 bmat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        CHECK_EQUAL( bmat4x2, amat4x2 );
    }
    
    TEST( Mat4x2LeftIdentity )
    {
        using namespace gfx;
        mat4x2 amat4x2 = mat4x2::left_identity();
        mat4x2 bmat4x2( 1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f );
        CHECK_EQUAL( bmat4x2, amat4x2 );
    }
    
    TEST( Mat4x2RowConstruction )
    {
        using namespace gfx;
        vec4 row0 (  4.7f,  0.0f, -5.3f, 10.0f );
        vec4 row1 (  0.0f,  1.0f, 18.0f, -2.0f );

        mat4x2 amat4x2 =  mat4x2::row_vectors( row0, row1 );
        mat4x2 bmat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        CHECK_EQUAL( bmat4x2, amat4x2 );
    }
    
    TEST( Mat4x2FuzzyEquality )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        mat4x2 bmat4x2 = amat4x2;
        CHECK_EQUAL( amat4x2, bmat4x2 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat4x2(0,0) += f_lit::delta * 0.5f;
        CHECK_EQUAL( amat4x2, bmat4x2 );
        // ...and a modification of exactly delta isn't...
        bmat4x2(1,0) = f_lit::delta;
        CHECK( amat4x2 != bmat4x2 );
        // ...and that a modification greater than
        // delta is not
        bmat4x2(1,0) = 0.0f;
        bmat4x2(1,0) += std::nextafter(f_lit::delta, 1.0f);
        CHECK( amat4x2 != bmat4x2 );
    }
    
    TEST( Mat4x2Inequality )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        mat4x2 bmat4x2 = amat4x2;
        CHECK_EQUAL( amat4x2, bmat4x2 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat4x2(0,0) += f_lit::delta * 0.5f;
        CHECK( false == ( amat4x2 < bmat4x2 ) );
        bmat4x2(0,0) = 4.7f;
        bmat4x2(0,0) -= f_lit::delta * 0.5f;
        CHECK( false == ( amat4x2 > bmat4x2 ) );
        // ...and a modification of exactly delta isn't
        bmat4x2(0,0) = 4.7f;
        bmat4x2(0,0) += f_lit::delta;
        bmat4x2(0,1) += f_lit::delta;
        bmat4x2(1,0) += f_lit::delta;
        bmat4x2(1,1) += f_lit::delta;
        bmat4x2(2,0) += f_lit::delta;
        bmat4x2(2,1) += f_lit::delta;
        bmat4x2(3,0) += f_lit::delta;
        bmat4x2(3,1) += f_lit::delta;
        CHECK( amat4x2 < bmat4x2 );
        bmat4x2 = amat4x2;
        bmat4x2(0,0) -= f_lit::delta;
        bmat4x2(0,1) -= f_lit::delta;
        bmat4x2(1,0) -= f_lit::delta;
        bmat4x2(1,1) -= f_lit::delta;
        bmat4x2(2,0) -= f_lit::delta;
        bmat4x2(2,1) -= f_lit::delta;
        bmat4x2(3,0) -= f_lit::delta;
        bmat4x2(3,1) -= f_lit::delta;
        CHECK( amat4x2 > bmat4x2 );
    }
    
    TEST( Mat4x2InequalityEquality ) // LOL, wot?
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f,
                        0.0f,  1.0f,
                       -5.3f, 18.0f,
                       10.0f, -2.0f );
        mat4x2 bmat4x2 = amat4x2;
        CHECK_EQUAL( amat4x2, bmat4x2 );
        CHECK( amat4x2 <= bmat4x2 );
        CHECK( amat4x2 >= bmat4x2 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat4x2(0,0) += f_lit::delta * 0.5f;
        CHECK(  amat4x2 <= bmat4x2 );
        bmat4x2(0,0) = 4.7f;
        bmat4x2(0,0) -= f_lit::delta * 0.5f;
        CHECK( amat4x2 >= bmat4x2 );
        // ...and a modification of exactly delta isn't
        bmat4x2(0,0) = 4.7f;
        bmat4x2(0,0) += f_lit::delta;
        bmat4x2(0,1) += f_lit::delta;
        bmat4x2(1,0) += f_lit::delta;
        bmat4x2(1,1) += f_lit::delta;
        bmat4x2(2,0) += f_lit::delta;
        bmat4x2(2,1) += f_lit::delta;
        bmat4x2(3,0) += f_lit::delta;
        bmat4x2(3,1) += f_lit::delta;
        CHECK( amat4x2 < bmat4x2 );
        bmat4x2 = amat4x2;
        bmat4x2(0,0) -= f_lit::delta;
        bmat4x2(0,1) -= f_lit::delta;
        bmat4x2(1,0) -= f_lit::delta;
        bmat4x2(1,1) -= f_lit::delta;
        bmat4x2(2,0) -= f_lit::delta;
        bmat4x2(2,1) -= f_lit::delta;
        bmat4x2(3,0) -= f_lit::delta;
        bmat4x2(3,1) -= f_lit::delta;
        CHECK( amat4x2 > bmat4x2 );
    }
    
    TEST( Mat4x2Addition )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f, 0.0f, -5.3f, 10.0f,
                        0.0f, 0.0f,  0.0f, 0.0f );
        mat4x2 bmat4x2( 0.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 18.0f, -2.0f );
        mat4x2 cmat4x2 = amat4x2 + bmat4x2;
        mat4x2 dmat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        CHECK_EQUAL( cmat4x2, dmat4x2 );
    }
    
    TEST( Mat4x2Subtraction )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f, 0.0f, -5.3f, 10.0f,
                        0.0f, 0.0f,  0.0f, 0.0f );
        mat4x2 bmat4x2( 0.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 18.0f, -2.0f );
        mat4x2 cmat4x2 = amat4x2 - bmat4x2;
        mat4x2 dmat4x2( 4.7f,   0.0f,  -5.3f, 10.0f,
                        0.0f,  -1.0f, -18.0f,  2.0f );
        CHECK_EQUAL( cmat4x2, dmat4x2 );
    }
    
    TEST( Mat4x2Negation )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        mat4x2 bmat4x2 = -amat4x2;
        mat4x2 cmat4x2( -4.7f,   0.0f,   5.3f, -10.0f,
                         0.0f,  -1.0f, -18.0f, 2.0f );
        CHECK_EQUAL( cmat4x2, bmat4x2 );
    }
    
    TEST( Mat4x2Mult2x4 )
    {
        using namespace gfx;
        mat4x2 amat4x2 ( 4.7f,  0.0f, -5.3f, 10.0f,
                         0.0f,  1.0f, 18.0f, -2.0f );
        mat2x4 amat2x4 (  1.0f, 0.0f,
                          0.0f, 1.0f,
                         10.0f, 5.0f,
                         1.5f, -1.0f );
        
        mat2 amat2 = amat4x2 * amat2x4;
        mat2 bmat2 ( -33.3f, -36.5,
                     177.0f, 93.0f );
        CHECK_EQUAL( bmat2, amat2 );
        
    }
    
    TEST( Mat4x2Mult3x4 )
    {
        using namespace gfx;
        mat4x2 amat4x2 ( 4.7f,  0.0f, -5.3f, 10.0f,
                         0.0f,  1.0f, 18.0f, -2.0f );
        mat3x4 amat3x4 (  1.0f, 0.0f,  5.0f,
                          0.0f, 1.0f,  7.0f,
                         10.0f, 5.0f,  0.0f,
                         1.5f, -1.0f, -2.0f );
        
        mat3x2 amat3x2 = amat4x2 * amat3x4;
        mat3x2 bmat3x2 ( -33.3f, -36.5, 3.5f,
                         177.0f, 93.0f, 11.0f );
        CHECK_EQUAL( bmat3x2, amat3x2 );
        
    }
    
    TEST( Mat4x2Mult4 )
    {
        using namespace gfx;
        mat4x2 amat4x2 ( 4.7f,  0.0f, -5.3f, 10.0f,
                         0.0f,  1.0f, 18.0f, -2.0f );
        mat4 amat4 (  1.0f, 0.0f,  5.0f, -6.0f,
                      0.0f, 1.0f,  7.0f, -3.0f,
                     10.0f, 5.0f,  0.0f,  8.0f,
                     1.5f, -1.0f, -2.0f, 11.0f );
        
        mat4x2 bmat4x2 = amat4x2 * amat4;
        mat4x2 cmat4x2 ( -33.3f, -36.5, 3.5f, 39.4f,
                         177.0f, 93.0f, 11.0f, 119.0f );
        CHECK_EQUAL( cmat4x2, bmat4x2 );
        
    }
    
    TEST( Mat4x2VectorPostMultiply )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        vec4 avec4 ( 1.0f, -1.0f, 0.0f, 10.0f );
        vec2 avec2 = amat4x2 * avec4;
        vec2 bvec2 ( 104.7f, -21.0f );
        CHECK_EQUAL( bvec2, avec2 );
    }
    
    TEST( Mat4x2VectorPreMultiply )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        vec2 avec2 ( 10.0f, 5.0f );
        vec4 avec4 = avec2 * amat4x2;
        vec4 bvec4 ( 47.0f, 5.0f, 37.0f, 90.0f );
        CHECK_EQUAL( bvec4, avec4 );
    }
    
    TEST( Mat4x2ScalarPostMultiply )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        float anum ( 2.0f );
        mat4x2 bmat4x2 = amat4x2 * anum;
        mat4x2 cmat4x2(  9.4f,  0.0f, -10.6f, 20.0f,
                         0.0f,  2.0f,  36.0f, -4.0f );
        CHECK_EQUAL( cmat4x2, bmat4x2 );
    }
    
    TEST( Mat4x2ScalarPreMultiply )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        float anum ( 2.0f );
        mat4x2 bmat4x2 = anum * amat4x2;
        mat4x2 cmat4x2(  9.4f,  0.0f, -10.6f, 20.0f,
                         0.0f,  2.0f,  36.0f, -4.0f );
        CHECK_EQUAL( cmat4x2, bmat4x2 );
    }
    
    TEST( Mat4x2ScalarPostDivide )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        float anum ( 2.0f );
        mat4x2 bmat4x2 = amat4x2 / anum;
        mat4x2 cmat4x2( 2.35f, 0.0f, -2.65f, 5.0f,
                        0.0f,  0.5f, 9.0f, -1.0f  );
        CHECK_EQUAL( cmat4x2, bmat4x2 );
    }
    
    TEST( Mat4x2Assignment )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        mat4x2 bmat4x2;
        bmat4x2 = amat4x2;
        CHECK_EQUAL( amat4x2, bmat4x2 );
    } 
    
    TEST( Mat4x2Lookup )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        CHECK_EQUAL( amat4x2(0,0),  4.7f );
        CHECK_EQUAL( amat4x2(0,1),  0.0f );
        CHECK_EQUAL( amat4x2(1,0),  0.0f );
        CHECK_EQUAL( amat4x2(1,1),  1.0f );
        CHECK_EQUAL( amat4x2(2,0), -5.3f );
        CHECK_EQUAL( amat4x2(2,1), 18.0f );
        CHECK_EQUAL( amat4x2(3,0), 10.0f );
        CHECK_EQUAL( amat4x2(3,1), -2.0f );
        
        vec2 avec2 ( 4.7f, 0.0f );
        CHECK_EQUAL( avec2, amat4x2[0] );
        avec2(y) = 10.0f;
        amat4x2[0] = avec2;
        CHECK_EQUAL( avec2, amat4x2[0] );
        avec2(x) = 2.0f;
        CHECK( avec2 != amat4x2[0] );
        amat4x2[0][0] = 2.0f;
        CHECK_EQUAL( avec2, amat4x2[0] );
    }
    
    TEST( Mat4x2ColumnLookup )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        CHECK_EQUAL( amat4x2(0,0),  4.7f );
        CHECK_EQUAL( amat4x2(0,1),  0.0f );
        CHECK_EQUAL( amat4x2(1,0),  0.0f );
        CHECK_EQUAL( amat4x2(1,1),  1.0f );
        CHECK_EQUAL( amat4x2(2,0), -5.3f );
        CHECK_EQUAL( amat4x2(2,1), 18.0f );
        CHECK_EQUAL( amat4x2(3,0), 10.0f );
        CHECK_EQUAL( amat4x2(3,1), -2.0f );
        
        vec2 avec2 ( 4.7f, 0.0f );
        CHECK_EQUAL( avec2, amat4x2.column(0) );
        avec2(y) = 10.0f;
        amat4x2.column(0) = avec2;
        CHECK_EQUAL( avec2, amat4x2.column(0) );
        avec2(x) = 2.0f;
        CHECK( avec2 != amat4x2.column(0) );
        amat4x2.column(0)[0] = 2.0f;
        CHECK_EQUAL( avec2, amat4x2.column(0) );
    }
    
    TEST( Mat4x2ColumnAssignment )
    {
        using namespace gfx;
        vec2 avec2( 4.7f, 0.0f );
        vec2 bvec2( 0.0f, 1.0f );
        vec2 cvec2( -5.3f, 18.0f );
        vec2 dvec2( 10.0f, -2.0f );
        mat4x2 amat4x2;
        amat4x2.columns( avec2, bvec2, cvec2, dvec2 );
        mat4x2 bmat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        CHECK_EQUAL( bmat4x2, amat4x2 );
    }
    
    TEST( Mat4x2FillAssignment )
    {
        using namespace gfx;
        mat4x2 amat4x2;
        amat4x2.fill( 2.0f );
        mat4x2 bmat4x2( 2.0f, 2.0f, 2.0f, 2.0f,
                        2.0f, 2.0f, 2.0f, 2.0f );
        CHECK_EQUAL( bmat4x2, amat4x2 );
    }
    
    TEST( Mat4x2RowLookup )
    {
        using namespace gfx;
        mat4x2 amat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        vec4 avec4( 4.7f, 0.0f, -5.3f, 10.0f );
        vec4 bvec4( 0.0f, 1.0f, 18.0f, -2.0f );

        CHECK_EQUAL( avec4, amat4x2.row(0) );
        CHECK_EQUAL( bvec4, amat4x2.row(1) );
        avec4(y) = 10.0f;
        amat4x2.row(0) = avec4;
        CHECK_EQUAL( avec4, amat4x2.row(0) );
        avec4(x) = 2.0f;
        CHECK( avec4 != amat4x2.row(0) );
        amat4x2.row(0)[0] = 2.0f;
        CHECK_EQUAL( avec4, amat4x2.row(0) );
    }
    
    TEST( Mat4x2RowAssignment )
    {
        using namespace gfx;
        vec4 avec4( 4.7f, 0.0f, -5.3f, 10.0f );
        vec4 bvec4( 0.0f, 1.0f, 18.0f, -2.0f );
        mat4x2 amat4x2;
        amat4x2.rows( avec4, bvec4 );
        mat4x2 bmat4x2( 4.7f,  0.0f, -5.3f, 10.0f,
                        0.0f,  1.0f, 18.0f, -2.0f );
        CHECK_EQUAL( bmat4x2, amat4x2 );
    }
}





SUITE( Matrix3x4 )
{
    TEST( Mat3x4Construction )
    {
        using namespace gfx;
        mat3x4 amat3x4;
        CHECK_EQUAL( 0.0f, amat3x4(0,0) );
        CHECK_EQUAL( 0.0f, amat3x4(0,1) );
        CHECK_EQUAL( 0.0f, amat3x4(0,2) );
        CHECK_EQUAL( 0.0f, amat3x4(0,3) );
        
        CHECK_EQUAL( 0.0f, amat3x4(1,0) );
        CHECK_EQUAL( 0.0f, amat3x4(1,1) );
        CHECK_EQUAL( 0.0f, amat3x4(1,2) );
        CHECK_EQUAL( 0.0f, amat3x4(1,3) );
        
        CHECK_EQUAL( 0.0f, amat3x4(2,0) );
        CHECK_EQUAL( 0.0f, amat3x4(2,1) );
        CHECK_EQUAL( 0.0f, amat3x4(2,2) );
        CHECK_EQUAL( 0.0f, amat3x4(2,3) );
        
        CHECK_EQUAL( amat3x4.n_cols, 3u );
        CHECK_EQUAL( amat3x4.n_rows, 4u );
        CHECK_EQUAL( amat3x4.n_comp, 12u );
    }
    
    TEST( Mat3x4CopyConstruction )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        mat3x4 bmat3x4 = amat3x4;
        CHECK_EQUAL( amat3x4, bmat3x4 );
        bmat3x4(2,1) = -15.0f;
        // No side effects
        CHECK( amat3x4(2,1) != bmat3x4(2,1) );
    }
    
    TEST( Mat3x4ExplicitConstruction )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        mat3x4 bmat3x4;
        bmat3x4(0,0) =  4.7f;    bmat3x4(1,0) =  0.0f;    bmat3x4(2,0) =   2.0f;
        bmat3x4(0,1) =  0.0f;    bmat3x4(1,1) =  1.0f;    bmat3x4(2,1) =   5.0f;
        bmat3x4(0,2) = -5.3f;    bmat3x4(1,2) = 18.0f;    bmat3x4(2,2) =  -3.0f;
        bmat3x4(0,3) = 10.0f;    bmat3x4(1,3) = -2.0f;    bmat3x4(2,3) =   1.0f;
        CHECK_EQUAL( bmat3x4, amat3x4 );
    }
    
    TEST( Mat3x4FillConstruction )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f );
        mat3x4 bmat3x4;
        bmat3x4(0,0) = 4.7f;    bmat3x4(1,0) = 4.7f;    bmat3x4(2,0) = 4.7f;
        bmat3x4(0,1) = 4.7f;    bmat3x4(1,1) = 4.7f;    bmat3x4(2,1) = 4.7f;
        bmat3x4(0,2) = 4.7f;    bmat3x4(1,2) = 4.7f;    bmat3x4(2,2) = 4.7f;
        bmat3x4(0,3) = 4.7f;    bmat3x4(1,3) = 4.7f;    bmat3x4(2,3) = 4.7f;
        CHECK_EQUAL( bmat3x4, amat3x4 );
    }
    
    TEST( Mat3x4ColumnConstruction )
    {
        using namespace gfx;
        vec4 col0 ( 4.7f, 0.0f, -5.3f, 10.0f );
        vec4 col1 ( 0.0f, 1.0f, 18.0f, -2.0f );
        vec4 col2 ( 2.0f, 5.0f, -3.0f, 1.0f );
        mat3x4 amat3x4( col0, col1, col2 );
        mat3x4 bmat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        CHECK_EQUAL( bmat3x4, amat3x4 );
    }
    
    TEST( Mat3x4UpperIdentity )
    {
        using namespace gfx;
        mat3x4 amat3x4 = mat3x4::upper_identity();
        mat3x4 bmat3x4( 1.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 0.0f );
        CHECK_EQUAL( bmat3x4, amat3x4 );
    }
    
    TEST( Mat3x4RowConstruction )
    {
        using namespace gfx;
        vec3 row0 (  4.7f,  0.0f,  2.0f );
        vec3 row1 (  0.0f,  1.0f,  5.0f );
        vec3 row2 ( -5.3f, 18.0f, -3.0f );
        vec3 row3 ( 10.0f, -2.0f,  1.0f );
        mat3x4 amat3x4 =  mat3x4::row_vectors( row0, row1, row2, row3 );
        mat3x4 bmat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        CHECK_EQUAL( bmat3x4, amat3x4 );
    }
    
    TEST( Mat3x4FuzzyEquality )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        mat3x4 bmat3x4 = amat3x4;
        CHECK_EQUAL( amat3x4, bmat3x4 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat3x4(0,0) += f_lit::delta * 0.5f;
        CHECK_EQUAL( amat3x4, bmat3x4 );
        // ...and a modification of exactly delta isn't...
        bmat3x4(1,0) = f_lit::delta;
        CHECK( amat3x4 != bmat3x4 );
        // ...and that a modification greater than
        // delta is not
        bmat3x4(1,0) = 0.0f;
        bmat3x4(1,0) += std::nextafter(f_lit::delta, 1.0f);
        CHECK( amat3x4 != bmat3x4 );
    }
    
    TEST( Mat3x4Inequality )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        mat3x4 bmat3x4 = amat3x4;
        CHECK_EQUAL( amat3x4, bmat3x4 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat3x4(0,0) += f_lit::delta * 0.5f;
        CHECK( false == ( amat3x4 < bmat3x4 ) );
        bmat3x4(0,0) = 4.7f;
        bmat3x4(0,0) -= f_lit::delta * 0.5f;
        CHECK( false == ( amat3x4 > bmat3x4 ) );
        // ...and a modification of exactly delta isn't
        bmat3x4(0,0) = 4.7f;
        bmat3x4(0,0) += f_lit::delta;
        bmat3x4(0,1) += f_lit::delta;
        bmat3x4(0,2) += f_lit::delta;
        bmat3x4(0,3) += f_lit::delta;
        
        bmat3x4(1,0) += f_lit::delta;
        bmat3x4(1,1) += f_lit::delta;
        bmat3x4(1,2) += f_lit::delta;
        bmat3x4(1,3) += f_lit::delta;
        
        bmat3x4(2,0) += f_lit::delta;
        bmat3x4(2,1) += f_lit::delta;
        bmat3x4(2,2) += f_lit::delta;
        bmat3x4(2,3) += f_lit::delta;
        
        CHECK( amat3x4 < bmat3x4 );
        bmat3x4 = amat3x4;
        bmat3x4(0,0) -= f_lit::delta;
        bmat3x4(0,1) -= f_lit::delta;
        bmat3x4(0,2) -= f_lit::delta;
        bmat3x4(0,3) -= f_lit::delta;
        
        bmat3x4(1,0) -= f_lit::delta;
        bmat3x4(1,1) -= f_lit::delta;
        bmat3x4(1,2) -= f_lit::delta;
        bmat3x4(1,3) -= f_lit::delta;
        
        bmat3x4(2,0) -= f_lit::delta;
        bmat3x4(2,1) -= f_lit::delta;
        bmat3x4(2,2) -= f_lit::delta;
        bmat3x4(2,3) -= f_lit::delta;
        CHECK( amat3x4 > bmat3x4 );
    }
    
    TEST( Mat3x4InequalityEquality ) // LOL, wot?
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        mat3x4 bmat3x4 = amat3x4;
        CHECK_EQUAL( amat3x4, bmat3x4 );
        CHECK( amat3x4 <= bmat3x4 );
        CHECK( amat3x4 >= bmat3x4 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat3x4(0,0) += f_lit::delta * 0.5f;
        CHECK(  amat3x4 <= bmat3x4 );
        bmat3x4(0,0) = 4.7f;
        bmat3x4(0,0) -= f_lit::delta * 0.5f;
        CHECK( amat3x4 >= bmat3x4 );
        // ...and a modification of exactly delta isn't
        bmat3x4(0,0) = 4.7f;
        bmat3x4(0,0) += f_lit::delta;
        bmat3x4(0,1) += f_lit::delta;
        bmat3x4(0,2) += f_lit::delta;
        bmat3x4(0,3) += f_lit::delta;
        
        bmat3x4(1,0) += f_lit::delta;
        bmat3x4(1,1) += f_lit::delta;
        bmat3x4(1,2) += f_lit::delta;
        bmat3x4(1,3) += f_lit::delta;
        
        bmat3x4(2,0) += f_lit::delta;
        bmat3x4(2,1) += f_lit::delta;
        bmat3x4(2,2) += f_lit::delta;
        bmat3x4(2,3) += f_lit::delta;
        CHECK( amat3x4 < bmat3x4 );
        bmat3x4 = amat3x4;
        bmat3x4(0,0) -= f_lit::delta;
        bmat3x4(0,1) -= f_lit::delta;
        bmat3x4(0,2) -= f_lit::delta;
        bmat3x4(0,3) -= f_lit::delta;
        
        bmat3x4(1,0) -= f_lit::delta;
        bmat3x4(1,1) -= f_lit::delta;
        bmat3x4(1,2) -= f_lit::delta;
        bmat3x4(1,3) -= f_lit::delta;
        
        bmat3x4(2,0) -= f_lit::delta;
        bmat3x4(2,1) -= f_lit::delta;
        bmat3x4(2,2) -= f_lit::delta;
        bmat3x4(2,3) -= f_lit::delta;
        CHECK( amat3x4 > bmat3x4 );
    }
    
    TEST( Mat3x4Addition )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f, 0.0f,  2.0f,
                        0.0f, 0.0f,  0.0f,
                       -5.3f, 0.0f, -3.0f,
                       10.0f, 0.0f,  0.0f );
        mat3x4 bmat3x4( 0.0f,  0.0f, 0.0f,
                        0.0f,  1.0f, 5.0f,
                        0.0f, 18.0f, 0.0f,
                        0.0f, -2.0f, 1.0f );
        mat3x4 cmat3x4 = amat3x4 + bmat3x4;
        mat3x4 dmat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        CHECK_EQUAL( cmat3x4, dmat3x4 );
    }
    
    TEST( Mat3x4Subtraction )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f, 0.0f,  2.0f,
                        0.0f, 0.0f,  0.0f,
                       -5.3f, 0.0f, -3.0f,
                       10.0f, 0.0f,  0.0f );
        mat3x4 bmat3x4( 0.0f,  0.0f, 0.0f,
                        0.0f,  1.0f, 5.0f,
                        0.0f, 18.0f, 0.0f,
                        0.0f, -2.0f, 1.0f );
        mat3x4 cmat3x4 = amat3x4 - bmat3x4;
        mat3x4 dmat3x4( 4.7f,   0.0f,  2.0f,
                        0.0f,  -1.0f, -5.0f,
                       -5.3f, -18.0f, -3.0f,
                       10.0f,   2.0f, -1.0f );
        CHECK_EQUAL( cmat3x4, dmat3x4 );
    }
    
    TEST( Mat3x4Negation )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        mat3x4 bmat3x4 = -amat3x4;
        mat3x4 cmat3x4( -4.7f,   0.0f, -2.0f,
                         0.0f,  -1.0f, -5.0f,
                         5.3f, -18.0f,  3.0f,
                       -10.0f,   2.0f, -1.0f );
        CHECK_EQUAL( cmat3x4, bmat3x4 );
    }
    
    TEST( Mat3x4Mult4x3 )
    {
        using namespace gfx;
        mat4x3 amat4x3 ( 4.7f,  0.0f,  2.0f, 10.0f,
                         0.0f,  1.0f,  5.0f, -2.0f,
                        -5.3f, 18.0f, -3.0f,  1.0f );
        mat3x4 amat3x4 ( 4.7f,  0.0f,  2.0f,
                         0.0f,  1.0f,  5.0f,
                        -5.3f, 18.0f, -3.0f,
                        10.0f, -2.0f,  1.0f );
        
        mat4 amat4 = amat3x4 * amat4x3;
        mat4 bmat4 (  11.49f, 36.0f,   3.4f,  49.0f,
                     -26.5f,  91.0f, -10.0f,   3.0f,
                     -9.01f, -36.0f,  88.4f, -92.0f,
                      41.7f,  16.0f,   7.0f, 105.0f );
        
        CHECK_EQUAL( bmat4, amat4 );
    }
    
    TEST( Mat3x4Mult2x3 )
    {
        using namespace gfx;
        mat2x3 amat2x3 ( 4.7f,  0.0f,
                         0.0f,  1.0f,
                        -5.3f, 18.0f );
        mat3x4 amat3x4 ( 4.7f,  0.0f,  2.0f,
                         0.0f,  1.0f,  5.0f,
                        -5.3f, 18.0f, -3.0f,
                        10.0f, -2.0f,  1.0f );
        
        mat2x4 amat2x4 = amat3x4 * amat2x3;
        mat2x4 bmat2x4 (  11.49f, 36.0f,
                         -26.5f,  91.0f,
                         -9.01f, -36.0f,
                          41.7f,  16.0f );
        
        CHECK_EQUAL( bmat2x4, amat2x4 );
    }
    
    TEST( Mat3x4Mult3 )
    {
        using namespace gfx;
        mat3 amat3 = mat3::identity();
        mat3x4 amat3x4 ( 4.7f,  0.0f,  2.0f,
                         0.0f,  1.0f,  5.0f,
                        -5.3f, 18.0f, -3.0f,
                        10.0f, -2.0f,  1.0f );
        
        mat3x4 bmat3x4 = amat3x4 * amat3;
        
        CHECK_EQUAL( amat3x4, bmat3x4 );
    }
    
    TEST( Mat3x4VectorPostMultiply )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        vec3 avec3 ( 1.0f, -1.0f, 5.0f );
        vec4 avec4 = amat3x4 * avec3;
        vec4 bvec4 ( 14.7f, 24.0f, -38.3f, 17.0f );
        CHECK_EQUAL( bvec4, avec4 );
    }
    
    TEST( Mat3x4VectorPreMultiply )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        vec4 avec4 ( 1.0f, -1.0f, 0.0f, 10.0f );
        vec3 avec3 = avec4 * amat3x4;
        vec3 bvec3 ( 104.7f, -21.0f, 7.0f );
        CHECK_EQUAL( bvec3, avec3 );
    }
    
    TEST( Mat3x4ScalarPostMultiply )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        float anum ( 2.0f );
        mat3x4 bmat3x4 = amat3x4 * anum;
        mat3x4 cmat3x4(  9.4f,  0.0f, 4.0f,
                         0.0f,  2.0f, 10.0f,
                       -10.6f, 36.0f, -6.0f,
                        20.0f, -4.0f, 2.0f );
        CHECK_EQUAL( cmat3x4, bmat3x4 );
    }
    
    TEST( Mat3x4ScalarPreMultiply )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        float anum ( 2.0f );
        mat3x4 bmat3x4 = anum * amat3x4;
        mat3x4 cmat3x4(  9.4f,  0.0f, 4.0f,
                         0.0f,  2.0f, 10.0f,
                       -10.6f, 36.0f, -6.0f,
                        20.0f, -4.0f, 2.0f );
        CHECK_EQUAL( cmat3x4, bmat3x4 );
    }
    
    TEST( Mat3x4ScalarPostDivide )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        float anum ( 2.0f );
        mat3x4 bmat3x4 = amat3x4 / anum;
        mat3x4 cmat3x4( 2.35f, 0.0f, 1.0f,
                        0.0f,  0.5f, 2.5f,
                       -2.65f, 9.0f, -1.5f,
                        5.0f, -1.0f, 0.5f );
        CHECK_EQUAL( cmat3x4, bmat3x4 );
    }
    
    TEST( Mat3x4Assignment )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        mat3x4 bmat3x4;
        bmat3x4 = amat3x4;
        CHECK_EQUAL( amat3x4, bmat3x4 );
    }
    
    TEST( Mat3x4Lookup )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        CHECK_EQUAL(  4.7f, amat3x4(0,0) );
        CHECK_EQUAL(  0.0f, amat3x4(0,1) );
        CHECK_EQUAL( -5.3f, amat3x4(0,2) );
        CHECK_EQUAL( 10.0f, amat3x4(0,3) );
        
        CHECK_EQUAL(  0.0f, amat3x4(1,0) );
        CHECK_EQUAL(  1.0f, amat3x4(1,1) );
        CHECK_EQUAL( 18.0f, amat3x4(1,2) );
        CHECK_EQUAL( -2.0f, amat3x4(1,3) );
        
        CHECK_EQUAL(  2.0f, amat3x4(2,0) );
        CHECK_EQUAL(  5.0f, amat3x4(2,1) );
        CHECK_EQUAL( -3.0f, amat3x4(2,2) );
        CHECK_EQUAL(  1.0f, amat3x4(2,3) );
        
        vec4 avec4 ( 0.0f, 1.0f, 18.0f, -2.0f );
        CHECK_EQUAL( avec4, amat3x4[1] );
        avec4(y) = 10.0f;
        amat3x4[1] = avec4;
        CHECK_EQUAL( avec4, amat3x4[1] );
        avec4(x) = 2.0f;
        CHECK( avec4 != amat3x4[1] );
        amat3x4[1][0] = 2.0f;
        CHECK_EQUAL( avec4, amat3x4[1] );
    }
    
    TEST( Mat3x4ColumnLookup )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        CHECK_EQUAL(  4.7f, amat3x4(0,0) );
        CHECK_EQUAL(  0.0f, amat3x4(0,1) );
        CHECK_EQUAL( -5.3f, amat3x4(0,2) );
        CHECK_EQUAL( 10.0f, amat3x4(0,3) );
        
        CHECK_EQUAL(  0.0f, amat3x4(1,0) );
        CHECK_EQUAL(  1.0f, amat3x4(1,1) );
        CHECK_EQUAL( 18.0f, amat3x4(1,2) );
        CHECK_EQUAL( -2.0f, amat3x4(1,3) );
        
        CHECK_EQUAL(  2.0f, amat3x4(2,0) );
        CHECK_EQUAL(  5.0f, amat3x4(2,1) );
        CHECK_EQUAL( -3.0f, amat3x4(2,2) );
        CHECK_EQUAL(  1.0f, amat3x4(2,3) );
        
        vec4 avec4 ( 0.0f, 1.0f, 18.0f, -2.0f );
        CHECK_EQUAL( avec4, amat3x4.column(1) );
        avec4(y) = 10.0f;
        amat3x4.column(1) = avec4;
        CHECK_EQUAL( avec4, amat3x4.column(1) );
        avec4(x) = 2.0f;
        CHECK( avec4 != amat3x4.column(1) );
        amat3x4.column(1)[0] = 2.0f;
        CHECK_EQUAL( avec4, amat3x4.column(1) );
    }
    
    TEST( Mat3x4ColumnAssignment )
    {
        using namespace gfx;
        vec4 avec4( 4.7f, 0.0f, -5.3f, 10.0f );
        vec4 bvec4( 0.0f, 1.0f, 18.0f, -2.0f );
        vec4 cvec4( 2.0f, 5.0f, -3.0f,  1.0f );
        mat3x4 amat3x4;
        amat3x4.columns( avec4, bvec4, cvec4 );
        mat3x4 bmat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        CHECK_EQUAL( bmat3x4, amat3x4 );
    }
    
    TEST( Mat3x4FillAssignment )
    {
        using namespace gfx;
        mat3x4 amat3x4;
        amat3x4.fill( 2.0f );
        mat3x4 bmat3x4( 2.0f, 2.0f, 2.0f,
                        2.0f, 2.0f, 2.0f,
                        2.0f, 2.0f, 2.0f,
                        2.0f, 2.0f, 2.0f );
        CHECK_EQUAL( bmat3x4, amat3x4 );
    }
    
    TEST( Mat3x4RowLookup )
    {
        using namespace gfx;
        mat3x4 amat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        vec3 avec3( 4.7f, 0.0f, 2.0f );
        vec3 bvec3( 0.0f, 1.0f, 5.0f );
        vec3 cvec3( -5.3f, 18.0f, -3.0f );
        vec3 dvec3( 10.0f, -2.0f, 1.0f );

        CHECK_EQUAL( avec3, amat3x4.row(0) );
        CHECK_EQUAL( bvec3, amat3x4.row(1) );
        CHECK_EQUAL( cvec3, amat3x4.row(2) );
        CHECK_EQUAL( dvec3, amat3x4.row(3) );
        avec3(y) = 10.0f;
        amat3x4.row(0) = avec3;
        CHECK_EQUAL( avec3, amat3x4.row(0) );
        avec3(x) = 2.0f;
        CHECK( avec3 != amat3x4.row(0) );
        amat3x4.row(0)[0] = 2.0f;
        CHECK_EQUAL( avec3, amat3x4.row(0) );
    }
    
    TEST( Mat3x4RowAssignment )
    {
        using namespace gfx;
        vec3 avec3( 4.7f, 0.0f, 2.0f );
        vec3 bvec3( 0.0f, 1.0f, 5.0f );
        vec3 cvec3( -5.3f, 18.0f, -3.0f );
        vec3 dvec3( 10.0f, -2.0f, 1.0f );
        mat3x4 amat3x4;
        amat3x4.rows( avec3, bvec3, cvec3, dvec3 );
        mat3x4 bmat3x4( 4.7f,  0.0f,  2.0f,
                        0.0f,  1.0f,  5.0f,
                       -5.3f, 18.0f, -3.0f,
                       10.0f, -2.0f,  1.0f );
        CHECK_EQUAL( bmat3x4, amat3x4 );
    }
}





SUITE( Matrix4x3 )
{
    TEST( Mat4x3Construction )
    {
        using namespace gfx;
        mat4x3 amat4x3;
        CHECK_EQUAL( 0.0f, amat4x3(0,0) );
        CHECK_EQUAL( 0.0f, amat4x3(0,1) );
        CHECK_EQUAL( 0.0f, amat4x3(0,2) );
        
        CHECK_EQUAL( 0.0f, amat4x3(1,0) );
        CHECK_EQUAL( 0.0f, amat4x3(1,1) );
        CHECK_EQUAL( 0.0f, amat4x3(1,2) );
        
        CHECK_EQUAL( 0.0f, amat4x3(2,0) );
        CHECK_EQUAL( 0.0f, amat4x3(2,1) );
        CHECK_EQUAL( 0.0f, amat4x3(2,2) );
        
        CHECK_EQUAL( 0.0f, amat4x3(3,0) );
        CHECK_EQUAL( 0.0f, amat4x3(3,1) );
        CHECK_EQUAL( 0.0f, amat4x3(3,2) );
        
        CHECK_EQUAL( amat4x3.n_cols, 4u );
        CHECK_EQUAL( amat4x3.n_rows, 3u );
        CHECK_EQUAL( amat4x3.n_comp, 12u );
    }
    
    TEST( Mat4x3CopyConstruction )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        mat4x3 bmat4x3 = amat4x3;
        CHECK_EQUAL( amat4x3, bmat4x3 );
        bmat4x3(0,0) = -15.0f;
        // No side effects
        CHECK( amat4x3(0,0) != bmat4x3(0,0) );
    }
    
    TEST( Mat4x3ExplicitConstruction )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        mat4x3 bmat4x3;
        bmat4x3(0,0) =  4.7f;
        bmat4x3(0,1) =  0.0f;
        bmat4x3(0,2) = -5.3f;
        
        bmat4x3(1,0) =  0.0f;
        bmat4x3(1,1) =  1.0f;
        bmat4x3(1,2) = 18.0f;
        
        bmat4x3(2,0) = 10.0f;
        bmat4x3(2,1) = -3.0f;
        bmat4x3(2,2) =  0.0f;
        
        bmat4x3(3,0) = 1.0f;
        bmat4x3(3,1) = 5.0f;
        bmat4x3(3,2) = 8.5f;
        CHECK_EQUAL( bmat4x3, amat4x3 );
    }
    
    TEST( Mat4x3FillConstruction )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f );
        mat4x3 bmat4x3;
        bmat4x3(0,0) = 4.7f;
        bmat4x3(0,1) = 4.7f;
        bmat4x3(0,2) = 4.7f;
        
        bmat4x3(1,0) = 4.7f;
        bmat4x3(1,1) = 4.7f;
        bmat4x3(1,2) = 4.7f;
        
        bmat4x3(2,0) = 4.7f;
        bmat4x3(2,1) = 4.7f;
        bmat4x3(2,2) = 4.7f;
        
        bmat4x3(3,0) = 4.7f;
        bmat4x3(3,1) = 4.7f;
        bmat4x3(3,2) = 4.7f;
        
        CHECK_EQUAL( bmat4x3, amat4x3 );
    }
    
    TEST( Mat4x3ColumnConstruction )
    {
        using namespace gfx;
        vec3 col0 (  4.7f,  0.0f, -5.3f );
        vec3 col1 (  0.0f,  1.0f, 18.0f );
        vec3 col2 ( 10.0f, -3.0f,  0.0f );
        vec3 col3 (  1.0f,  5.0f,  8.5f );
        mat4x3 amat4x3( col0, col1, col2, col3 );
        mat4x3 bmat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        CHECK_EQUAL( bmat4x3, amat4x3 );
    }
    
    TEST( Mat4x3LeftIdentity )
    {
        using namespace gfx;
        mat4x3 amat4x3 = mat4x3::left_identity();
        mat4x3 bmat4x3( 1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f );
        CHECK_EQUAL( bmat4x3, amat4x3 );
    }
    
    TEST( Mat4x3RowConstruction )
    {
        using namespace gfx;
        vec4 row0 (  4.7f,  0.0f, 10.0f, 1.0f );
        vec4 row1 (  0.0f,  1.0f, -3.0f, 5.0f );
        vec4 row2 ( -5.3f, 18.0f, 0.0f, 8.5f );
        mat4x3 amat4x3 =  mat4x3::row_vectors( row0, row1, row2 );
        mat4x3 bmat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        CHECK_EQUAL( bmat4x3, amat4x3 );
    }
    
    TEST( Mat4x3FuzzyEquality )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        mat4x3 bmat4x3 = amat4x3;
        CHECK_EQUAL( amat4x3, bmat4x3 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat4x3(0,0) += f_lit::delta * 0.5f;
        CHECK_EQUAL( amat4x3, bmat4x3 );
        // ...and a modification of exactly delta isn't...
        bmat4x3(1,0) = f_lit::delta;
        CHECK( amat4x3 != bmat4x3 );
        // ...and that a modification greater than
        // delta is not
        bmat4x3(1,0) = 0.0f;
        bmat4x3(1,0) += std::nextafter(f_lit::delta, 1.0f);
        CHECK( amat4x3 != bmat4x3 );
    }
    
    TEST( Mat4x3Inequality )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        mat4x3 bmat4x3 = amat4x3;
        CHECK_EQUAL( amat4x3, bmat4x3 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat4x3(0,0) += f_lit::delta * 0.5f;
        CHECK( false == ( amat4x3 < bmat4x3 ) );
        bmat4x3(0,0) = 4.7f;
        bmat4x3(0,0) -= f_lit::delta * 0.5f;
        CHECK( false == ( amat4x3 > bmat4x3 ) );
        // ...and a modification of exactly delta isn't
        bmat4x3(0,0) = 4.7f;
        bmat4x3(0,0) += f_lit::delta;
        bmat4x3(0,1) += f_lit::delta;
        bmat4x3(0,2) += f_lit::delta;
        
        bmat4x3(1,0) += f_lit::delta;
        bmat4x3(1,1) += f_lit::delta;
        bmat4x3(1,2) += f_lit::delta;
        
        bmat4x3(2,0) += f_lit::delta;
        bmat4x3(2,1) += f_lit::delta;
        bmat4x3(2,2) += f_lit::delta;
        
        bmat4x3(3,0) += f_lit::delta;
        bmat4x3(3,1) += f_lit::delta;
        bmat4x3(3,2) += f_lit::delta;
        
        CHECK( amat4x3 < bmat4x3 );
        bmat4x3 = amat4x3;
        bmat4x3(0,0) -= f_lit::delta;
        bmat4x3(0,1) -= f_lit::delta;
        bmat4x3(0,2) -= f_lit::delta;
        
        bmat4x3(1,0) -= f_lit::delta;
        bmat4x3(1,1) -= f_lit::delta;
        bmat4x3(1,2) -= f_lit::delta;
        
        bmat4x3(2,0) -= f_lit::delta;
        bmat4x3(2,1) -= f_lit::delta;
        bmat4x3(2,2) -= f_lit::delta;
        
        bmat4x3(3,0) -= f_lit::delta;
        bmat4x3(3,1) -= f_lit::delta;
        bmat4x3(3,2) -= f_lit::delta;
        
        CHECK( amat4x3 > bmat4x3 );
    }
    
    TEST( Mat4x3InequalityEquality ) // LOL, wot?
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        mat4x3 bmat4x3 = amat4x3;
        CHECK_EQUAL( amat4x3, bmat4x3 );
        CHECK( amat4x3 <= bmat4x3 );
        CHECK( amat4x3 >= bmat4x3 );
        // Make sure that a modification less than
        // the defined delta is still equal...
        bmat4x3(0,0) += f_lit::delta * 0.5f;
        CHECK(  amat4x3 <= bmat4x3 );
        bmat4x3(0,0) = 4.7f;
        bmat4x3(0,0) -= f_lit::delta * 0.5f;
        CHECK( amat4x3 >= bmat4x3 );
        // ...and a modification of exactly delta isn't
        bmat4x3(0,0) = 4.7f;
        bmat4x3(0,0) += f_lit::delta;
        bmat4x3(0,1) += f_lit::delta;
        bmat4x3(0,2) += f_lit::delta;
        
        bmat4x3(1,0) += f_lit::delta;
        bmat4x3(1,1) += f_lit::delta;
        bmat4x3(1,2) += f_lit::delta;
        
        bmat4x3(2,0) += f_lit::delta;
        bmat4x3(2,1) += f_lit::delta;
        bmat4x3(2,2) += f_lit::delta;
        
        bmat4x3(3,0) += f_lit::delta;
        bmat4x3(3,1) += f_lit::delta;
        bmat4x3(3,2) += f_lit::delta;
        
        CHECK( amat4x3 < bmat4x3 );
        bmat4x3 = amat4x3;
        
        bmat4x3(0,0) -= f_lit::delta;
        bmat4x3(0,1) -= f_lit::delta;
        bmat4x3(0,2) -= f_lit::delta;
        
        bmat4x3(1,0) -= f_lit::delta;
        bmat4x3(1,1) -= f_lit::delta;
        bmat4x3(1,2) -= f_lit::delta;
        
        bmat4x3(2,0) -= f_lit::delta;
        bmat4x3(2,1) -= f_lit::delta;
        bmat4x3(2,2) -= f_lit::delta;
        
        bmat4x3(3,0) -= f_lit::delta;
        bmat4x3(3,1) -= f_lit::delta;
        bmat4x3(3,2) -= f_lit::delta;
        
        CHECK( amat4x3 > bmat4x3 );
    }
    
    TEST( Mat4x3Addition )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f, 0.0f, 10.0f, 0.0f,
                        0.0f, 0.0f, -3.0f, 0.0f,
                       -5.3f, 0.0f,  0.0f, 0.0f );
        mat4x3 bmat4x3( 0.0f,  0.0f, 0.0f, 1.0f,
                        0.0f,  1.0f, 0.0f, 5.0f,
                        0.0f, 18.0f, 0.0f, 8.5f );
        mat4x3 cmat4x3 = amat4x3 + bmat4x3;
        mat4x3 dmat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        CHECK_EQUAL( cmat4x3, dmat4x3 );
    }
    
    TEST( Mat4x3Subtraction )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f, 0.0f, 10.0f, 1.0f,
                        0.0f, 0.0f,  0.0f, 0.0f,
                       -5.3f, 0.0f,  0.0f, 8.5f );
        mat4x3 bmat4x3( 0.0f,  0.0f,  0.0f, 0.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                        0.0f, 18.0f,  0.0f, 0.0f );
        mat4x3 cmat4x3 = amat4x3 - bmat4x3;
        mat4x3 dmat4x3( 4.7f,   0.0f, 10.0f, 1.0f,
                        0.0f,  -1.0f, 3.0f, -5.0f,
                       -5.3f, -18.0f,  0.0f, 8.5f );
        CHECK_EQUAL( cmat4x3, dmat4x3 );
    }
    
    TEST( Mat4x3Negation )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        mat4x3 bmat4x3 = -amat4x3;
        mat4x3 cmat4x3( -4.7f,  0.0f, -10.0f, -1.0f,
                         0.0f,  -1.0f,  3.0f, -5.0f,
                         5.3f, -18.0f,  0.0f, -8.5f );
        CHECK_EQUAL( cmat4x3, bmat4x3 );
    }
    
    TEST( Mat4x3Mult3x4 )
    {
        using namespace gfx;
        mat3x4 amat3x4 ( 4.7f,  0.0f, -5.3f,
                         0.0f,  1.0f, 18.0f,
                         5.0f, 7.0f, -2.0f,
                         -1.0f, 11.0f, 10.0f );
        mat4x3 amat4x3 ( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        
        mat3 amat3 = amat4x3 * amat3x4;
        mat3 bmat3 (  71.09f, 81.0f, -34.91f,
                      -20.0f, 35.0f, 74.0f,
                     -33.41f, 111.5f, 437.09f );
        CHECK_EQUAL( bmat3, amat3 );
        
    }
    
    TEST( Mat4x3Mult2x4 )
    {
        using namespace gfx;
        mat2x4 amat2x4 ( 4.7f,  0.0f,
                         0.0f,  1.0f,
                         5.0f, 7.0f,
                         -1.0f, 11.0f );
        mat4x3 amat4x3 ( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        
        mat2x3 amat2x3 = amat4x3 * amat2x4;
        mat2x3 bmat2x3 (  71.09f, 81.0f,
                       -20.0f, 35.0f,
                       -33.41f, 111.5f );
        CHECK_EQUAL( bmat2x3, amat2x3 );
        
    }
    
    TEST( Mat4x3Mult4 )
    {
        using namespace gfx;
        mat4 amat4 = mat4::identity();
        mat4x3 amat4x3 ( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        
        mat4x3 bmat4x3 = amat4x3 * amat4;
        
        CHECK_EQUAL( amat4x3, bmat4x3 );
        
    }
    
    TEST( Mat4x3VectorPostMultiply )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        vec4 avec4 ( 4.7f, 0.0f, 5.0f, -1.0f );
        vec3 avec3 = amat4x3 * avec4;
        vec3 bvec3 ( 71.09f, -20.0f, -33.41f );
        CHECK_EQUAL( bvec3, avec3 );
    }
    
    TEST( Mat4x3VectorPreMultiply )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        vec3 avec3 ( 1.0f, -1.0f, 0.0f );
        vec4 avec4 = avec3 * amat4x3;
        vec4 bvec4 ( 4.7f, -1.0f, 13.0f, -4.0f );
        CHECK_EQUAL( bvec4, avec4 );
    }
    
    TEST( Mat4x3ScalarPostMultiply )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        float anum ( 2.0f );
        mat4x3 bmat4x3 = amat4x3 * anum;
        mat4x3 cmat4x3(  9.4f,  0.0f, 20.0f, 2.0f,
                         0.0f,  2.0f, -6.0f, 10.0f,
                         -10.6f, 36.0f, 0.0f, 17.0f );
        CHECK_EQUAL( cmat4x3, bmat4x3 );
    }
    
    TEST( Mat4x3ScalarPreMultiply )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        float anum ( 2.0f );
        mat4x3 bmat4x3 = anum * amat4x3;
        mat4x3 cmat4x3(  9.4f,  0.0f, 20.0f, 2.0f,
                         0.0f,  2.0f, -6.0f, 10.0f,
                         -10.6f, 36.0f, 0.0f, 17.0f );
        CHECK_EQUAL( cmat4x3, bmat4x3 );
    }
    
    TEST( Mat4x3ScalarPostDivide )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        float anum ( 2.0f );
        mat4x3 bmat4x3 = amat4x3 / anum;
        mat4x3 cmat4x3( 2.35f, 0.0f, 5.0f, 0.5f,
                        0.0f,  0.5f, -1.5f, 2.5f,
                       -2.65f, 9.0f, 0.0f, 4.25f );
        CHECK_EQUAL( cmat4x3, bmat4x3 );
    }
    
    TEST( Mat4x3Assignment )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        mat4x3 bmat4x3;
        bmat4x3 = amat4x3;
        CHECK_EQUAL( amat4x3, bmat4x3 );
    }
    
    TEST( Mat4x3Lookup )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        CHECK_EQUAL( amat4x3(0,0),  4.7f );
        CHECK_EQUAL( amat4x3(0,1),  0.0f );
        CHECK_EQUAL( amat4x3(0,2), -5.3f );
        
        CHECK_EQUAL( amat4x3(1,0),  0.0f );
        CHECK_EQUAL( amat4x3(1,1),  1.0f );
        CHECK_EQUAL( amat4x3(1,2), 18.0f );
        
        CHECK_EQUAL( amat4x3(2,0), 10.0f );
        CHECK_EQUAL( amat4x3(2,1), -3.0f );
        CHECK_EQUAL( amat4x3(2,2),  0.0f );
        
        CHECK_EQUAL( amat4x3(3,0), 1.0f );
        CHECK_EQUAL( amat4x3(3,1), 5.0f );
        CHECK_EQUAL( amat4x3(3,2), 8.5f );
        
        vec3 avec3 ( 4.7f, 0.0f, -5.3f );
        CHECK_EQUAL( avec3, amat4x3[0] );
        avec3(y) = 10.0f;
        amat4x3[0] = avec3;
        CHECK_EQUAL( avec3, amat4x3[0] );
        avec3(x) = 2.0f;
        CHECK( avec3 != amat4x3[0] );
        amat4x3[0][0] = 2.0f;
        CHECK_EQUAL( avec3, amat4x3[0] );
    }

    TEST( Mat4x3ColumnLookup )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        CHECK_EQUAL( amat4x3(0,0),  4.7f );
        CHECK_EQUAL( amat4x3(0,1),  0.0f );
        CHECK_EQUAL( amat4x3(0,2), -5.3f );
        
        CHECK_EQUAL( amat4x3(1,0),  0.0f );
        CHECK_EQUAL( amat4x3(1,1),  1.0f );
        CHECK_EQUAL( amat4x3(1,2), 18.0f );
        
        CHECK_EQUAL( amat4x3(2,0),  10.0f );
        CHECK_EQUAL( amat4x3(2,1),  -3.0f );
        CHECK_EQUAL( amat4x3(2,2), 0.0f );
        
        CHECK_EQUAL( amat4x3(3,0),  1.0f );
        CHECK_EQUAL( amat4x3(3,1),  5.0f );
        CHECK_EQUAL( amat4x3(3,2), 8.5f );
        
        vec3 avec3 ( 10.0f, -3.0f, 0.0f );
        CHECK_EQUAL( avec3, amat4x3.column(2) );
        avec3(y) = 10.0f;
        amat4x3.column(2) = avec3;
        CHECK_EQUAL( avec3, amat4x3.column(2) );
        avec3(x) = 2.0f;
        CHECK( avec3 != amat4x3.column(2) );
        amat4x3.column(2)[0] = 2.0f;
        CHECK_EQUAL( avec3, amat4x3.column(2) );
    }
    
    TEST( Mat4x3ColumnAssignment )
    {
        using namespace gfx;
        vec3 avec3( 4.7f, 0.0f, -5.3f );
        vec3 bvec3( 0.0f, 1.0f, 18.0f );
        vec3 cvec3( 10.0f, -3.0f, 0.0f );
        vec3 dvec3( 1.0f, 5.0f, 8.5f );
        mat4x3 amat4x3;
        amat4x3.columns( avec3, bvec3, cvec3, dvec3 );
        mat4x3 bmat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        CHECK_EQUAL( bmat4x3, amat4x3 );
    }
    
    TEST( Mat4x3FillAssignment )
    {
        using namespace gfx;
        mat4x3 amat4x3;
        amat4x3.fill( 2.0f );
        mat4x3 bmat4x3( 2.0f, 2.0f, 2.0f, 2.0f,
                        2.0f, 2.0f, 2.0f, 2.0f,
                        2.0f, 2.0f, 2.0f, 2.0f );
        CHECK_EQUAL( bmat4x3, amat4x3 );
    }
    
    TEST( Mat4x3RowLookup )
    {
        using namespace gfx;
        mat4x3 amat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        vec4 avec4( 4.7f, 0.0f, 10.0f, 1.0f );
        vec4 bvec4( 0.0f, 1.0f, -3.0f, 5.0f );
        vec4 cvec4( -5.3f, 18.0f, 0.0f, 8.5f );

        CHECK_EQUAL( avec4, amat4x3.row(0) );
        CHECK_EQUAL( bvec4, amat4x3.row(1) );
        CHECK_EQUAL( cvec4, amat4x3.row(2) );
        avec4(y) = 10.0f;
        amat4x3.row(0) = avec4;
        CHECK_EQUAL( avec4, amat4x3.row(0) );
        avec4(x) = 2.0f;
        CHECK( avec4 != amat4x3.row(0) );
        amat4x3.row(0)[0] = 2.0f;
        CHECK_EQUAL( avec4, amat4x3.row(0) );
    }
    
    TEST( Mat4x3RowAssignment )
    {
        using namespace gfx;
        vec4 avec4( 4.7f, 0.0f, 10.0f, 1.0f );
        vec4 bvec4( 0.0f, 1.0f, -3.0f, 5.0f );
        vec4 cvec4( -5.3f, 18.0f, 0.0f, 8.5f );
        mat4x3 amat4x3;
        amat4x3.rows( avec4, bvec4, cvec4 );
        mat4x3 bmat4x3( 4.7f,  0.0f, 10.0f, 1.0f,
                        0.0f,  1.0f, -3.0f, 5.0f,
                       -5.3f, 18.0f,  0.0f, 8.5f );
        CHECK_EQUAL( bmat4x3, amat4x3 );
    }
}


int main( int argc, char** argv )
{
    return UnitTest::RunAllTests();
}