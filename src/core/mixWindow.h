#pragma once
#include "../platform/typedefs.h"
#include <cstdint>
#include "../math/vec.h"

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

			mixWindow ();
			~mixWindow();

			void initialize() noexcept;
			inline void close() noexcept;
			int get_key(int key) noexcept;
			void set_window_mode(WindowMode mode);
			void set_monitor(GLFWmonitor* monitor);

			vec2 get_window_size () const;

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

			void on_window_size_changed (const vec2i& size);

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
