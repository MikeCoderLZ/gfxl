#ifndef CLASS_A_HPP
#define CLASS_A_HPP

class ClassA {
public:
    ClassA() {};
    virtual ~ClassA() {};
    virtual ClassA* copy() const { return new ClassA(); }
};

#endif
