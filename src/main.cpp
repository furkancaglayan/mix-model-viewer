#include <iostream>
#include <GL/glew.h>
#include "core/mixWindow.h"

int main() 
{
	GLenum err;

	if (!glfwInit())
	{
		std::cout << "GLFW INIT ERROR!";
	}
	glewExperimental = true;
	mix::core::mixWindow* window = new mix::core::mixWindow(1024, 768);

	if ((err = glewInit()) != GLEW_OK)
	{
		std::cout << glewGetErrorString(err) << std::endl;
	}

	while (glfwGetKey(window->get_glfw_window(), GLFW_KEY_ESCAPE) != GLFW_PRESS) 
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(window->get_glfw_window());
		glfwPollEvents();
	}
}