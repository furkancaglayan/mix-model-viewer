#pragma once
#include "ievent_callback_base.h"
#include <memory>

namespace mix
{
    namespace library
    {

        /*
        template <typename T> class event_callback : public ievent_callback_base
        {
            public:

            event_callback (T* instance, void (T::*function) ())
            {
                _instance = instance;
                _function = function;
            }

            void operator() () override
            {
                (_instance->*_function) ();
            }

            private:

            void (T::*_function) ();
            T* _instance;
        };
        */

        template <class T, class U> class event_callback : public ievent_callback_base_with_args<U>
        {
            public:

            event_callback (T* instance, void (T::*function) (U*))
            {
                _instance = instance;
                _function = function;
            }

            void operator() (U* obj) override
            {
                (_instance->*_function) (obj);
            }

            private:

            void (T::*_function) (U*);
            T* _instance;
        };
    } // namespace library
} // namespace mix
