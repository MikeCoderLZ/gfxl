#ifndef CONTEXT_HPP
#define CONTEXT_HPP

namespace gfx {

    /**
    * The way in which contexts and windows interact is obscure;
    * It is possible that some OpenGL settings need to be saved in
    * order to make this all work correctly.
    * 
    */
                                
    class context {
    public:
        typedef std::vector<GLubyte>  ub_indexer;
        typedef std::vector<GLushort> us_indexer;
        typedef std::vector<GLuint>   ui_indexer;
        
        class settings {
        public:
                                settings();
        private:
            friend              class video_system;
        };
        
                                context( window const& target_window,
                                         settings const& set = settings() );
                                ~context();
        void                    clear_color( float red, float green,
                                            float blue, float alpha = 1.0f );
        bool                    is_active() const;
        unsigned int            major_version() const;
        unsigned int            minor_version() const;
        uvec2                   version() const;
        unsigned int            depth_bits() const;
        bool                    double_buffered() const;
        bool                    operator ==( context const& rhs ) const;
        
        void                    draw_triangles( size_t const tris,
                                                ui_indexer const& indices );

        
    private:
                                
        window const*           target_window;
        SDL_GLContext           sys_context;
        friend                  class video_system;
    };

    inline context::settings::settings() {};

    inline  bool    context::operator ==( context const& rhs ) const
    { return this->sys_context == rhs.sys_context; }

    inline void     context::draw_triangles( size_t const tris,
                                            ui_indexer const& indices )
    {
        if ( not this->is_active() ) {
            throw std::logic_error( "Request to draw triangles on in-active context." );
        }
        gl::DrawElements( gl::TRIANGLES,
                        tris * 3,
                        gl::UNSIGNED_INT,
                        &indices[0] );
    }
}
#endif