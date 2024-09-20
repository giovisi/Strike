#pragma once

#include "Core.h"

namespace Strike {

	class STRIKE_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
