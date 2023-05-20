#include "mixEditor.h"
#include <cassert>

std::unique_ptr<mix::mixEditor> mix::mixEditor::_instance = nullptr;
void window_pos_callback (GLFWwindow* window, int xpos, int ypos);
void window_close_callback (GLFWwindow* window);
void window_size_callback (GLFWwindow* window, int width, int height);

inline void mix::mixEditor::select_monitor (int index)
{
    int count;
    auto monitors = glfwGetMonitors (&count);
    assert (index < count);
    auto monitor = monitors[index];
    _window->set_monitor (monitor);
}

mix::mixEditor::mixEditor () : _active_scene{ std::make_unique<mix::scene_management::mixScene> () }, _window{ nullptr }
{
}

void mix::mixEditor::create_new ()
{
    mix::mixEditor::_instance = std::make_unique<mix::mixEditor> ();
    mix::mixEditor::_instance->start ();
}

void mix::mixEditor::run ()
{
    _active_scene->update ();
    glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    _should_run = _window->get_key (GLFW_KEY_ESCAPE) != GLFW_PRESS;
    /*
    if (_window->get_key (GLFW_KEY_F1) == GLFW_PRESS)
    {
        select_monitor (0);
    }
    else if (_window->get_key (GLFW_KEY_F2) == GLFW_PRESS)
    {
        select_monitor (1);
    }
    else if (_window->get_key (GLFW_KEY_F3) == GLFW_PRESS)
    {
        _window->set_window_mode (core::WindowMode::FullScreen);
    }
    else if (_window->get_key (GLFW_KEY_F4) == GLFW_PRESS)
    {
        _window->set_window_mode (core::WindowMode::Windowed);
    }*/

    render ();

    // Start the Dear ImGui frame
  
    test_gui.new_frame (_active_scene->get_root(), _active_scene->get_lights(), _window.get());
    glfwSwapBuffers (_window->get_glfw_window ());
    glfwPollEvents ();
}

void mix::mixEditor::render ()
{
    _active_scene->render (_rendering.get());
}

mix::core::mixWindow* mix::mixEditor::get_window () const
{
    return nullptr;
}

mix::scene_management::mixScene* mix::mixEditor::get_active_scene () const
{
    return nullptr;
}

void mix::mixEditor::start ()
{
    _window = std::make_unique<mix::core::mixWindow> ();
    _window->initialize ();
    _should_run = true;
    _rendering = std::make_unique<mix::rendering::rendering_context> ();
    _rendering->initialize ();

    glfwSetWindowPosCallback (_window->get_glfw_window (), window_pos_callback);
    glfwSetWindowCloseCallback (_window->get_glfw_window (), window_close_callback);
    glfwSetWindowSizeCallback (_window->get_glfw_window (), window_size_callback);

    test_gui.init (_window.get ());
}

void window_pos_callback (GLFWwindow* window, int xpos, int ypos)
{
    mix::mixEditor::_instance->_window->cache_pos (xpos, ypos);
}


/// <summary>
/// Can be used to clear close flag if it should not close.
/// </summary>
/// <param name="window"></param>
void window_close_callback (GLFWwindow* window)
{
}

void window_size_callback (GLFWwindow* window, int width, int height)
{
    mix::mixEditor::_instance->_window->cache_size (width, height);
}
