#pragma once
#include <gtest/gtest.h>
#include "../core/mixWindow.h"
namespace
{
	class test_base : public testing::Test
    {
        protected:

        void SetUp () override
        {
            EXPECT_TRUE (glfwInit ());
        }

        void TearDown () override
        {
            glfwTerminate ();
        }
    };
}