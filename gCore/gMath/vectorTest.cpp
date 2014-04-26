#include <iostream>

#include "./vec.hpp"
#include "./op.hpp"

int main( int argc, char** argv )
{
    using namespace gfx;

    using std::cout;
    using std::endl;

    Vec2 vec2_1;
    Vec2 vec2_2 ( 0.5f, -1.2f );
    Vec2 vec2_3 ( 2.0f );

    Vec3 vec3_1;
    Vec3 vec3_2 ( 15.0f, -2.1f, 8.2f );
    Vec3 vec3_3 ( -1.2f );
    Vec3 vec3_x ( 1.0f, 0.0f, 0.0f );
    Vec3 vec3_y ( 0.0f, 1.0f, 0.0f );

    Vec3 vec3_copy = vec3_3;

    Vec4 vec4_1;
    Vec4 vec4_2 (45.1f, 0.25f, -1.25f, -0.026f );
    Vec4 vec4_3 ( -5.8f );
    Vec4 vec4_4 ( 1.0f, 1.0f, 0.0f, 0.0f );

    cout << "Running vector diagnositcs." << endl;

    cout << "Default Vec2." << endl;
    cout << vec2_1 << endl;
    cout << "Default Vec3." << endl;
    cout << vec3_1 << endl;
    cout << "Default Vec4." << endl;
    cout << vec4_1 << endl;

    cout << "Constructed Vec2 <0.5,-1.2>." << endl;
    cout << vec2_2 << endl;
    cout << "Constructed Vec3 <15.0,-2.1, 8.2>." << endl;
    cout << vec3_2 << endl;
    cout << "Constructed Vec4 <45.1,0.25.-1.25, -0.026>." << endl;
    cout << vec4_2 << endl;

    cout << "Filled Vec2 <2.0,2.0>." << endl;
    cout << vec2_3 << endl;
    cout << "Filled Vec3 <-1.2,-1.2,-1.2>." << endl;
    cout << vec3_3 << endl;
    cout << "Filled Vec4 <-5.8,-5.8,-5.8,-5.8>." << endl;
    cout << vec4_3 << endl;

    cout << "Copied value of vectr filled with -1.2." << endl;
    cout << vec3_copy << endl;

    cout << "Constructed Vec2 Swizzled to <1.2,0.5>." << endl;
    Vec2 vec2_4 = vec2_2(-y,x);
    cout << vec2_4 << endl;
    cout << "Constructed Vec3 Swizzled to <8.2,2.1,-2.1>." << endl;
    Vec3 vec3_4 = vec3_2(z,-y,y);
    cout << vec3_4 << endl;
    cout << "Constructed Vec4 Swizzled to <45.1,-0.25,45.1,-1.25>." << endl;
    Vec4 vec4_5 = vec4_2(x,-y,x,z);
    cout << vec4_5 << endl;

    cout << "Vector <1,1,0,0> normalized." << endl;
    cout << norm( vec4_4 ) << endl;

    cout << "X-axis interpolated linearly halfway to Y-axis." << endl;
    cout << mix_ln( vec3_x, vec3_y, 0.5f ) << endl;

    cout << "Vector diagnostics complete." << endl;
    return 0;
}
