#ifndef VERSION_HPP
#define VERSION_HPP

namespace gfx {

    class version {
    public:
                        version( unsigned int const maj_ver,
                                 unsigned int const min_ver,
                                 unsigned int sub_ver = 0   );
                        version( version const& copy );
        bool            operator==( version const& rhs );
        bool            operator!=( version const& rhs );
        bool            operator<=( version const& rhs );
        bool            operator>=( version const& rhs );
        bool            operator>( version const& rhs );
        bool            operator<( version const& rhs );
        unsigned int    maj_ver() const;
        unsigned int    min_ver() const;
        unsigned int    sub_ver() const;
    private:
        unsigned int    maj_ver_v;
        unsigned int    min_ver_v;
        unsigned int    sub_ver_v;
    };
    
    inline version::version( unsigned int maj_ver,
                             unsigned int min_ver,
                             unsigned int sub_ver ) :
                                 maj_ver_v ( maj_ver ),
                                 min_ver_v ( min_ver ),
                                 sub_ver_v ( sub_ver ) {}
                                 
    inline version::version( version const& copy )
    {
        maj_ver_v = copy.maj_ver_v;
        min_ver_v = copy.min_ver_v;
        sub_ver_v = copy.sub_ver_v;
    }
                                 
    inline bool     version::operator==( version const& rhs )
    {
        return     maj_ver_v == rhs.maj_ver_v
               and min_ver_v == rhs.min_ver_v
               and sub_ver_v == rhs.sub_ver_v;
    }
    
    inline bool     version::operator!=( version const& rhs )
    {
        return    maj_ver_v != rhs.maj_ver_v
               or min_ver_v != rhs.min_ver_v
               or sub_ver_v != rhs.sub_ver_v;
    }
    
    inline bool     version::operator<=( version const& rhs )
    {
        return     maj_ver_v <= rhs.maj_ver_v
               and min_ver_v <= rhs.min_ver_v
               and sub_ver_v <= rhs.sub_ver_v;
    }
    
    inline bool     version::operator>=( version const& rhs )
    {
        return     maj_ver_v >= rhs.maj_ver_v
               and min_ver_v >= rhs.min_ver_v
               and sub_ver_v >= rhs.sub_ver_v;
    }
    
    inline bool     version::operator<( version const& rhs )
    {
        return     maj_ver_v < rhs.maj_ver_v
               or (maj_ver_v == rhs.maj_ver_v and min_ver_v < rhs.min_ver_v)
               or (maj_ver_v == rhs.maj_ver_v and min_ver_v == rhs.min_ver_v and sub_ver_v < rhs.sub_ver_v);
    }
    
    inline bool     version::operator>( version const& rhs )
    {
        return     maj_ver_v > rhs.maj_ver_v
               or (maj_ver_v == rhs.maj_ver_v and min_ver_v > rhs.min_ver_v)
               or (maj_ver_v == rhs.maj_ver_v and min_ver_v == rhs.min_ver_v and sub_ver_v > rhs.sub_ver_v);
    }
    
    inline unsigned int     version::maj_ver() const
    { return maj_ver_v; }
    
    inline unsigned int     version::min_ver() const
    { return min_ver_v; }
    
    inline unsigned int     version::sub_ver() const
    { return sub_ver_v; }
    
    version const opengl_1_1 = version( 1, 1 );
    version const opengl_1_2 = version( 1, 2 );
    version const opengl_1_2_1 = version( 1, 2, 1 );
    version const opengl_1_3 = version( 1, 3 );
    version const opengl_1_4 = version( 1, 4 );
    version const opengl_1_5 = version( 1, 5 );
    version const opengl_2_0 = version( 2, 0 );
    version const opengl_2_1 = version( 2, 1 );
    version const opengl_3_0 = version( 3, 0 );
    version const opengl_3_1 = version( 3, 1 );
    version const opengl_3_2 = version( 3, 2 );
    version const opengl_3_3 = version( 3, 3 );
    version const opengl_4_0 = version( 4, 0 );
    version const opengl_4_1 = version( 4, 1 );
    version const opengl_4_2 = version( 4, 2 );
    version const opengl_4_3 = version( 4, 3 );
    version const opengl_4_4 = version( 4, 4 );

}



#endif