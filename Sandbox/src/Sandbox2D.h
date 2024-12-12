#pragma once

#include "Strike.h"

#include "ParticleSystem.h"

class Sandbox2D : public Strike::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	
	void OnUpdate(Strike::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Strike::Event& e) override;

private:
	Strike::OrthographicCameraController m_CameraController;

	// temporary --> inside 2D renderer
	Strike::Ref<Strike::VertexArray> m_SquareVA;
	Strike::Ref<Strike::Shader> m_FlatColorShader;

	Strike::Ref<Strike::Texture2D> m_CheckerboardTexture;
	Strike::Ref<Strike::Texture2D> m_SpriteSheet;
	Strike::Ref<Strike::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;

	struct ProfileResult {
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResult;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

	uint32_t m_MapWidth, m_MapHeight;

	std::unordered_map<char, Strike::Ref<Strike::SubTexture2D>> s_TextureMap;
};