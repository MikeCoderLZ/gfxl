#ifndef MANAGED_HPP
#define MANAGED_HPP
namespace gfx {

    class managed {
    protected:
                              managed( video_manager* owner,
                                       size_t g_id           );
                              ~managed();
        video_manager* const  owner;
        size_t                g_id;
        friend class          video_manager;
    };

    inline managed::managed( video_manager* owner,
                            size_t g_id           ) :
                                owner( owner ),
                                g_id( g_id )          {}
                                
    inline managed::~managed() {}
}

#endif