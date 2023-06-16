#include "mixWindow.h"
#include <iostream>
#include <stdio.h>
#include "../library/debug.h"

int mix::core::mixWindow::get_key (int key) noexcept
{
    return glfwGetKey (_glfw_window, key);
}

vec2i mix::core::mixWindow::get_window_size () const
{
    vec2i s;
    glfwGetWindowSize (_glfw_window, &s.x, &s.y);
    return s;
}

void mix::core::mixWindow::set_window_size (const vec2i& size) const
{
    glfwSetWindowSize (_glfw_window, size.x, size.y);
}

vec2i mix::core::mixWindow::get_window_position () const
{
    vec2i s;
    glfwGetWindowPos (_glfw_window, &s.x, &s.y);
    return s;
}

void mix::core::mixWindow::set_window_position (const vec2i& size) const
{
    glfwSetWindowPos (_glfw_window, size.x, size.y);
}

void mix::core::mixWindow::get_frame_rect (vec2i& xy, vec2i zw) const
{
    glfwGetWindowFrameSize (_glfw_window, &xy.x, &xy.y, &zw.x, &zw.y);
}

void mix::core::mixWindow::set_aspect_ratio (int w, int h) const
{
    glfwSetWindowAspectRatio (_glfw_window, w, h);
}

void mix::core::mixWindow::set_icon (GLFWimage* images, int count)
{
    //assert (width == height);
    glfwSetWindowIcon (_glfw_window, count, images);
}

void mix::core::mixWindow::set_title (std::string title)
{
    glfwSetWindowTitle (_glfw_window, title.c_str());
}

void mix::core::mixWindow::maximize () const
{
    glfwMaximizeWindow (_glfw_window);
}

void mix::core::mixWindow::restore () const
{
    glfwRestoreWindow (_glfw_window);
}

GLFWwindow* mix::core::mixWindow::get_glfw_window () const noexcept
{
    return _glfw_window;
}

void mix::core::mixWindow::on_window_position_changed (int x, int y)
{
    _x = x;
    _y = y;
}

void mix::core::mixWindow::hide () const
{
    glfwHideWindow (_glfw_window);
}

void mix::core::mixWindow::show () const
{
    glfwShowWindow (_glfw_window);
}

void mix::core::mixWindow::on_window_size_changed (const vec2i& size)
{
    _width = size.x;
    _height = size.y;
}

mix::core::mixWindow::mixWindow ()
{
    _x = 0;
    _y = 0;
}

mix::core::mixWindow::~mixWindow ()
{
    if (_glfw_window != nullptr)
    {
        close ();
    }
}

void mix::core::mixWindow::close () noexcept
{
    glfwDestroyWindow (_glfw_window);
    _glfw_window = nullptr;
}

bool mix::core::mixWindow::initialize (vec2i size) noexcept
{
    auto result = true;

    std::cout << "Creating Window" << std::endl;
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, _context_version_max);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, _context_version_min);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint (GLFW_VISIBLE, GLFW_FALSE);

    glfwWindowHint (GLFW_MAXIMIZED, GLFW_FALSE);
    _width = size.x;
    _height = size.y;
  
    
    _glfw_window = glfwCreateWindow (_width, _height, "GLFW: Window created", NULL, NULL);
    if (!_glfw_window)
    {
        glfwTerminate ();
        result = false;
        FAILED_ASSERT ("Failed to initialize a window. Check if glfw was initialized!");
    }

    vec2i frame_xy;
    vec2i frame_yz{};
    get_frame_rect (frame_xy, frame_yz);
    _y = frame_xy.x;

    glfwSetWindowMonitor (_glfw_window, NULL, _x, _y, _width, _height, 0);
    glfwMakeContextCurrent (_glfw_window);
    return result;
}
