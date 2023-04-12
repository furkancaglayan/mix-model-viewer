#pragma once
#include <memory>
#include "../core/mixWindow.h"

namespace mix
{
	class mixEditor
	{
	public:
		bool _should_run = false;
		void run();
		void start();
		inline void select_monitor(int num);
		static std::unique_ptr<mixEditor> _instance;
		static void create_new();

		mixEditor() = default;
		std::unique_ptr<core::mixWindow> _window = nullptr;
	};
}
