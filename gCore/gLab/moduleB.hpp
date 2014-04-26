#ifndef MODULE_B_HPP
#define MODULE_B_HPP

#include <iostream>

#include "classA.hpp"

class ModuleB {
public:
    friend  std::ostream& operator<<( std::ostream& out, ModuleB const& src );
            ModuleB();
    ClassA  a_class;
private:
    union {
        float components[3];
        unsigned char bytes[ sizeof(float) * 3];
    } data;
};

inline  std::ostream& operator<<( std::ostream& out, ModuleB const& src )
{
    out << "<" << src.data.components[0] << "," << src.data.components[1] << "," << src.data.components[2] << ">" << std::endl;
    return out;
}

#endif
