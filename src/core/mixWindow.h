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
				void close() noexcept;
				inline int get_key(int key) noexcept;

				static constexpr int _context_version_min = 4;
				static constexpr int _context_version_max = 6;

			private:
				GLFWwindow* _window = nullptr;
				GLuint _width;
				GLuint _height;
		};
	}
}
