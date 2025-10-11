#pragma once
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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