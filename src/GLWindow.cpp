#include "GLWindow.h"

GLWindow::GLWindow()
{
    width = 800;
    height = 600;
}

GLWindow::GLWindow(GLint windowWidth, GLint windowHeight)
{
    width = windowWidth;
    height = windowHeight;
}

int GLWindow::Initialize()
{
        // Init GLFW
    if (!glfwInit())
    {
        printf("GLFW initialization failed!");
        glfwTerminate();

        return 1;
    }

    // Setup GLFW window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Core profile = No Backwards Compability
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Allow Forward Compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);

    if (!mainWindow)
    {
        printf("GLFW window creation failed!");
        glfwTerminate();

        return 1;
    }

    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    GLenum status = glewInit();

    if (status != GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(status));
        glfwDestroyWindow(mainWindow);
        glfwTerminate();

        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    // Setup Viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    return 0;
}

GLWindow::~GLWindow()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}