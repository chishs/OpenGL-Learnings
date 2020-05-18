#include "Mesh.h"
#include "Shader.h"
#include "GLWindow.h"
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

const float radianConversionFactor = M_PI / 180.0f;

GLWindow mainWindow;
std::vector<Mesh*> meshes;
std::vector<Shader> shaders;

// Vertex Shader
static const char *vShader = "shaders/shader.vert";

// Fragment Shader
static const char *fShader = "shaders/shader.frag";

void CreateObjects()
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
        0.0f, 1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
    };

    Mesh *mesh = new Mesh();
    mesh->CreateMesh(vertices, indices, 12, 12);
    meshes.push_back(mesh);

    Mesh *mesh2 = new Mesh();
    mesh2->CreateMesh(vertices, indices, 12, 12);
    meshes.push_back(mesh2);
}

void CreateShaders()
{
    Shader *shader = new Shader();
    shader->CreateShadersFromFile(vShader, fShader);
    shaders.push_back(*shader);
}

int main()
{
    mainWindow = GLWindow(800, 600);
    mainWindow.Initialize();

    CreateObjects();
    CreateShaders();

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat) mainWindow.GetBufferWidth() / (GLfloat) mainWindow.GetBuffferHeight(), 0.1f, 100.0f);

    GLuint uniformModel = 0, uniformProjection = 0;

    // Loop until window closed
    while (!mainWindow.ShouldClose())
    {
        // Get + Handle user inputs events
        glfwPollEvents();

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shaders[0].UseShader();
        uniformModel = shaders[0].GetModelLocation();
        uniformProjection = shaders[0].GetProjectionLocation();

        glm::mat4 model(1.0f);

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        
        meshes[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        meshes[1]->RenderMesh();

        glUseProgram(0);

        mainWindow.SwapBuffers();
    }

    return 0;
}