#include <iostream>
#include <GL/glew.h>
#include "core/mixWindow.h"
#include "editor/mixEditor.h"
#include <memory>

int main() 
{
	GLenum err;

	if (!glfwInit())
	{
		std::cout << "GLFW INIT ERROR!";
	}
	glewExperimental = true;

	if ((err = glewInit()) != GLEW_OK)
	{
		std::cout << glewGetErrorString(err) << std::endl;
	}

	mix::mixEditor::create_new();
	while (mix::mixEditor::_instance->_should_run)
	{
		mix::mixEditor::_instance->run();
	}
}