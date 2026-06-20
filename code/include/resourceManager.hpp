#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP
#include "texture.hpp"

struct ResourceManager {

    static void loadTexture(const char* file, Texture2D& texture);
    static void loadTexture(const char* file, Texture2D& texture, unsigned int wrapS, unsigned int wrapT, unsigned int filterMin, unsigned int filterMax);

};

#endif