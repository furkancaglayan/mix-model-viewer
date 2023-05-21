#pragma once

#include "i_guicomponent.h"
#include <memory>
#include <string>
#include <vector>

namespace mixImGui
{
    class gui_window
    {
        public:

        void init ();
        void render ();
        gui_window () = delete;

        private:

        mixImGui::i_guicomponent* _comp;
        gui_window (mixImGui::i_guicomponent* comp);
    };
} // namespace mixImGui
