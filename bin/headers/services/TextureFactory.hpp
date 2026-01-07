#pragma once
#include "headers/graphics/Texture.hpp"
#include <bits/stdc++.h>
#include <string>


class TextureFactory
{
    std::map<std::string, std::shared_ptr<Texture>> textures;
    
public:
    TextureFactory() = default;
    
    std::shared_ptr<Texture> GetTexture(std::string texturePath);

};