#pragma once
#include <string>
#include "headers/pch.hpp"


class Shader
{
private:
    std::string code;
    GLenum shaderType;

    uint shaderId;

public:
    Shader(std::string code, GLenum shaderType);
    ~Shader() = default;

    void CompileShader();
    uint GetShaderId();
};