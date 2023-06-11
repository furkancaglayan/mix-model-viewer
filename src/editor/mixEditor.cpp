#include "mixEditor.h"
#include <cassert>
#include <iostream>
#include "windows/project_window.h"

std::unique_ptr<mix::mixEditor> mix::mixEditor::_instance = nullptr;
void window_pos_callback (GLFWwindow* window, int xpos, int ypos);
void window_close_callback (GLFWwindow* window);
void window_size_callback (GLFWwindow* window, int width, int height);

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

void mix::mixEditor::create_new (editor_config config)
{
    mix::mixEditor::_instance = std::make_unique<mix::mixEditor> ();
    mix::mixEditor::_instance->start (config);
}

void mix::mixEditor::initialize_asset_manager (std::string path)
{
    mix::mixEditor::_instance->_asset_manager = std::make_unique<mix::assetsystem::mixAsset_manager> (path);
}

void mix::mixEditor::initialize_gui ()
{
    assert (mix::mixEditor::_instance->_asset_manager);
    auto _window = mix::mixEditor::_instance->_window.get();
    mixImGui::mixGui::init (_window->get_glfw_window ());
    mixImGui::mixGui::add_font (mix::mixEditor::_instance->_asset_manager->get_asset_with_full_name<mix::assetsystem::mixFont> ("Raleway-Medium.ttf").get(), true);

    auto w_size = _window->get_window_size ();

    mix::editor::windows::scene_window::initialize (w_size);
    mix::editor::windows::hierarchy_window::initialize (w_size);
    mix::editor::windows::shortcuts_window::initialize (w_size);
    mix::editor::windows::project_window::initialize (w_size);
}

mix::assetsystem::mixAsset_manager* mix::mixEditor::get_asset_manager ()
{
    return mix::mixEditor::_instance->_asset_manager.get ();
}

void mix::mixEditor::run ()
{
    _active_scene->update ();
    _should_run = _window->get_key (GLFW_KEY_ESCAPE) != GLFW_PRESS;
}

void mix::mixEditor::render ()
{
    _frame_buffer->bind ();

    glClearColor (0.9f, 0.9f, 0.9f, 1.0f);
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

void mix::mixEditor::start (editor_config config)
{
    _window = std::make_unique<mix::core::mixWindow> ();
    _window->initialize (vec2i(1024, 768));
    _window->hide ();
    _window->set_title ("Mix Model Viewer");

    _should_run = true;
    _rendering = std::make_unique<mix::rendering::rendering_context> ();
    _rendering->initialize ();

    glfwSetWindowPosCallback (_window->get_glfw_window (), window_pos_callback);
    glfwSetWindowCloseCallback (_window->get_glfw_window (), window_close_callback);
    glfwSetWindowSizeCallback (_window->get_glfw_window (), window_size_callback);
}

void mix::mixEditor::on_window_size_changed (const vec2i& size)
{
    _window->on_window_size_changed (size);
    mixImGui::mixGui::on_editor_window_size_changed (size);
    glViewport (0, 0, size.x, size.y);
    _frame_buffer->rescale (size.x, size.y);
}

void mix::mixEditor::gui_pass ()
{
    mixImGui::mixGui::render (_frame_buffer.get ());
}

void window_pos_callback (GLFWwindow* window, int xpos, int ypos)
{
    mix::mixEditor::_instance->get_window ()->on_window_position_changed (xpos, ypos);
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
    //This is called when the window is iconified.
    if (width != 0 && height != 0)
    {
        mix::mixEditor::_instance->on_window_size_changed (vec2i (width, height));
    }
}
