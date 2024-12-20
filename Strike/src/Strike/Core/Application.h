#pragma once

#include "Window.h"
#include "Strike/Core/Base.h"
#include "Strike/Core/LayerStack.h"
#include "Strike/Events/Event.h"
#include "Strike/Events/ApplicationEvent.h"

#include "Strike/Core/Timestep.h"

#include "Strike/ImGui/ImGuiLayer.h" 

int main(int argc, char** argv);

namespace Strike {

	class  Application {
	public:
		Application(const std::string& name = "Strike App");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		void Close();

		inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance; }

	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	 Application* CreateApplication();
}
