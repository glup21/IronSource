#include "headers/graphics/Texture.hpp"
#include "headers/pch.hpp"

Texture::Texture(unsigned char* data, int width, int height, int channels)
    : data(data), width(width), height(height), channels(channels)
{
    GLenum format = channels == 4 ? GL_RGBA : GL_RGB;

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glGenerateMipmap(textureId);

    // Parameters here
}

void Texture::Use(GLuint socket)
{
    glActiveTexture(socket);
    glBindTexture(GL_TEXTURE_2D, textureID);
}