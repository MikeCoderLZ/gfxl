#include "datatypes.hpp"

namespace gfx {

// Isolating the instantiation of the actual swizzle objects
// to its own compilation unit like this makes it extremely
// unlikely someone will circumvent the system and flub it up.
//
// They would literally have to try to flub it up on purpose.
    
class swizz_factory {
public:
    inline static swizz4 make_swizz4( int index )
    {
        return swizz4( index );
    }
    inline static swizz3 make_swizz3( int index )
    {
        return swizz3( index );
    }
    inline static swizz2 make_swizz2( int index ){
        return swizz2( index );
    }
    inline static swizz1 make_swizz1( int index ){
        return swizz1( index );
    }
};

// Classical Components
//swizz1 const x = swizz_factory::make_swizz1( 1 );
swizz2 const y = swizz_factory::make_swizz2( 2 );
swizz3 const z = swizz_factory::make_swizz3( 3 );
swizz4 const w = swizz_factory::make_swizz4( 4 );
// Texture Coordinates
swizz1 const s = swizz_factory::make_swizz1( 1 );
swizz2 const t = swizz_factory::make_swizz2( 2 );
swizz3 const p = swizz_factory::make_swizz3( 3 );
swizz4 const q = swizz_factory::make_swizz4( 4 );
// Color Coordinates
swizz1 const r = swizz_factory::make_swizz1( 1 );
swizz2 const g = swizz_factory::make_swizz2( 2 );
swizz3 const b = swizz_factory::make_swizz3( 3 );
swizz4 const a = swizz_factory::make_swizz4( 4 );
// Hamiltonian Coordinates
swizz1 const i = swizz_factory::make_swizz1( 1 );
swizz2 const j = swizz_factory::make_swizz2( 2 );
swizz3 const k = swizz_factory::make_swizz3( 3 );
swizz4 const m = swizz_factory::make_swizz4( 4 );

}
