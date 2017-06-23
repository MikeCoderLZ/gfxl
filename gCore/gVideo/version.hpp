#ifndef VERSION_HPP
#define VERSION_HPP

namespace gfx {

    /**
     * \class gfx::version version.hpp "gCore/gVideo/version.hpp"
     * \brief Class for expressing, storing, and comparing library versions.
     * Specifically for OpenGL version checks, but can be used for any library.
     * Appropriate operators are overloaded so that version numbers can be
     * compared naturally in code. There is no default constructor; all
     * version objects must pertain to a specific version number.
     */
    class version {
    public:
                        version( unsigned int const maj_ver,
                                 unsigned int const min_ver,
                                 unsigned int sub_ver = 0   );
                        version( version const& copy );
        bool            operator==( version const& rhs ) const;
        bool            operator!=( version const& rhs ) const;
        bool            operator<=( version const& rhs ) const;
        bool            operator>=( version const& rhs ) const;
        bool            operator>( version const& rhs ) const;
        bool            operator<( version const& rhs ) const;
        unsigned int    maj_ver() const;
        unsigned int    min_ver() const;
        unsigned int    sub_ver() const;
    private:
        unsigned int    maj_ver_v;
        unsigned int    min_ver_v;
        unsigned int    sub_ver_v;
    };
    /**
     * \brief Construct a new version object.
     * Explicit version numbers are required, but the sub version number has
     * a default value of 0.
     */
    inline version::version( unsigned int maj_ver,
                             unsigned int min_ver,
                             unsigned int sub_ver ) :
                                 maj_ver_v ( maj_ver ),
                                 min_ver_v ( min_ver ),
                                 sub_ver_v ( sub_ver ) {}
    /**
     * \brief Copy constructor for version objects.
     */
    inline version::version( version const& copy )
    {
        maj_ver_v = copy.maj_ver_v;
        min_ver_v = copy.min_ver_v;
        sub_ver_v = copy.sub_ver_v;
    }
    /**
     * \brief Test if the verion objects have identical version numbers.
     */
    inline bool     version::operator==( version const& rhs ) const
    {
        return     maj_ver_v == rhs.maj_ver_v
               and min_ver_v == rhs.min_ver_v
               and sub_ver_v == rhs.sub_ver_v;
    }
    /**
     * \brief Test if the verion objects do not have identical version numbers.
     */
    inline bool     version::operator!=( version const& rhs ) const
    {
        return    maj_ver_v != rhs.maj_ver_v
               or min_ver_v != rhs.min_ver_v
               or sub_ver_v != rhs.sub_ver_v;
    }
    /**
     * \brief Test if the first version object is a previous or the same
     * version number as the second.
     */
    inline bool     version::operator<=( version const& rhs ) const
    {
        return     maj_ver_v <= rhs.maj_ver_v
               and min_ver_v <= rhs.min_ver_v
               and sub_ver_v <= rhs.sub_ver_v;
    }
    /**
     * \brief Test if the first version object is a subsequent or the same
     * version number as the second.
     */
    inline bool     version::operator>=( version const& rhs ) const
    {
        return     maj_ver_v >= rhs.maj_ver_v
               and min_ver_v >= rhs.min_ver_v
               and sub_ver_v >= rhs.sub_ver_v;
    }
    /**
     * \brief Test if the first version object is a previous version number
     * compared to the second.
     */
    inline bool     version::operator<( version const& rhs ) const
    {
        return     maj_ver_v < rhs.maj_ver_v
               or (maj_ver_v == rhs.maj_ver_v and min_ver_v < rhs.min_ver_v)
               or (maj_ver_v == rhs.maj_ver_v and min_ver_v == rhs.min_ver_v and sub_ver_v < rhs.sub_ver_v);
    }
    /**
     * \brief Test if the first version object is a subsequent version number
     * compared to the second.
     */
    inline bool     version::operator>( version const& rhs ) const
    {
        return     maj_ver_v > rhs.maj_ver_v
               or (maj_ver_v == rhs.maj_ver_v and min_ver_v > rhs.min_ver_v)
               or (maj_ver_v == rhs.maj_ver_v and min_ver_v == rhs.min_ver_v and sub_ver_v > rhs.sub_ver_v);
    }
    /**
     * \brief Return the major version number.
     */
    inline unsigned int     version::maj_ver() const
    { return maj_ver_v; }
    /**
     * \brief Return the minor version number.
     */
    inline unsigned int     version::min_ver() const
    { return min_ver_v; }
    /**
     * \brief Return the subversion number.
     */
    inline unsigned int     version::sub_ver() const
    { return sub_ver_v; }
    /** \var gfx::version const opengl_1_1
     * Represents OpenGL version 1.1, the default version supplied by Windows. */
    version const opengl_1_1 = version( 1, 1 );
    /** \var gfx::version const opengl_1_2
     * Represents OpenGL version 1.2. */
    version const opengl_1_2 = version( 1, 2 );
    /** \var gfx::version const opengl_1_2_1
     * Represents OpenGL version 1.2_1. */
    version const opengl_1_2_1 = version( 1, 2, 1 );
    /** \var gfx::version const opengl_1_3
     * Represents OpenGL version 1.3. */
    version const opengl_1_3 = version( 1, 3 );
    /** \var gfx::version const opengl_1_4
     * Represents OpenGL version 1.4, the default version supplied by
     * GNU/Linux distros. */
    version const opengl_1_4 = version( 1, 4 );
    /** \var gfx::version const opengl_1_5
     * Represents OpenGL version 1.5. */
    version const opengl_1_5 = version( 1, 5 );
    /** \var gfx::version const opengl_2_0
     * Represents OpenGL version 2.0. */
    version const opengl_2_0 = version( 2, 0 );
    /** \var gfx::version const opengl_2_1
     * Represents OpenGL version 2.1. */
    version const opengl_2_1 = version( 2, 1 );
    /** \var gfx::version const opengl_3_0
     * Represents OpenGL version 3.0. */
    version const opengl_3_0 = version( 3, 0 );
    /** \var gfx::version const opengl_3_1
     * Represents OpenGL version 3.1. */
    version const opengl_3_1 = version( 3, 1 );
    /** \var gfx::version const opengl_3_2
     * Represents OpenGL version 3.2. */
    version const opengl_3_2 = version( 3, 2 );
    /** \var gfx::version const opengl_3_3
     * Represents OpenGL version 3.3. */
    version const opengl_3_3 = version( 3, 3 );
    /** \var gfx::version const opengl_4_0
     * Represents OpenGL version 4.0. */
    version const opengl_4_0 = version( 4, 0 );
    /** \var gfx::version const opengl_4_1
     * Represents OpenGL version 4.1. */
    version const opengl_4_1 = version( 4, 1 );
    /** \var gfx::version const opengl_4_2
     * Represents OpenGL version 4.2. */
    version const opengl_4_2 = version( 4, 2 )
    /** \var gfx::version const opengl_4_3
     * Represents OpenGL version 4.3. */
    version const opengl_4_3 = version( 4, 3 );
    /** \var gfx::version const opengl_4_4
     * Represents OpenGL version 4.4. */
    version const opengl_4_4 = version( 4, 4 );

}



#endif