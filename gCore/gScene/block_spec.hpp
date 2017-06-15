#ifndef BLOCK_SPECK_HPP
#define BLOCK_SPEC_HPP

namespace gfx {

    class block_spec {
    public:
                                        block_spec();
                                        ~block_spec();
        template< typename T >
        block_spec&                      attribute( type<T> const& proto );
    private:
        friend                          class buffer;
        typedef std::vector< info* >    attrib_vector;
        attrib_vector*                  attributes;
    };

    inline  block_spec::block_spec() : attributes( new block_spec::attrib_vector() ) {}
    
    template< typename T > inline
    block_spec&     block_spec::attribute( type<T> const& proto )
    {   
        // pointers to the type class can be safely
        // cast to pointers to the info ABC
        info* new_attrib = (info*) proto.copy();
        attributes->push_back( new_attrib );
        return *this; }
}
#endif