#include "test_base.h"
#include <chrono>
#include <thread>
#include <string>

TEST_F (test_base, simple_window_test)
{
    mix::core::mixWindow* window = new mix::core::mixWindow ();
    auto result = window->initialize (vec2i (1024, 768));
    ASSERT_TRUE (result);
    window->show ();
    std::this_thread::sleep_for (std::chrono::seconds (2));
    window->set_title ("Title");
    std::this_thread::sleep_for (std::chrono::seconds (2));
    const vec2i size = vec2i (1600, 900);
    window->set_window_size (size);
    ASSERT_EQ (size, window->get_window_size());
    std::this_thread::sleep_for (std::chrono::seconds (1));
    const vec2i pos = vec2i (300, 300);
    window->set_window_position (pos);
    ASSERT_EQ (pos, window->get_window_position ());
    std::this_thread::sleep_for (std::chrono::seconds (1));
    delete window;
}
