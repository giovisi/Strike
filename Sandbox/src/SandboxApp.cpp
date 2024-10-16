#include <Strike.h>

class ExampleLayer : public Strike::Layer {
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override {
		STRK_INFO("ExampleLayer::Update");
	}
	
	void OnEvent(Strike::Event &event) override {
		STRK_TRACE("{0}", event);
	}
};

class Sandbox : public Strike::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Strike::ImGuiLayer());
	}

	~Sandbox() {

	}
};

Strike::Application* Strike::CreateApplication() {
	return new Sandbox();
}