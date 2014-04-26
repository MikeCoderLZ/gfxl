#ifndef TYPE_HPP
#define TYPE_HPP

#include <cstddef>
#include <sstream>
#include <string>
#include "../gVideo/gl_core_3_3.hpp"

namespace gfx {

  namespace type {

    template< typename T >
    inline std::string value_type_to_string()
    {
        return T::type_schema.to_string();
    }

    template< typename T, size_t N >
    class schema {
      public:
        schema( std::string const& name ) : name( name )
            {
                this->name += "<" + value_type_to_string<T>() + ">";
            };

        inline static size_t n_components() { return N; };
        inline static size_t n_bytes() { return sizeof(T); };
        inline std::string const& to_string() const { return name; }

        inline bool operator==( schema const& rhs ) const
                {
                    return (this->n_components() == rhs.n_components())
                            && (this->n_bytes() == rhs.n_bytes())
                            && (this->to_string() == rhs.to_string());
                }

      private:
        std::string name;

    };

    template<>
    inline std::string value_type_to_string<float>() { return "float"; };
    template<>
    inline std::string value_type_to_string<double>() { return "double"; };
    template<>
    inline std::string value_type_to_string<char>() { return "char"; };
    template<>
    inline std::string value_type_to_string<short>() { return "short"; };
    template<>
    inline std::string value_type_to_string<int>() { return "int"; };
    template<>
    inline std::string value_type_to_string<unsigned char>() { return "unsigned char"; };
    template<>
    inline std::string value_type_to_string<unsigned short>() { return "unsigned short"; };
    template<>
    inline std::string value_type_to_string<unsigned int>() { return "unsigned int"; };

    template< typename T, size_t N >
    class vec : public schema<T,N> {
      public:
        friend class schema_factory;
        vec( std::string const& name ) : schema<T,N>( name ) {}

    };

    template< typename T >
    class scalar : public schema<T,1> {
      public:
        friend class schema_factory;
        scalar(std::string const& name ) : schema<T,1>( name) {};

    };

    extern vec<float, 4> const fvec4;
    extern vec<float, 3> const fvec3;
    extern vec<float, 2> const fvec2;
    extern scalar<float> const float32;

    extern vec<double, 4> const dvec4;
    extern vec<double, 3> const dvec3;
    extern vec<double, 2> const dvec2;
    extern scalar<double> const double64;

    extern vec<int, 4> const ivec4;
    extern vec<int, 3> const ivec3;
    extern vec<int, 2> const ivec2;
    extern scalar<int> const int32;

    extern vec<short, 4> const svec4;
    extern vec<short, 3> const svec3;
    extern vec<short, 2> const svec2;
    extern scalar<short> const short16;

    extern vec<char, 4> const cvec4;
    extern vec<char, 3> const cvec3;
    extern vec<char, 2> const cvec2;
    extern scalar<char> const char8;

    extern vec<unsigned int, 4> const uvec4;
    extern vec<unsigned int, 3> const uvec3;
    extern vec<unsigned int, 2> const uvec2;
    extern scalar<unsigned int> const uint32;

    extern vec<unsigned short, 4> const usvec4;
    extern vec<unsigned short, 3> const usvec3;
    extern vec<unsigned short, 2> const usvec2;
    extern scalar<unsigned short> const ushort16;

    extern vec<unsigned char, 4> const ucvec4;
    extern vec<unsigned char, 3> const ucvec3;
    extern vec<unsigned char, 2> const ucvec2;
    extern scalar<unsigned char> const uchar8;

  }

}

#endif
