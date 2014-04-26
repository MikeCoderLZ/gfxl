#include <iostream>

#include "./quaternion.hpp"
#include "./op.hpp"

int main(int argc, char** argv )
{
    using namespace gfx;
    using std::cout;
    using std::endl;

    Qutn qutn1;
    //Qutn qutn2 = Qutn::axisAngle( Vec3( 1.0F, 0.0F, 0.0F), 90.0F / IN_DEGREES );
    Qutn qutn2 = Qutn::axisAngle( Vec3( 1.0F, 0.0F, 0.0F), AngleD::inDegs( 90.0D) );
    Qutn qutn3 = Qutn::axisAngle( Vec3( 0.0F, 1.0F, 0.0F), AngleD::inDegs( 90.0D) );
    Qutn qutn4 = Qutn::axisAngle( Vec3( 0.0F, 0.0F, 1.0F), AngleD::inDegs( 90.0D) );

    cout << "Begining quaternion diagnostics." << endl;
    cout << "90 Degrees in Rads: " << AngleD::inDegs( 90.0D).toRads() << endl;

    cout << "Default quaternion." << endl;
    cout << qutn1 << endl;

    cout << qutn2 << " multiplied by " << qutn3 << endl;
    cout << " should be the same as " << qutn4 << " multiplied by " << qutn2 << "." << endl;
    Qutn qutn_23 = qutn2 * qutn3;
    cout << qutn_23 << endl;
    Qutn qutn_42 = qutn4 * qutn2;
    cout << qutn_42 << endl;

    cout << "Quaternions test complete." << endl;

    return 0;
}
