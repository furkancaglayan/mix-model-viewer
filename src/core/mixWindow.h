#pragma once
#include <GLFW/glfw3.h>
#include <cstdint>

namespace mix
{
	namespace core
	{
		enum class WindowMode: std::uint8_t
		{
			Windowed,
			FullScreen
		};

		class mixWindow
		{
		public:

			mixWindow() = delete;
			mixWindow(GLuint width, GLuint height) : _width{ width }, _height{ height }
			{
			}
			~mixWindow();

			void set_context_as_current() noexcept;
			void initialize() noexcept;
			inline void close() noexcept;
			inline void set_size(GLuint width, GLuint height) noexcept;
			inline int get_key(int key) noexcept;
			inline void set_window_mode(WindowMode mode);
			void set_monitor(GLFWmonitor* monitor);

			GLFWwindow* get_glfw_window() const noexcept;
			static constexpr int _context_version_min = 3;
			static constexpr int _context_version_max = 3;

		private:
			GLFWwindow* _glfw_window = nullptr;
			GLFWmonitor* _monitor = nullptr;

			WindowMode _mode = WindowMode::Windowed;
			GLuint _width;
			GLuint _height;
		};
	}
}
