#pragma once
#include "ievent_callback_base.h"
#include <vector>
namespace mix
{
    namespace library
    {

        class event
        {
            public:

            event ();
            ~event ();

            void add_listener (ievent_callback_base* action);
            void remove_listener (ievent_callback_base* action);
            void dispatch ();

            private:

            std::vector<ievent_callback_base*> _actions;
        };
    } // namespace library
} // namespace mix
