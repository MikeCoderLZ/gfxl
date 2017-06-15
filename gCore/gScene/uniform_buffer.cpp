#include "uniform_buffer.hpp"

namespace gfx {

    uniform_buffer::uniform_buffer( settings const& set ) :
                                    buffer::buffer( set ) 
    {}
    
    uniform_buffer::~uniform_buffer()
    {}
    
    void uniform_buffer::align()
    {}

}