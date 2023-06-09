#pragma once
#include <memory>

namespace mix
{
    namespace library
    {
        class ievent_callback_base
        {
            public:

            virtual void operator() () = 0;
        };
    } // namespace library
} // namespace mix
