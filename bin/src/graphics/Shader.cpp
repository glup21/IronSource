#include "headers/graphics/Shader.hpp"
#include "spdlog/spdlog.h"
#include <GLFW/glfw3.h>  

Shader::Shader(std::string code, GLenum shaderType)
{
    this->code = code;
    this->shaderType = shaderType;
}

void Shader::CompileShader()
{
    spdlog::info("Starting shader compilation");
    this->shaderId = glCreateShader(shaderType);

    const char* src = this->code.c_str();
    glShaderSource(this->shaderId, 1, &src, NULL); 

    glCompileShader(this->shaderId);

    int success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
        spdlog::critical("Failed to compile shader: {}", shaderType);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

uint Shader::GetShaderId()
{
    return this->shaderId;
}