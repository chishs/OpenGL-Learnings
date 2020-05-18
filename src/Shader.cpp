#include "Shader.h"

Shader::Shader()
{
    shaderId = 0;
    uniformModel = 0;
    uniformProjection = 0;
}

void Shader::CreateFromString(const char* vertexShaderCode, const char* fragmentShaderCode)
{
    CompileShader(vertexShaderCode, fragmentShaderCode);
}

void Shader::CreateShadersFromFile(const char* vertexShaderFile, const char* fragmentShaderFile)
{
    std::string vertexShaderString = ReadFile(vertexShaderFile);
    std::string fragmentShaderString = ReadFile(fragmentShaderFile);
    
    const char* vertexShaderCode = vertexShaderString.c_str();
    const char* fragmentShaderCode = fragmentShaderString.c_str();

    CompileShader(vertexShaderCode, fragmentShaderCode);
}

std::string Shader::ReadFile(const char* file)
{
    std::string content;
    std::ifstream fileStream(file, std::ios::in);

    if (!fileStream.is_open())
    {
        fprintf(stderr, "Failed to read %s. File does not exist", file);

        return "";
    }

    std::string line = "";

    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();

    return content;
}

void Shader::CompileShader(const char* vertexShaderCode, const char* fragmentShaderCode)
{
    shaderId = glCreateProgram();

    if (!shaderId)
    {
        fprintf(stderr, "Error: %s\n", glGetError());

        return;
    }

    AddShader(shaderId, vertexShaderCode, GL_VERTEX_SHADER);
    AddShader(shaderId, fragmentShaderCode, GL_FRAGMENT_SHADER);

    GLint isSuccessful = 0;
    GLchar errorLog[1024] = { 0 };

    glLinkProgram(shaderId);
    glGetProgramiv(shaderId, GL_LINK_STATUS, &isSuccessful);

    if (!isSuccessful)
    {
        glGetProgramInfoLog(shaderId, sizeof(errorLog), NULL, errorLog);
        fprintf(stderr, "Error linking program: %s\n", errorLog);

        return;
    }

    glValidateProgram(shaderId);
    glGetProgramiv(shaderId, GL_VALIDATE_STATUS, &isSuccessful);

    if (!isSuccessful)
    {
        glGetProgramInfoLog(shaderId, sizeof(errorLog), NULL, errorLog);
        fprintf(stderr, "Error validating program: %s\n", errorLog);

        return;
    }

    uniformModel = glGetUniformLocation(shaderId, "model");
    uniformProjection = glGetUniformLocation(shaderId, "projection");
}

GLuint Shader::GetProjectionLocation()
{
    return uniformProjection;
}

GLuint Shader::GetModelLocation()
{
    return uniformModel;
}

void Shader::UseShader()
{
    glUseProgram(shaderId);
}

void Shader::ClearShader()
{
    if (shaderId != 0)
    {
        glDeleteProgram(0);
        
        shaderId = 0;
    }

    uniformModel = 0;
    uniformProjection = 0;
}

void Shader::AddShader(GLuint program, const char* shaderCode, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    const GLchar* code[1];
    code[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(shader, 1, code, codeLength);
    glCompileShader(shader);

    GLint isSuccessful = 0;
    GLchar errorLog[1024] = { 0 };

    glGetShaderiv(shader, GL_COMPILE_STATUS, &isSuccessful);

    if (!isSuccessful)
    {
        glGetShaderInfoLog(shader, sizeof(errorLog), NULL, errorLog);
        fprintf(stderr, "Error compiling shader (%d): %s\n", shaderType, errorLog);

        return;
    }

    glAttachShader(program, shader);
}

Shader::~Shader()
{
    ClearShader();
}