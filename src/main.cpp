#include <iostream>
#include <GL/glew.h>
#include "core/mixWindow.h"
#include <memory>

int main() 
{
	GLenum err;

	if (!glfwInit())
	{
		std::cout << "GLFW INIT ERROR!";
	}
	glewExperimental = true;
	
	auto window = std::make_unique<mix::core::mixWindow>(1024, 768);
	window.get()->initialize();

	if ((err = glewInit()) != GLEW_OK)
	{
		std::cout << glewGetErrorString(err) << std::endl;
	}

	while (window.get()->get_key(GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glfwSwapBuffers(window->get_glfw_window());
		glfwPollEvents();
	}
}