#ifndef CONTEXT_HPP
#define CONTEXT_HPP

namespace gfx {

    /**
    * The way in which contexts and windows interact is obscure;
    * It is possible that some OpenGL settings need to be saved in
    * order to make this all work correctly.
    * 
    */
    
    /**
     * \class gfx::context context.hpp "gCore/gVideo/context.hpp
     * \brief Represents an OpenGL rendering context.
     * 
     * The context class is a representation of an OpenGL rendering context.
     * A valid context and associated \ref gfx::window "window" are needed
     * to render using OpenGL, and an initialized \ref gfx::video_system
     * "video system" must be present. Some tedious details are handled
     * automagically and configuration uses the \ref gfx::context::settings
     * "settings member class".
     * 
     * \todo Review interaction with the window class. The way in which
     * the two interact is obscure; it is possible that some OpenGL
     * settings need to be saved in order to make this all work correctly.
     * 
     * \see gfx::window
     */
    class context {
    public:
        typedef std::vector<GLubyte>  ub_indexer;
        typedef std::vector<GLushort> us_indexer;
        typedef std::vector<GLuint>   ui_indexer;
        
        /**
         * \class gfx::context::settings
         * \brief Used to configure a \ref gfx::context "context".
         * 
         * A settings object is passed to the context constructor. Calls to
         * the mutator member functions alter the settings used when
         * initializing a context. Subsequent calls overwrite previous calls
         * that alter the same settings and a reference to the settings
         * object is returned to facilitate chaining.
         */        
        class settings {
        public:
                                settings();
        settings&               double_buffered();
        settings&               not_double_buffered();
        settings&               depth_bits( unsigned int bits);
        private:
            friend              class video_system;
            friend              class context;
            unsigned int        n_depth_bits;
            bool                is_double_buffered;
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

    /**
     * \brief Construct a \ref gfx::context::settings "settings" object with
     * default settings.
     * 
     * The default settings for a \ref gfx::context "context" object are 
     * double buffering with 24 bits of depth.
     */
    inline context::settings::settings() : n_depth_bits ( 24 ),
                                           is_double_buffered ( true ) {};
    /**
     * \brief Use double buffering when using the \ref gfx::context::settings
     * "settings" object to construct a \ref gfx::context "context".
     * @see gfx::context::settings::not_double_buffered()
     */
    inline context::settings& context::settings::double_buffered()
    { is_double_buffered = true; return *this; }
    /**
     * \brief Do not use double buffering when using the \ref gfx::context::settings
     * "settings" object to construct a \ref gfx::context "context".
     * @see gfx::context::settings::double_buffered()
     */
    inline context::settings& context::settings::not_double_buffered()
    { is_double_buffered = false; return *this; }
    /**
     * \brief Set the number of depth bits to use when constructing a
     * \ref gfx::context "context" object.
     * No bounds checking is done, so outrageous amounts of depths bits may
     * cause errors. Furthermore, simply indicating a number of depth bits
     * will not automatically set the context to use depth testing.
     * @param bits The number of depth bits to use
     */
    inline context::settings& context::settings::depth_bits( unsigned int bits )
    { n_depth_bits = bits; return *this; }
    /**
     * \brief Compare this \ref gfx::context "context" to another for equality.
     * The comparison is down using internal OpenGL system values; it is feasible
     * that two contexts could compare equal, but extremely extremely unlikely
     * as it would require ill-advised hacking of how the \ref gfx::video_system
     * "video system" works.
     * @param rhs The context to compare this context to
     */
    inline  bool    context::operator ==( context const& rhs ) const
    { return this->sys_context == rhs.sys_context; }
    /**
     * \brief Draw triangles using the indices given.
     * This is a trainwreck of badness; it is only a placeholder and I don't
     * even know if it works (I strongly suspect it does not). It requires
     * a vertex array object and associated buffer to be active before it works.
     * @param tris The number of triangles the given indexer describes
     * @param indices The indices that describe the triangles.
     */
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