#pragma once
#include "headers/graphics/Shader.hpp"
#include "headers/graphics/ShaderProgram.hpp"
#include "headers/graphics/Light.hpp"
#include <vector>
#include <bits/stdc++.h>
#include <string>

class ShaderLibrary
{
private:
    std::map<std::pair<std::string, std::string>, std::shared_ptr<ShaderProgram>> shaderPrograms;
    std::map<std::string, std::shared_ptr<Shader>> shaders;

    std::shared_ptr<Shader> GetShader(std::string shaderPath, GLenum shaderType);
public:
    ShaderLibrary() = default;

    std::shared_ptr<ShaderProgram> GetShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
    void RegisterCamera(Camera* camera);
    void RegisterLight(Light* light);

    void ResetShaderPrograms();
};