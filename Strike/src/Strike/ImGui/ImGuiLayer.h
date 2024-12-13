#pragma once

#include "Strike/Core/Layer.h"

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
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		inline void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}