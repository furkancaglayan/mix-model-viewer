#pragma once
#include "ievent_callback_base.h"
#include <memory>

namespace mix
{
    namespace library
    {
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

        template <class T, class U> class event_callback_args : public ievent_callback_base_with_args<U>
        {
            public:

            void operator() (U* obj) override
            {
                (_instance->*_function) (obj);
            }

            static event_callback_args<T, U>* create_callback (T* instance, void (T::*function) (U*))
            {
                return new event_callback_args (instance, function);
            }
            private:

            event_callback_args (T* instance, void (T::*function) (U*))
            {
                _instance = instance;
                _function = function;
            }

            void (T::*_function) (U*);
            T* _instance;
        };
    } // namespace library
} // namespace mix
