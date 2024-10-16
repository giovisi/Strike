#pragma once

#include "Window.h"
#include "Strike/Core.h"
#include "Strike/LayerStack.h"
#include "Strike/Events/Event.h"
#include "Strike/Events/ApplicationEvent.h"

namespace Strike {

	class STRIKE_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	STRIKE_API Application* CreateApplication();
}
