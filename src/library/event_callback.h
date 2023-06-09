#pragma once
#include <memory>
#include "ievent_callback_base.h"

namespace mix
{
    namespace library
    {

        template <typename T> class ievent_callback_base : public ievent_callback_base
        {
            public:

            ievent_callback_base (T* instance, void (T::*function) ())
            {
                _callback = std::unique_ptr (instance);
                _function = function;
            }

            void operator() () override
            {
                (_callback->*_function) ();
            }

            private:

            void (T::*_function) ();
            std::unique_ptr<T> _callback;
        };
    } // namespace core
} // namespace mix
