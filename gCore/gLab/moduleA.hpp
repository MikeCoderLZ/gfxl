#ifndef MODULE_A_HPP
#define MODULE_A_HPP

#include <iostream>
#include "classA.hpp"

class ModuleA {
public:
    ClassA a_class;
    ModuleA();
    virtual void foo();
};

class ModuleC : public ModuleA {
public:
    ModuleC();
    virtual void foo();
};

#endif
