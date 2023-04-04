#include "mixEditor.h"
#include <cassert>
#include <GLFW/glfw3.h>

inline void mix::mixEditor::select_monitor(int index)
{
	int count;
	auto monitors = glfwGetMonitors(&count);
	assert(index < count);
	auto monitor = monitors[index];
	_window->set_monitor(monitor);
}

void mix::mixEditor::run() 
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(_window->get_glfw_window());
	glfwPollEvents();

	//_should_run = _window.get()->get_key(static_cast<int>(GLFW_KEY_ESCAPE)) != GLFW_PRESS;
}

void mix::mixEditor::start()
{
	_window = std::make_unique<mix::core::mixWindow>(1024, 768);
	_window.get()->initialize();
	_should_run = true;
}

