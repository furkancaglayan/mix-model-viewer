#include "mixEditor.h"
#include <cassert>
#include <iostream>

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

void mix::mixEditor::init_render_buffers ()
{
    auto size = _window->get_window_size ();
    _frame_buffer = std::make_unique<mix::containers::frame_buffer> (static_cast<int> (size.x), static_cast<int> (size.y));
}

unsigned mix::mixEditor::get_rendered_texture () const
{
    return _frame_buffer->get_render_texture ();
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
    _should_run = _window->get_key (GLFW_KEY_ESCAPE) != GLFW_PRESS;
}

void mix::mixEditor::render ()
{
    _frame_buffer->bind ();

    glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    _active_scene->render (_rendering.get ());
    glBindVertexArray (0);

    _frame_buffer->unbind ();

    glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    gui_pass ();
    glfwSwapBuffers (_window->get_glfw_window ());
    glfwPollEvents ();
    glBindVertexArray (0);
}

mix::core::mixWindow* mix::mixEditor::get_window () const
{
    return _window.get ();
}

mix::scene_management::mixScene* mix::mixEditor::get_active_scene () const
{
    return _active_scene.get ();
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

    mixImGui::mixGui::init (_window->get_glfw_window ());


    auto w_size = _window->get_window_size ();

    mix::editor::windows::scene_window::initialize (w_size);
    mix::editor::windows::hierarchy_window::initialize (w_size);
}

void mix::mixEditor::on_window_size_changed (int w, int h)
{
    _window->on_window_size_changed (w, h);

    vec2 w_size = _window->get_window_size ();

    mixImGui::mixGui::on_window_size_changed (w, h, static_cast<int> (w_size.x), static_cast<int> (w_size.y));
    glViewport (0, 0, w, h);
    _frame_buffer->rescale (w, h);
}

void mix::mixEditor::gui_pass ()
{
    mixImGui::mixGui::render (_frame_buffer.get ());
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
    mix::mixEditor::_instance->on_window_size_changed (width, height);
}
