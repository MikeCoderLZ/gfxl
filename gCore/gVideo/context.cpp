namespace gfx {

    context::~context()
    {
        owner->del_context( *this );
    }
    
    void context::clear_color( float red, float green, float blue, float alpha )
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Render operation 'clear_color()' called on Context that is not active." );
        }

        gl::ClearColor( red, green, blue, alpha );
        gl::Clear( gl::COLOR_BUFFER_BIT );
    }
    
    unsigned int    context::major_version() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'major_version()' called on Context that is not active." );
        }
        int maj_ver;
        int ret = SDL_GL_GetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, &maj_ver );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'major_version()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return (unsigned int)  maj_ver;
    }
    
    unsigned int    context::minor_version() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'minor_version()' called on Context that is not active." );
        }
        int min_ver;
        int ret = SDL_GL_GetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, &min_ver );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'minor_version()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return (unsigned int) min_ver ;
    }
    
    uvec2    context::version() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'version()' called on Context that is not active." );
        }
        int maj_ver;
        int ret = SDL_GL_GetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, &maj_ver );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'major_version()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        
        int min_ver;
        ret = SDL_GL_GetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, &min_ver );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'minor_version()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return uvec2( (unsigned int) maj_ver, (unsigned int) min_ver );
    }
    
    unsigned int    context::depth_bits() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'depth_bits()' called on Context that is not active." );
        }
        int bits;
        int ret = SDL_GL_GetAttribute( SDL_GL_DEPTH_SIZE, &bits );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'depth_bits()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return (unsigned int) bits;
    }
    
    bool    context::double_buffered() const
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Property query 'double_buffered()' called on Context that is not active." );
        }
        int buffed;
        int ret = SDL_GL_GetAttribute( SDL_GL_DOUBLEBUFFER, &buffed );
        if ( ret != 0 ) {
            std::string msg ( "Property query 'double_buffered()' failed:\n\t" );
            msg += SDL_GetError();
            throw std::runtime_error( msg );
        }
        return bool( buffed );
    }
}