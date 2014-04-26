#include "moduleA.hpp"

ModuleA::ModuleA() : a_class() {}

void ModuleA::foo() { std::cout << "ModuleA foo." << std::endl; }

ModuleC::ModuleC() : ModuleA() {}

void ModuleC::foo() { std::cout << "ModuleC foo." << std::endl; }
