#include <iostream>

//#include "type_op.hpp"
#include "datatype.hpp"
#include "swizzTest.hpp"

int main( int argc, char** argv )
{
    using namespace gfx;
    using std::cout;
    using std::endl;

    float32 scalarf_1;
    float32 scalarf_2 (0.4f);
    float32 scalarf_3 (2.0f);

    fvec2 vec2_1;
    fvec2 vec2_2 ( 0.5f, -1.2f );
    fvec2 vec2_3 ( 2.0f );

    fvec3 vec3_1;
    fvec3 vec3_2 ( 0.5f, -1.2f, 8.2f );
    fvec3 vec3_3 ( 2.0f );

    fvec4 vec4_1;
    fvec4 vec4_2 ( 0.5f, -1.2f, 8.2f, -8.6f );
    fvec4 vec4_3 ( 2.0f );
    
    mat<float> mat_33_1(3,3);
    mat<float> mat_33_I = mat<float>::identity(3);
    mat<float> mat_32_1(3,2);
    mat_32_1(1,0) = 4.1f;
    mat_32_1(0,1) = -23.7f;

    cout << test::output_float() << endl;
    cout << "Running datatype diagnositcs." << endl;

    cout << "A scalar!" << endl;
    cout << scalarf_1 << endl;

    cout << "Default fvec2." << endl;
    cout << vec2_1 << endl;
    cout << "Constructed fvec2 with 0.5, -1.2." << endl;
    cout << vec2_2 << endl;
    cout << "Constructed fvec2 with 2.0" << endl;
    cout << vec2_3 << endl;

    cout << "Default fvec3." << endl;
    cout << vec3_1 << endl;
    cout << "Constructed fvec3 with 0.5, -1.2, 8.2." << endl;
    cout << vec3_2 << endl;
    cout << "Constructed fvec3 with 2.0" << endl;
    cout << vec3_3 << endl;

    cout << "Default fvec4." << endl;
    cout << vec4_1 << endl;
    cout << "Constructed fvec4 with 0.5, -1.2, 8.2, -8.6." << endl;
    cout << vec4_2 << endl;
    cout << "Constructed fvec4 with 2.0" << endl;
    cout << vec4_3 << endl;

    cout << "And type reporting; this name is forwarded through the built-in type system." << endl;
    cout << type<fvec3>().name() << endl;

    cout << type<fvec3>().n_components() << endl;
    cout << type<fvec3>().component_size() << endl;
    cout << type<fvec3>().mapped_size() << endl;

    cout << "Now to proper diagnostics. Here we check the swizzles." << endl;
    cout << "vec2_2(x,x): " << vec2_2 << " to " << vec2_2(x,x) << endl;
    cout << "vec3_2(y,x,z): " << vec3_2 << " to " << vec3_2(y,x,z) << endl;
    cout << "vec4_2(w,y,x,z): " << vec4_2 << " to " << vec4_2(w,y,x,z) << endl;

    cout << "Test some operators; addition of additive inverse of all vectors should yield 0 (or close to it)" << endl;
    cout << vec2_2 + vec2_2(-x,-y) << endl;
    cout << vec3_2 + vec3_2(-x,-y,-z) << endl;
    cout << vec4_2 + vec4_2(-x,-y,-z,-w) << endl;

    cout << "Subtraction of additive inverse should double the magnitudes." << endl;
    cout << vec2_2 - vec2_2(-x,-y) << endl;
    cout << vec3_2 - vec3_2(-x,-y,-z) << endl;
    cout << vec4_2 - vec4_2(-x,-y,-z,-w) << endl;

    cout << "Multiply by a vector filled with 2.0 should yield the same." << endl;
    cout << vec2_2 * fvec2(2.0f) << endl;
    cout << vec3_2 * fvec3(2.0f) << endl;
    cout << vec4_2 * fvec4(2.0f) << endl;

    cout << "Multiply by a vector filled with 0.5 should half the magnitudes." << endl;
    cout << vec2_2 * fvec2(0.5f) << endl;
    cout << vec3_2 * fvec3(0.5f) << endl;
    cout << vec4_2 * fvec4(0.5f) << endl;

    cout << "Dividing by vector filled with 2.0 should half the magnitudes as well." << endl;
    cout << vec2_2 / fvec2(2.0f) << endl;
    cout << vec3_2 / fvec3(2.0f) << endl;
    cout << vec4_2 / fvec4(2.0f) << endl;

    cout << "Testing scalar operators; lot's of type promotion." << endl;
    cout << "should be 1.4: " << scalarf_2 + 1.0f << endl;
    cout << "should be 0.2: " << (float32) (0.5f * scalarf_2) << endl;
    cout << "should be 0.2: " << scalarf_2 / 2.0f << endl;
    cout << "should be -1.6: " << scalarf_2 - scalarf_3 << endl;

    cout << "Testing mutators." << endl;
    scalarf_2 = 1.5f;
    cout << "should be 1.5: " << scalarf_2 << endl;
    vec2_1(x) = 42.0f;
    cout << "should be 42.0: " << vec2_1(x) << endl;
    vec3_1(y) = -89.0f;
    cout << "should be -89.0: " << vec3_1(y) << endl;
    vec4_1(w) = 0.048f;
    cout << "should be 0.048: " << vec4_1(w) << endl;
    
    cout << "Testing Matrices" << endl;
    
    cout << "Default construction of 3x3" << endl;
    cout << mat_33_1 << endl;
    
    cout << "Now, fill it with the value 5.7:" << endl;
    
    mat_33_1.fill( 5.7f );
    cout << mat_33_1 << endl;
    
    cout << "Now, the same, but using the named contructor:" << endl;
    
    mat<float> mat_33_2 = mat<float>::fill( 3,3, 5.7f );
    cout << mat_33_2 << endl;
    
    cout << "Identity matrix, 3x3" << endl;
    cout << mat_33_I << endl;
    
    cout << "Multiplication with Identity matrix should not change the matrix:" << endl;
    cout << mat_33_I * mat_33_2 << endl;
    
    cout << "Whereas multiplication with a zero matrix should result in all zeroes:" << endl;
    
    mat_33_1.fill( 0.0f );
    cout << mat_33_1 * mat_33_2 << endl;
    
    cout << "Let's scale that matrix by 2 using the identity matrix and a scalar:" << endl;
    cout << 2.0f * mat_33_I * mat_33_2 << endl;
    
    cout << "Let's alter the components..." << endl;
    mat_33_2(2,0) = -6.5f;
    cout << mat_33_2 << endl;
    cout << "And then transpose the matrix:" << endl;
    mat_33_2.transpose();
    cout << mat_33_2 << endl;
    
    cout << "A 3x2 matrix with some values:" << endl;
    cout << mat_32_1 << endl;
    
    cout << "Now transpose it:" << endl;
    mat_32_1.transpose();
    cout << mat_32_1 << endl;

    cout << "Datatype diagnostics complete." << endl;
    return 0;
}
