#include "mixWindow.h"
#include <stdio.h>
#include <iostream>

GLFWwindow* mix::core::mixWindow::get_glfw_window()
{
    return _window;
}

void mix::core::mixWindow::set_context_as_current()
{
    glfwMakeContextCurrent(_window);
}

mix::core::mixWindow::~mixWindow()
{

}

GLFWmonitor* mix::core::mixWindow::get_monitor()
{
    return _monitor;
}

void mix::core::mixWindow::set_fullscreen()
{
    //glfwSetWindowMonitor()
}

mix::core::mixWindow::mixWindow(unsigned int width, unsigned int height)
{
    std::cout << "Creating Window" << std::endl;

    _monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* _mode = glfwGetVideoMode(_monitor);

    if (_mode == nullptr)
    {
        printf("Cant retrieve mode");
    }

    glfwWindowHint(GLFW_RED_BITS, _mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, _mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, _mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, _mode->refreshRate);

    _width = width;
    _height = height;

    _window = glfwCreateWindow(width, height, "GLFW: Window created", NULL, NULL);
    if (!_window)
    {
        glfwTerminate();
        printf("Failed to create a window");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _context_version_max);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _context_version_min);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    set_context_as_current();

}