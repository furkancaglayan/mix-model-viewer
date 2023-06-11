#pragma once
#include "../platform/typedefs.h"
#include <cstdint>
#include "../math/vec.h"

namespace mix
{
	namespace core
	{
		class mixWindow
		{
			using uint = unsigned int;
		public:

			mixWindow ();
			~mixWindow();

			void initialize (vec2i size) noexcept;
			inline void close() noexcept;
			int get_key(int key) noexcept;

			vec2 get_window_size () const;
            void set_window_size (const vec2i& size) const;
            void get_frame_rect (vec2i& xy, vec2i zw) const;
            void set_aspect_ratio (int w, int h) const;
            void set_icon (GLFWimage* images, int count);
            void set_title (std::string title);

			void maximize () const;
            void restore () const;

            GLFWwindow* get_glfw_window () const noexcept;
			static constexpr int _context_version_min = 3;
			static constexpr int _context_version_max = 3;

			void on_window_position_changed (int x, int y);

			void hide () const;
            void show () const;
            void on_window_size_changed (const vec2i& size);

		private:
			GLFWwindow* _glfw_window = nullptr;
			GLFWmonitor* _monitor = nullptr;

			//TODO: pack into a struct
			uint _width;
			uint _height;
			uint _x;
			uint _y;
		};
	}
}
