#pragma once

#include "Window.h"
#include "Strike/Core.h"
#include "Strike/LayerStack.h"
#include "Strike/Events/Event.h"
#include "Strike/Events/ApplicationEvent.h"

#include "Strike/ImGui/ImGuiLayer.h" 

#include "Strike/Renderer/Shader.h"
#include "Strike/Renderer/Buffer.h"

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	 Application* CreateApplication();
}
