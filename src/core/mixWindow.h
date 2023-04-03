#pragma once
#include <GLFW/glfw3.h>

namespace mix
{
	namespace core
	{
		class mixWindow
		{
		public:

			mixWindow(unsigned int width, unsigned int height);
			~mixWindow();

			void set_context_as_current();
			GLFWwindow* get_glfw_window();
			GLFWmonitor* get_monitor();
			void set_fullscreen();
			int _width;
			int _height;

		private:
			const int _context_version_min = 4;
			const int _context_version_max = 6;
			GLFWwindow* _window;
			GLFWmonitor* _monitor;
		};
	}
}
