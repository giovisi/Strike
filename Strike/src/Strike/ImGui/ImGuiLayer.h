#pragma once

#include "Strike/Layer.h"

#include "Strike/Events/KeyEvent.h"
#include "Strike/Events/MouseEvent.h"
#include "Strike/Events/ApplicationEvent.h"

namespace Strike {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}