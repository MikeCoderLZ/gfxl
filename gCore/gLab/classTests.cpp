#include <iostream>
#include <fstream>

#include "moduleA.hpp"
#include "moduleB.hpp"

int main( int argc, char** argv )
{
    ModuleA test_mod_1;
    ModuleB test_mod_2;
    ModuleC test_mod_3;

    test_mod_1.foo();
    test_mod_3.foo();

    std::cout << test_mod_2;

    std::fstream testFile("./shader/testFrag.glsl", std::ios_base::in );

    if( testFile.fail() ) {
        std::cout << "File load failed." << std::endl;
    } else {
        std::cout << "File load succeeded." << std::endl;
    }

    size_t buffer_size = 128;
    char* buffer = new char[buffer_size];

    std::string fileData = "";

    while( testFile.good() ) {
        // This looks ugly, I know.  Translation:
        // "read a number of bytes equal to the size of the read
        // buffer minus one then assign the character at the end
        // of that read to a null terminating character.
        buffer[ testFile.read( buffer, buffer_size - 1 ).gcount() ] = '\0';
        fileData += buffer;
    }

    std::cout << fileData << std::endl;

    return 0;
}
