#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "PAROC.hpp"


struct Texture2D {
    unsigned int id;            // Id handle of OpenGL texture
    unsigned int width, height; // width and height in pixel
    unsigned int format;
    // texture configuration
    unsigned int wrapS;
    unsigned int wrapT;
    unsigned int filterMin;
    unsigned int filterMax;
    bool initialized;

    Texture2D();

    void generate(unsigned int width, unsigned int height, unsigned char* data); // generate texture from image data
    void bind(); // bind the texture as the current active texture
};



#endif // TEXTURE_HPP
