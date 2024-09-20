#include <Strike.h>

class Sandbox : public Strike::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Strike::Application* Strike::CreateApplication() {
	return new Sandbox();
}