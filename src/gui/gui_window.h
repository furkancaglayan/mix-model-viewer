#pragma once

#include "gui_layout.h"
#include "i_guicomponent.h"
#include <memory>
#include <string>
#include <vector>

namespace mixImGui
{
    enum class window_flags
    {
        None = 0,
        NoTitleBar = 1 << 0,
        NoResize = 1 << 1,
        NoMove = 1 << 2,
        NoScrollbar = 1 << 3,
        NoScrollWithMouse = 1 << 4,
        NoCollapse = 1 << 5,
        AlwaysAutoResize = 1 << 6,
        NoBackground = 1 << 7,
        NoSavedSettings = 1 << 8,
        NoMouseInputs = 1 << 9,
        MenuBar = 1 << 10,
        HorizontalScrollbar = 1 << 11,
        NoFocusOnAppearing = 1 << 12,
        NoBringToFrontOnFocus = 1 << 13,
        AlwaysVerticalScrollbar = 1 << 14,
        AlwaysHorizontalScrollbar = 1 << 15,
        AlwaysUseWindowPadding = 1 << 16,
        NoNavInputs = 1 << 18,
        NoNavFocus = 1 << 19,
        UnsavedDocument = 1 << 20,      
    };

    inline window_flags operator| (window_flags a, window_flags b)
    {
        return static_cast<window_flags> (static_cast<int> (a) | static_cast<int> (b));
    }
    class gui_window
    {
        public:

        virtual void render ();
        gui_window (std::string window_name, window_rect r, window_flags flags = window_flags::None);

        void disable ();
        void enable ();
        void rescale (int w, int h, int w_sizex, int w_sizey);

        void set_title (std::string s);
        protected:

        void begin ();
        void end () const;
        bool _is_open = true;
        std::string _window_name;
        window_rect _rect;
        window_flags _flags;
    };
} // namespace mixImGui
