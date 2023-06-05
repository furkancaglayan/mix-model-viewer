#pragma once
#include "../core/mixWindow.h"
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
namespace mix
{
    namespace containers
    {
        class frame_buffer
        {
            public:

            frame_buffer (int w, int h);
            ~frame_buffer ();

            void bind () const;

            void unbind () const;
            void rescale (int w, int h) const;

            unsigned get_render_texture () const;
            private:

            void initialize (int w, int h);

            unsigned _fbo;
            unsigned _render_texture;
            unsigned _render_buffer;
        };
    } // namespace containers
} // namespace mix
