#ifndef CHECK_ERROR_HPP
#define CHECK_ERROR_HPP

#include <iostream>
#include "gl_core_3_3.hpp"

inline
/**
 * \fn void checkGLError( char const* codetag )
 * \brief Digest OpenGL error state and print to standard output.
 * Intended for debug and development use. 
 * \param codeTag A string to indicate context from the calling code
 * \todo Make this suitable for use in error logging.
 */
void checkGLError( char const* codeTag ) {
    GLuint errorStatus = gl::GetError();
    if( errorStatus != gl::NO_ERROR_ ){
        std::cout << "error at " << codeTag << ": " << errorStatus << '\n';

        switch(errorStatus){

            case gl::INVALID_ENUM:
                std::cout << "GL_INVALID_ENUM" << std::endl;
                break;
            case gl::INVALID_VALUE:
                std::cout << "GL_INVALID_VALUE" << std::endl;
                break;
            case gl::INVALID_OPERATION:
                std::cout << "GL_INVALID_OPERATION" << std::endl;
                break;
            case gl::OUT_OF_MEMORY:
                std::cout << "GL_OUT_OF_MEMORY" << std::endl;
                break;
            case gl::TABLE_TOO_LARGE:
                std::cout << "GL_TABLE_TOO_LARGE" << std::endl;
                break;
            case gl::INVALID_FRAMEBUFFER_OPERATION:
                std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
                break;
            default:
                std::cout << "Other Error...wait, what?" << std::endl;
                break;
        }
    }
}

#endif
