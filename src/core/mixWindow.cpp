#include "mixWindow.h"
#include <iostream>
#include <stdio.h>

int mix::core::mixWindow::get_key (int key) noexcept
{
    return glfwGetKey (_glfw_window, key);
}

void mix::core::mixWindow::set_window_mode (WindowMode mode)
{
    _mode = mode;
    if (mode == WindowMode::Windowed)
    {
        glfwSetWindowMonitor (_glfw_window, NULL, _x, _y, _width, _height, 0);
    }
    else if (mode == WindowMode::FullScreen)
    {
        const GLFWvidmode* _mode = glfwGetVideoMode (_monitor);
        glfwSetWindowMonitor (_glfw_window, _monitor, 0, 0, _mode->width,
                              _mode->height, _mode->refreshRate);
    }
}

void mix::core::mixWindow::set_monitor (GLFWmonitor* monitor)
{
    if (_mode == WindowMode::FullScreen)
    {
        _monitor = monitor;
        const GLFWvidmode* mode = glfwGetVideoMode (_monitor);
        if (!mode)
        {
            glfwTerminate ();
            printf ("Cant retrieve mode");
        }

        glfwWindowHint (GLFW_RED_BITS, mode->redBits);
        glfwWindowHint (GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint (GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint (GLFW_REFRESH_RATE, mode->refreshRate);

        glfwSetWindowMonitor (_glfw_window, monitor, 0, 0, mode->width,
                              mode->height, mode->refreshRate);
    }
    else if (_mode == WindowMode::Windowed)
    {
        glfwSetWindowMonitor (_glfw_window, NULL, _x, _y, _width, _height, 0);
    }
}

GLFWwindow* mix::core::mixWindow::get_glfw_window () const noexcept
{
    return _glfw_window;
}

void mix::core::mixWindow::set_context_as_current () noexcept
{
    glfwMakeContextCurrent (_glfw_window);
}

mix::core::mixWindow::~mixWindow ()
{
}

inline void mix::core::mixWindow::close () noexcept
{
    glfwDestroyWindow (_glfw_window);
}

void mix::core::mixWindow::initialize () noexcept
{
    std::cout << "Creating Window" << std::endl;


    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, _context_version_max);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, _context_version_min);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _glfw_window = glfwCreateWindow (_width, _height, "GLFW: Window created", NULL, NULL);
    if (!_glfw_window)
    {
        glfwTerminate ();
        printf ("Failed to create a window");
    }
    set_monitor (glfwGetPrimaryMonitor ());

    set_context_as_current ();
}
