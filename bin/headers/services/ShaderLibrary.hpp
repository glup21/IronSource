#pragma once
#include "headers/graphics/Shader.hpp"
#include "headers/graphics/ShaderProgram.hpp"
#include <vector>
#include <bits/stdc++.h>
#include <string>

class ShaderLibrary
{
private:
    std::map<std::pair<std::string, std::string>, std::shared_ptr<ShaderProgram>> shaderPrograms;
public:

    std::shared_ptr<ShaderProgram> GetShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
};