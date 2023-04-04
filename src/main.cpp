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

	auto editor = std::make_unique<mix::mixEditor>();
	editor.get()->start();

	while (editor.get()->_should_run)
	{
		editor.get()->run();
	}
}