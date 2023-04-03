#include "mixWindow.h"
#include <stdio.h>
#include <iostream>

inline int mix::core::mixWindow::get_key(int key) noexcept
{
    return glfwGetKey(_window, key);
}

void mix::core::mixWindow::set_context_as_current() noexcept
{
    glfwMakeContextCurrent(_window);
}

mix::core::mixWindow::~mixWindow()
{
}

void mix::core::mixWindow::close() noexcept
{
    glfwDestroyWindow(_window);
}

void mix::core::mixWindow::initialize() noexcept
{
    std::cout << "Creating Window" << std::endl;

    const GLFWvidmode* _mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    if (!_mode)
    {
        glfwTerminate();
        printf("Cant retrieve mode");
    }

    glfwWindowHint(GLFW_RED_BITS, _mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, _mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, _mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, _mode->refreshRate);

    _window = glfwCreateWindow(_width, _height, "GLFW: Window created", NULL, NULL);
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