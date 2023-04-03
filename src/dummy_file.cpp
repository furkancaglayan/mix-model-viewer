#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>

int main()
{
	if (!glfwInit())
	{
		std::cout << "GLFW INIT ERROR!";
	}
	glewExperimental = true;
	GLint err;
	if ((err = glewInit()) != GLEW_OK)
	{
		std::cout << glewGetErrorString(err) << std::endl;
	}
}