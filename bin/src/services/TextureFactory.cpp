#include "headers/services/TextureFactory.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::shared_ptr<Texture> TextureFactory::GetTexture(std::string texturePath)
{
    auto iterator = this->textures.find(texturePath);
    if(iterator != this->textures.end())
    {
        return iterator->second;
    }

    int width, height, channels;
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);

    auto texture = std::make_shared<Texture>(data, width, height, channels);
    return texture;
}