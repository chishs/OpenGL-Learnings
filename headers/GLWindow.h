#pragma once

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLWindow
{
    public:
        GLWindow();
        GLWindow(GLint windowWidth, GLint windowHeight);
        int Initialize();
        GLfloat GetBufferWidth() { return bufferWidth; }
        GLfloat GetBuffferHeight() { return bufferHeight; }
        bool ShouldClose() { return glfwWindowShouldClose(mainWindow); }
        void SwapBuffers() { glfwSwapBuffers(mainWindow); }
        ~GLWindow();
    
    private:
        GLFWwindow *mainWindow;
        GLint width, height;
        GLint bufferWidth, bufferHeight;
};