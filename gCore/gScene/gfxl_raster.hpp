#pragma once

namespace gfx {

class Raster {
    
    enum class Format {
        RGB8,
        RGBA8
    };
    
    template< typename storage_type >
    class Pixel {
    public:
        storage_type r() const;
        storage_type g() const;
        storage_type b() const;
        storage_type a() const;
    };
    
    
}

inline size_t channelBits( Raster::Format format )
{
    switch ( format ) {
        case RGB8 :
            return 8;
        case RGBA8 :
            return 8;
    }
}

inline size_t redBits( Raster::Format format )
{
    switch ( format ) {
        case RGB8 :
            return 8;
        case RGBA8 :
            return 8;
    }
}

inline size_t greenBits( Raster::Format format )
{
    switch ( format ) {
        case RGB8 :
            return 8;
        case RGBA8 :
            return 8;
    }
}

inline size_t blueBits( Raster::Format format )
{
    switch ( format ) {
        case RGB8 :
            return 8;
        case RGBA8 :
            return 8;
    }
}

class Raster2D : public Raster {
public:
    
    Raster2D()
      : mFormat ( Raster::Format.RGB8 ),
        xDim (0),
        yDim (0),
        displayRatio (1.0f) {}

    Raster2D( int width, int height, Raster::Format format )
      : mFormat ( format ),
        xDim( width ),
        yDim( height ),
        displayRatio (1.0f) {}
    
    Raster2D( const char* data, int width, int height, Raster::Format format )
      : mFormat ( format ),
        xDim( width ),
        yDim( height ),
        displayRatio (1.0f)
    {
        
    }
    
protected:

    Raster::Format mFormat;
   /**
    * The ratio of screen dimensions to raster dimensions.Typically 1,
    * but on Mac it would sometimes be 0.5.
    */
   int xDim;
   int yDim;
   
   float displayRatio;
    
}

}