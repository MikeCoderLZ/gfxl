#ifndef TYPE_OP_HPP
#define TYPE_OP_HPP

#include <cstddef>
#include <typeinfo>
#include "../gVideo/gl_core_3_3.hpp"

#define G_TYPE( TYPE_NAME, N_COMPONENTS, COMPONENT_SIZE, GL_ENUM ) \
        class type< TYPE_NAME > { \
        public: \
            static size_t n_components() { return N_COMPONENTS; } \
            static size_t component_size() { return COMPONENT_SIZE; } \
            static GLenum component_to_GL() { return GL_ENUM; } \
            static size_t mapped_size() { return n_components() * component_size(); } \
            static char const* to_string() { return typeid(TYPE_NAME).name(); } \
        };

namespace gfx {

    template< typename T >
    class type {
    public:
        static size_t n_components() { return 1; }
        static size_t component_size() { return sizeof(T); }
        static GLenum component_to_GL() { return gl::NONE; }
        static size_t mapped_size() { return n_components() * component_size(); }
        static char const* to_string() { return typeid(T).name(); }
    };

}

#endif
