#include "texture.hpp"
#include <glad/glad.h>

Texture2D::Texture2D() {
    glGenTextures(1, &this->id);
    initialized = false;
    // apply default configuration
    this->format = GL_RGB;
    this->filterMax = GL_LINEAR;
    this->filterMin = GL_LINEAR;
    this->wrapS = GL_REPEAT;
    this->wrapT = GL_REPEAT;
}

void Texture2D::generate(unsigned int width, unsigned int height, unsigned char* data) {
    glBindTexture(GL_TEXTURE_2D, this->id);

    //Apply default parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    //glGenerateMipmap(GL_TEXTURE_2D); //generate mipmap only if a filter that sample from mipmap is used
    glBindTexture(GL_TEXTURE_2D, 0); // unbind texture to avoid accidental modification
    initialized = true;
}

void Texture2D::bind() {
    glBindTexture(GL_TEXTURE_2D, this->id);
}