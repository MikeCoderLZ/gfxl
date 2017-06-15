#include "block_spec.hpp"

namespace gfx {

    block_spec::~block_spec()
    {
        attrib_vector::iterator i;
        for( i = attributes->begin(); i != attributes->end(); ++i )
            { delete *i; }
        delete attributes;
    }
}