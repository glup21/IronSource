#pragma once
#include "headers/graphics/Shader.hpp"
#include <vector>

class ShaderProgram
{
private:
    std::shared_ptr<Shader> vertexShader;
    std::shared_ptr<Shader> fragmentShader;
public:


};