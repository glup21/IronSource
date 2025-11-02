#pragma once
#include <string>

class GlobalConfig
{
public:
    static std::string GetDefaultVertexShaderPath() 
    {
        return "./bin/shaders/vertexShader.vert";
    }

    static std::string GetDefaultFragmentShaderPath() 
    {
        return "./bin/shaders/fragmentShaderBlinn.frag";
    }
};