#include "mixEditor.h"
#include <cassert>

std::unique_ptr<mix::mixEditor> mix::mixEditor::_instance = nullptr;
void window_pos_callback(GLFWwindow* window, int xpos, int ypos);
void window_close_callback(GLFWwindow* window);
void window_size_callback(GLFWwindow* window, int width, int height);

inline void mix::mixEditor::select_monitor(int index)
{
	int count;
	auto monitors = glfwGetMonitors(&count);
	assert(index < count);
	auto monitor = monitors[index];
	_window->set_monitor(monitor);
}

void mix::mixEditor::create_new()
{
	mix::mixEditor::_instance = std::make_unique<mix::mixEditor>();
	mix::mixEditor::_instance->start();
}

void mix::mixEditor::run() 
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(_window->get_glfw_window());
	glfwPollEvents();

	_should_run = _window->get_key(GLFW_KEY_ESCAPE) != GLFW_PRESS;

	if (_window->get_key(GLFW_KEY_F1) == GLFW_PRESS)
	{
		select_monitor(0);
	}
	else if (_window->get_key(GLFW_KEY_F2) == GLFW_PRESS)
	{
		select_monitor(1);
	}
	else if (_window->get_key(GLFW_KEY_F3) == GLFW_PRESS)
	{
		_window->set_window_mode(core::WindowMode::FullScreen);
	}
	else if (_window->get_key(GLFW_KEY_F4) == GLFW_PRESS)
	{
		_window->set_window_mode(core::WindowMode::Windowed);
	}
}

void mix::mixEditor::start()
{
	_window = std::make_unique<mix::core::mixWindow>(1024, 768);
	_window->initialize();
	_should_run = true;

	glfwSetWindowPosCallback(_window->get_glfw_window(), window_pos_callback);
	glfwSetWindowCloseCallback(_window->get_glfw_window(), window_close_callback);
	glfwSetWindowSizeCallback(_window->get_glfw_window(), window_size_callback);
}

void window_pos_callback(GLFWwindow* window, int xpos, int ypos)
{
	mix::mixEditor::_instance->_window->cache_pos(xpos, ypos);
}


/// <summary>
/// Can be used to clear close flag if it should not close.
/// </summary>
/// <param name="window"></param>
void window_close_callback(GLFWwindow* window)
{

}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	mix::mixEditor::_instance->_window->cache_size(width, height);
}



