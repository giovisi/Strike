#pragma once

#include "Window.h"
#include "Strike/Core.h"
#include "Strike/LayerStack.h"
#include "Strike/Events/Event.h"
#include "Strike/Events/ApplicationEvent.h"

#include "Strike/ImGui/ImGuiLayer.h" 

#include "Strike/Renderer/Shader.h"
#include "Strike/Renderer/Buffer.h"
#include "Strike/Renderer/VertexArray.h"

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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;


	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	 Application* CreateApplication();
}
