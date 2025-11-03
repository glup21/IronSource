#pragma once

class Texture
{
private:
    unsigned char* data;
    int width; 
    int height;
    int channels;

    GLuint textureId;
public:
    Texture(unsigned char* data, int width, int height, int channels);
    ~Texture() = default;

    void Use(GLuint socket);
};