#pragma once

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader
{
    public:
        Shader();
        void CreateFromString(const char* vertexShaderCode, const char* fragmentShaderCode);
        void CreateShadersFromFile(const char* vertexShaderFile, const char* fragmentShaderFile);
        std::string ReadFile(const char* file);
        GLuint GetProjectionLocation();
        GLuint GetModelLocation();
        void UseShader();
        void ClearShader();
        ~Shader();
    
    private:
        GLuint shaderId, uniformProjection, uniformModel;

        void CompileShader(const char* vertexShaderCode, const char* fragmentShaderCode);
        void AddShader(GLuint program, const char* code, GLenum shaderType);
};
