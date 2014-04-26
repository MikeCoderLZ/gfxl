#ifndef DATATYPE_INFO_HPP
#define DATATYPE_INFO_HPP

#include <typeinfo>
#include "../gVideo/gl_core_3_3.hpp"

namespace gfx {

enum type_class { INTEGER, FLOAT, DOUBLE };

class info {
public:
                        info( char const* new_name);
    virtual             ~info()                 {}
    virtual size_t      n_components() const    = 0;
    virtual size_t      component_size() const  = 0;
    virtual GLenum      component_to_GL() const = 0;
    virtual size_t      mapped_size() const     = 0;
    virtual type_class  mapping() const         = 0;
    virtual char const* name() const            = 0;
    virtual info*       copy() const            = 0;
    virtual bool        operator==( info const& rhs ) const { return str_name == rhs.str_name; }
    virtual bool        operator!=( info const& rhs ) const { return str_name != rhs.str_name; }
protected:
    std::string str_name;
};

inline  info::info( char const* new_name ) : str_name( new_name ) {}

template< typename T >
class type : public info {
public:
                            type() : info( typeid(T).name() ) {}
                            type( T const& dummy ) : info( typeid(T).name() )  {}
    virtual                 ~type()                 {}
    virtual size_t          n_components() const    { return 1; }
    virtual size_t          component_size() const  { return sizeof(T); }
    virtual GLenum          component_to_GL() const { return gl::NONE; }
    virtual size_t          mapped_size() const     { return n_components() * component_size(); }
    virtual type_class      mapping() const         { return INTEGER; }
    virtual char const*     name() const            { return str_name.c_str(); }
    virtual type<T>*        copy() const            { return new type<T>(); }
    virtual bool            operator==( type<T> const& rhs ) const { return true; }
    virtual bool            operator!=( type<T> const& rhs ) const { return false; }

};

template<>
class type< float > : public info {
public:
                            type() : info( typeid(float).name() ) {}
                            type( float const& dummy ) : info( typeid(float).name() )  {}
    virtual                 ~type()                 {}
    virtual size_t          n_components() const    { return 1; }
    virtual size_t          component_size() const  { return sizeof(float); }
    virtual GLenum          component_to_GL() const { return gl::FLOAT; }
    virtual size_t          mapped_size() const     { return n_components() * component_size(); }
    virtual type_class      mapping() const         { return FLOAT; }
    virtual char const*     name() const            { return str_name.c_str(); }
    virtual type<float>*    copy() const            { return new type<float>(); }
    virtual bool            operator==( type<float> const& rhs ) const { return true; }
    virtual bool            operator!=( type<float> const& rhs ) const { return false; }

};

template<>
class type< double > : public info {
public:
                            type() : info( typeid(double).name() ) {}
                            type( double const& dummy ) : info( typeid(double).name() )  {}
    virtual                 ~type()                 {}
    virtual size_t          n_components() const    { return 1; }
    virtual size_t          component_size() const  { return sizeof(double); }
    virtual GLenum          component_to_GL() const { return gl::DOUBLE; }
    virtual size_t          mapped_size() const     { return n_components() * component_size(); }
    virtual type_class      mapping() const         { return DOUBLE; }
    virtual char const*     name() const            { return str_name.c_str(); }
    virtual type<double>*   copy() const            { return new type<double>(); }
    virtual bool            operator==( type<double> const& rhs ) const { return true; }
    virtual bool            operator!=( type<double> const& rhs ) const { return false; }

};

#define G_TYPE( TYPE_NAME, N_COMPONENTS, COMPONENT_SIZE, GL_ENUM, MAPPING ) \
    class type< TYPE_NAME > : public info { \
    public: \
                                    type() : info( typeid(TYPE_NAME).name() ) {} \
                                    type( TYPE_NAME const& dummy ) : info( typeid(TYPE_NAME).name() )  {} \
        virtual                     ~type()                         {} \
        virtual size_t              n_components() const            { return (N_COMPONENTS); } \
        virtual size_t              component_size() const          { return (COMPONENT_SIZE); } \
        virtual GLenum              component_to_GL() const         { return (GL_ENUM); } \
        virtual size_t              mapped_size() const             { return n_components() * component_size(); } \
        virtual type_class          mapping() const                 { return MAPPING; } \
        virtual char const*         name() const                    { return str_name.c_str(); } \
        virtual type<TYPE_NAME>*    copy() const                    { return new type<TYPE_NAME>(); } \
        virtual bool                operator==( type<TYPE_NAME> const& rhs ) const  { return true; } \
        virtual bool                operator!=( type<TYPE_NAME> const& rhs ) const { return false; } \
    };

}
#endif
