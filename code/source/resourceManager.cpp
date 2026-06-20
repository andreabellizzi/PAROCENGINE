#include <string>
#include "resourceManager.hpp"
#include "logger.hpp"

#include "stb_image.h"
#include "glad/glad.h"


void ResourceManager::loadTexture(const char *file, Texture2D& texture) {
    ResourceManager::loadTexture(file, texture, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
}

void ResourceManager::loadTexture(const char *file, Texture2D& texture, unsigned int wrapS, unsigned int wrapT, unsigned int filterMin, unsigned int filterMax) {
    unsigned char* data;
    int nrChannels=0;
    //stbi_set_flip_vertically_on_load(true);
    data = stbi_load(file, (int*) &texture.width, (int*) &texture.height, &nrChannels, 0);
    if (data && nrChannels >= 0 && nrChannels <= 4) {
        switch (nrChannels) {
            case 1:
                texture.format = GL_RED;
                break;
            case 2:
                texture.format = GL_RG;
                break;
            case 3:
                texture.format = GL_RGB;
                break;
            case 4:
                texture.format = GL_RGBA;
                break;
            default:
                LOG_ERROR("error, nrChannels equal to 0")
                break;
        }

        // remember to bind the texture before setting parameters and uploading data, otherwise it will affect the currently bound texture
        texture.bind();
        texture.filterMax = filterMax;
        texture.filterMin = filterMin;
        texture.wrapS = wrapS;
        texture.wrapT = wrapT;
        texture.generate(texture.width, texture.height, data);
        glBindTexture(GL_TEXTURE_2D, 0); // unbind texture to avoid accidental modification
    }
    else {
        LOG_ERROR(std::string("failed to load texture") + file);
        throw std::invalid_argument(std::string("Failed loading texture: ")+file);
    }

    stbi_image_free(data);
}
