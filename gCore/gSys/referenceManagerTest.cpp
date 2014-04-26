#include "./referenceManager.hpp"
#include <iostream>

int main( int argc, char** argv )
{
    using namespace gfx;
    using std::cout;
    using std::endl;

    ReferenceManager man;
    Ref test1 = man.reference("test1.content1");
    Ref test2 = man.reference("test1.content2");
    Ref test3 = man.reference("test2.content3");

    cout << test1;

    cout << "Beginning ReferenceManager diagnostics." << endl;

    cout << man;

    cout << "Done." << endl;

    return 0;

}
