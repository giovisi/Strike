#include <Strike.h>
#include <Strike/Core/EntryPoint.h>

#include "StrikeThroughLayer.h"

namespace Strike {
	class StrikeThrough : public Application {
	public:
		StrikeThrough()
			: Application("StrikeThrough") {
			PushLayer(new StrikeThroughLayer());
		}

		~StrikeThrough() {

		}
	};

	Application* CreateApplication() {
		return new StrikeThrough();
	}
}