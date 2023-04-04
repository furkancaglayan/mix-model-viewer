#pragma once
#include <GLFW/glfw3.h>
#include "../core/mixWindow.h"
#include <memory>
namespace mix
{
	class mixEditor
	{
	public:
		bool _should_run;
		void run();
		void start();
		inline void select_monitor(int num);
	private:
		std::unique_ptr<core::mixWindow> _window;
	};
}
