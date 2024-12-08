#pragma once

#include "Window.h"
#include "Strike/Core/Core.h"
#include "Strike/Core/LayerStack.h"
#include "Strike/Events/Event.h"
#include "Strike/Events/ApplicationEvent.h"

#include "Strike/Core/Timestep.h"

#include "Strike/ImGui/ImGuiLayer.h" 

namespace Strike {

	class  Application {
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
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		Timestep m_Timestep;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	 Application* CreateApplication();
}
