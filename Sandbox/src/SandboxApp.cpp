#include <Strike.h>

#include "imgui/imgui.h"

class ExampleLayer : public Strike::Layer {
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override {
		if (Strike::Input::IsKeyPressed(STRK_KEY_TAB))
			STRK_TRACE("Tab Key is pressed! (Poll)");
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Test");
		ImGui::End();
	}
	
	void OnEvent(Strike::Event &event) override {
		if (event.GetEventType() == Strike::EventType::KeyPressed) {
			Strike::KeyPressedEvent& e = (Strike::KeyPressedEvent&)event;
			if (e.GetKeyCode() == STRK_KEY_TAB)
				STRK_TRACE("Tab key is pressed! (event)");
			STRK_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Strike::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Strike::Application* Strike::CreateApplication() {
	return new Sandbox();
}