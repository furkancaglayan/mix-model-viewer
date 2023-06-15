#include "mixWindow.h"
#include "gtest/gtest.h"
#include <chrono>
#include <thread>

    TEST (mixWindow, window_test)
    {
        mix::core::mixWindow* window = new mix::core::mixWindow ();
        auto result = window->initialize (vec2i (1024, 768));
        ASSERT_TRUE (result);
        window->show ();

        std::this_thread::sleep_for (std::chrono::seconds (10));
        
    }
