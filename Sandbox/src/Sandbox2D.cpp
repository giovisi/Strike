#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true) {}


void Sandbox2D::OnAttach() {
	STRK_PROFILE_FUNCTION();

	m_CheckerboardTexture = Strike::Texture2D::Create("assets/textures/Checkerboard.png");

}

void Sandbox2D::OnDetach() {
	STRK_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Strike::Timestep ts) {
	STRK_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	{
		STRK_PROFILE_SCOPE("Renderer Prep");
		Strike::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Strike::RenderCommand::Clear();
	}

	{
		STRK_PROFILE_SCOPE("Renderer Draw");
		Strike::Renderer2D::BeginScene(m_CameraController.GetCamera());
		//Strike::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), {0.8f, 0.2f, 0.3f, 1.0f});
		Strike::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, {0.8f, 0.2f, 0.3f, 1.0f});
		Strike::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Strike::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f, glm::vec4(1.0f, 0.8f, 0.8f, 1.0f));
		Strike::Renderer2D::DrawQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture, 20.0f);
		Strike::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender() {
	STRK_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Strike::Event& e) {
	m_CameraController.OnEvent(e);
}
