#pragma once
#include <string>
#include <GL/glew.h>

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
};