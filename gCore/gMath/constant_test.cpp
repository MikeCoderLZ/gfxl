#include <iostream>

#include "../../UnitTest++_src/UnitTest++.h"
#include "constant.hpp"

SUITE( Angles )
{
    TEST( Radians )
    {
        using namespace gfx;
        angle ang_deg = angle::in_degs( 90.0f );
        angle ang_rad = angle::in_rads( f_lit::pi * 0.5f );
        float diff ( f_lit::delta );
        CHECK_CLOSE( ang_deg.to_rads(),
                     ang_rad.to_rads(),
                     diff );
    }
    
    TEST( Gradians )
    {
        using namespace gfx;
        angle ang_deg = angle::in_degs( 90.0f );
        angle ang_rad = angle::in_grads( 50.0f );
        float diff ( f_lit::delta );
        CHECK_CLOSE( ang_deg.to_grads(),
                     ang_rad.to_grads(),
                     diff );
    }
    
    TEST( Degrees )
    {
        using namespace gfx;
        angle ang_deg1 = angle::in_degs( 90.0f );
        angle ang_deg2 = angle::in_degs( 45.0f );
        float diff ( f_lit::delta );
        CHECK_CLOSE( ang_deg1.to_degs(),
                     ang_deg2.to_degs() * 2.0f,
                     diff );
    }
}

SUITE( Constants )
{
    TEST( Pi )
    {
        using namespace gfx;
        float pi_v = f_lit::pi;
        float pi_v_neg = f_lit::pi * f_lit::neg_one;
        float pi_h = f_lit::pi * f_lit::half;
        float pi_i = f_lit::inv_pi;
        float diff ( f_lit::delta );
        CHECK_CLOSE( pi_v, pi_h * 2.0f, diff );
        CHECK_CLOSE( 1.0f, pi_v * pi_i, diff );
        CHECK_CLOSE( 0.0f, pi_v + pi_v_neg, diff );
    }
    
    TEST( Tau )
    {
        using namespace gfx;
        float pi_v = f_lit::pi;
        float tau_v = f_lit::tau;
        float tau_v_neg = f_lit::tau * f_lit::neg_one;
        float tau_h = f_lit::tau * f_lit::half;
        float tau_i = f_lit::inv_tau;
        float diff ( f_lit::delta );
        CHECK_CLOSE( tau_v, pi_v * 2.0f, diff );
        CHECK_CLOSE( tau_v, tau_h * 2.0f, diff );
        CHECK_CLOSE( 1.0f, tau_v * tau_i, diff );
        CHECK_CLOSE( 0.0f, tau_v + tau_v_neg, diff );
    }
    
    TEST( sqrtTwo )
    {
        using namespace gfx;
        float sqrt_two_v = f_lit::sqrt_two;
        float sqrt_two_v_neg = f_lit::sqrt_two * f_lit::neg_one;
        float sqrt_two_h = f_lit::sqrt_two * f_lit::half;
        float sqrt_two_i = f_lit::inv_sqrt_two;
        float diff ( f_lit::delta );
        CHECK_CLOSE( sqrt_two_v, sqrt_two_h * 2.0f, diff );
        CHECK_CLOSE( 1.0f, sqrt_two_v * sqrt_two_i, diff );
        CHECK_CLOSE( 2.0f, sqrt_two_v * sqrt_two_v, diff );
        CHECK_CLOSE( 0.0f, sqrt_two_v + sqrt_two_v_neg, diff );
    }
    
    TEST( sqrtThree )
    {
        using namespace gfx;
        float sqrt_three_v = f_lit::sqrt_three;
        float sqrt_three_v_neg = f_lit::sqrt_three * f_lit::neg_one;
        float sqrt_three_h = f_lit::sqrt_three * f_lit::half;
        float sqrt_three_i = f_lit::inv_sqrt_three;
        float diff ( f_lit::delta );
        CHECK_CLOSE( sqrt_three_v, sqrt_three_h * 2.0f, diff );
        CHECK_CLOSE( 1.0f, sqrt_three_v * sqrt_three_i, diff );
        CHECK_CLOSE( 3.0f, sqrt_three_v * sqrt_three_v, diff );
        CHECK_CLOSE( 0.0f, sqrt_three_v + sqrt_three_v_neg, diff );
    }
    
    TEST( ThreeSixty )
    {
        using namespace gfx;
        float n360_v = f_lit::n360;
        float n360_v_neg = f_lit::n360 * f_lit::neg_one;
        float n360_h = f_lit::n360 * f_lit::half;
        float n360_i = f_lit::inv_360;
        float diff ( f_lit::delta );
        CHECK_CLOSE( n360_v, n360_h * 2.0f, diff );
        CHECK_CLOSE( 1.0f, n360_v * n360_i, diff );
        CHECK_CLOSE( 0.0f, n360_v + n360_v_neg, diff );
    }
    
    TEST( Phi )
    {
        using namespace gfx;
        float phi_v = f_lit::phi;
        // Ratio of consecutive Fibonacci numbers: F(39):F(38)
        float phi_g = 39088169.0f / 24157817.0f; 
        float diff ( f_lit::delta );
        CHECK_CLOSE( phi_g, phi_v, diff );
    }
}

int main( int argc, char** argv )
{
     return UnitTest::RunAllTests();
}