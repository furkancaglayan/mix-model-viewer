#include <iostream>
#include <GL/glew.h>
#include <memory>
#include <imgui.h>
#include "editor/mixEditor.h"
#include <stb_image.h>

int main() 
{
	int width, height, channels;
	     unsigned char* img = stbi_load("sky.jpg", &width, &height, &channels, 0);
	     if (img == NULL) {
		        printf("Error in loading the image\n");
		        exit(1);
		
	}
	printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);

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