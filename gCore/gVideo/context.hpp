#ifndef CONTEXT_HPP
#define CONTEXT_HPP

namespace gfx {

    /**
    * The way in which contexts and windows interact is obscure;
    * It is possible that soem OpenGL setting need to be saved in
    * order to make this all work correctly.
    * 
    */
                                
    class context : public managed {
    public:
        typedef std::vector<GLubyte>  ub_indexer;
        typedef std::vector<GLushort> us_indexer;
        typedef std::vector<GLuint>   ui_indexer;
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
        class settings {
        public:
                                settings();
        private:
            friend              class video_manager;
        };
        
    private:
                                context( video_manager* const owner,
                                        size_t g_id,
                                        window const* target_window,
                                        SDL_GLContext sys_context);
        window const*           target_window;
        SDL_GLContext           sys_context;
        friend                  class video_manager;
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

    inline context::context( video_manager* const owner,
                            size_t g_id,
                            window const* target_window,
                            SDL_GLContext sys_context    ) :
                                managed( owner, g_id ),
                                target_window( target_window ),
                                sys_context( sys_context )      {}
}
#endif