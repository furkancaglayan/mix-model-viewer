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
			using uint = unsigned int;
		public:

			mixWindow(uint width, uint height) : _width{ width }, _height{ height }, _x{ 100 }, _y{ 100 }
			{
			}
			~mixWindow();

			void set_context_as_current() noexcept;
			void initialize() noexcept;
			inline void close() noexcept;
			int get_key(int key) noexcept;
			void set_window_mode(WindowMode mode);
			void set_monitor(GLFWmonitor* monitor);

			GLFWwindow* get_glfw_window() const noexcept;
			static constexpr int _context_version_min = 3;
			static constexpr int _context_version_max = 3;

			void cache_pos(int x, int y) 
			{
				if (_mode == WindowMode::Windowed)
				{
					_x = x;
					_y = y;
				}
			}

			void cache_size(int w, int h)
			{
				if (_mode == WindowMode::Windowed)
				{
					_width = w;
					_height = h;
				}
			}

		private:
			GLFWwindow* _glfw_window = nullptr;
			GLFWmonitor* _monitor = nullptr;

			WindowMode _mode = WindowMode::Windowed;

			//TODO: pack into a struct
			uint _width;
			uint _height;
			uint _x;
			uint _y;
		};
	}
}
