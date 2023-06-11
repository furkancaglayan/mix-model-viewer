#pragma once

#include "../math/vec.h"
#include "gui_layout.h"
#include "i_guielement.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace mixImGui
{
    /*
    enum class window_binds
    {
        horizontal_bind,
        vertical_bind
    };
    */
    enum class window_positioning
    {
        flexible,
        fixed
    };

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

    inline window_flags operator& (window_flags a, window_flags b)
    {
        return static_cast<window_flags> (static_cast<int> (a) & static_cast<int> (b));
    }

    inline window_flags operator~(window_flags a)
    {
        return static_cast<window_flags> (~static_cast<int> (a));
    }

    class gui_window
    {
        public:

        gui_window (std::string window_name, window_rect r, window_flags flags = window_flags::None);

        virtual void render ();

        void disable ();
        void enable ();
        virtual void on_editor_window_size_changed (const vec2i& size);
        void set_title (std::string s);
        //std::vector<gui_window*> get_window_binds (window_binds bind) const;

        //void bind_with_window (gui_window* other, window_binds bind);
        void set_contrainsts (window_rect constraints);
        void clear_constraints ();

        void set_positioning (window_positioning wp);

        protected:

        //std::map<window_binds, std::vector<gui_window*>> _window_binds;
        void begin ();
        void end () const;
        void rescale (const vec2i& size);
        void set_position (const vec2i& pos);
        vec2i get_position () const;
        vec2i get_size () const;
        virtual void on_editor_window_size_changed_impl (const vec2i& size) = 0;
        virtual void on_window_resized (const vec2i& old_size, const vec2i& new_size);

        bool _is_open = true;
        std::string _window_name;
        window_rect _rect, _constraints;

        window_flags get_flags () const;
        private:

        window_flags _flags;
        window_positioning _positioning = window_positioning::flexible;

        bool _has_constraints = false;
    };
} // namespace mixImGui
