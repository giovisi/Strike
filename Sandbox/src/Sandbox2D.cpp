#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


static const uint32_t s_MapWidth = 24;
static const char* s_MapTiles = 
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWDDDDDDWWWWWWWWWW"
"WWWWWWDDDDDDDDDDDDWWWWWW"
"WWWWWDDDDDDDDDDDDDDWWWWW"
"WWWWWWDDDDDDDDDDDDWWWWWW"
"WWWWWDDWWWDDDDDDWWWWWWWW"
"WWWWWDDWWWDDDDDDDDDWWWWW"
"WWWWDDDDDDDDDDDDDDDDWWWW"
"WWWWWDDDDDDDDDDDDDWWWWWW"
"WWWWDDDDDDDDDDDDDDDDWWWW"
"WWWWWWDDDDDDDDDDDWWWWWWW"
"WWWWWDDDDDDDDDDWWWWWWWWW"
"WWWWWWWWWDDDDDWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
;


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true) {}


void Sandbox2D::OnAttach() {
	STRK_PROFILE_FUNCTION();

	m_CheckerboardTexture = Strike::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = Strike::Texture2D::Create("assets/game/textures/RPG_Spritesheet.png");

	Strike::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = Strike::Framebuffer::Create(fbSpec);

	m_TextureStairs = Strike::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0, 11 }, { 128, 128 });
	m_TextureTree = Strike::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / s_MapWidth;

	s_TextureMap['D'] = Strike::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 11 }, { 128, 128 });
	s_TextureMap['W'] = Strike::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, { 128, 128 });


	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(5.0f);
}

void Sandbox2D::OnDetach() {
	STRK_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Strike::Timestep ts) {
	STRK_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Strike::Renderer2D::ResetStats();
	{
		STRK_PROFILE_SCOPE("Renderer Prep");
		m_Framebuffer->Bind();
		Strike::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Strike::RenderCommand::Clear();
	}
#if 1
	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		STRK_PROFILE_SCOPE("Renderer Draw");
		Strike::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Strike::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(- 45.0f), {0.8f, 0.2f, 0.3f, 1.0f});
		Strike::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, {0.8f, 0.2f, 0.3f, 1.0f});
		Strike::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Strike::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		Strike::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_CheckerboardTexture, 20.0f);
		Strike::Renderer2D::EndScene();

		Strike::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y <= 5.0f; y += 0.5f) {
			for (float x = -5.0f; x <= 5.0f; x += 0.5f) {
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Strike::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Strike::Renderer2D::EndScene();
	}
#endif
#if 0
	if (Strike::Input::IsMouseButtonPressed(STRK_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = Strike::Input::GetMousePosition();
		auto width = Strike::Application::Get().GetWindow().GetWidth();
		auto height = Strike::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());
#endif
#if 0
	Strike::Renderer2D::BeginScene(m_CameraController.GetCamera());

	for (uint32_t y = 0; y < m_MapHeight; y++) {
		for (uint32_t x = 0; x < m_MapWidth; x++) {
			char tileType = s_MapTiles[x + y * m_MapWidth];
			Strike::Ref<Strike::SubTexture2D> texture;
			if (s_TextureMap.find(tileType) != s_TextureMap.end())
				texture = s_TextureMap[tileType];
			else
				texture = m_TextureStairs;

			Strike::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, m_MapHeight - y - m_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f }, texture);
		}
	}

	//Strike::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_TextureStairs);
	//Strike::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_TextureBarrel);
	//Strike::Renderer2D::DrawQuad({ -1.0f, 0.5f, 0.5f }, { 1.0f, 2.0f }, m_TextureTree);
	Strike::Renderer2D::EndScene();
#endif
	m_Framebuffer->Unbind();
}

void Sandbox2D::OnImGuiRender() {
	STRK_PROFILE_FUNCTION();

	static bool dockingEnabled = true;

	if (dockingEnabled) {
		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
		
				if (ImGui::MenuItem("Exit")) Strike::Application::Get().Close();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = Strike::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		//ImGui::Image((void*)textureID, ImVec2{ 320.0f, 180.0f });
		ImGui::Image((void*)textureID, ImVec2(1280.f, 720.f), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();

		ImGui::End();
	}
	else {
		ImGui::Begin("Settings");

		auto stats = Strike::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		uint32_t textureID = m_CheckerboardTexture->GetRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
		ImGui::End();
	}
}

void Sandbox2D::OnEvent(Strike::Event& e) {
	m_CameraController.OnEvent(e);
}
