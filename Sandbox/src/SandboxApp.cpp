#include <Strike.h>
#include <Strike/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"


class ExampleLayer : public Strike::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true) {
		m_VertexArray = Strike::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		};

		Strike::Ref<Strike::VertexBuffer> vertexBuffer = Strike::VertexBuffer::Create(vertices, sizeof(vertices));
		Strike::BufferLayout layout = {
			{Strike::ShaderDataType::Float3, "a_Position"},
			{Strike::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Strike::Ref<Strike::IndexBuffer> indexBuffer = Strike::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_SquareVA = Strike::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f, 0.0f, 1.0f
		};

		Strike::Ref<Strike::VertexBuffer> squareVB = Strike::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVB->SetLayout({
			{ Strike::ShaderDataType::Float3, "a_Position" },
			{ Strike::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Strike::Ref<Strike::IndexBuffer> squareIB = Strike::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		//-------- To adjust logo dimensions --------
		m_SquareLogo = Strike::VertexArray::Create();

		float squareVerticesLogo[5 * 4] = {
			-0.5f, -0.36f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.36f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.36f,  0.0f, 1.0f, 1.0f,
			-0.5f,  0.36f,  0.0f, 0.0f, 1.0f
		};

		squareVB = Strike::VertexBuffer::Create(squareVerticesLogo, sizeof(squareVerticesLogo));

		squareVB->SetLayout({
			{ Strike::ShaderDataType::Float3, "a_Position" },
			{ Strike::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareLogo->AddVertexBuffer(squareVB);
		m_SquareLogo->SetIndexBuffer(squareIB);
		//-------------------------------------------

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Strike::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main() {
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader = Strike::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Strike::Texture2D::Create("assets/textures/Checkerboard.png");
		m_StrikeLogoTexture = Strike::Texture2D::Create("assets/textures/StrikeLogo.png");

		std::dynamic_pointer_cast<Strike::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Strike::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Strike::Timestep ts) override {
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Strike::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Strike::RenderCommand::Clear();

		Strike::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Strike::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Strike::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Strike::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");
		m_Texture->Bind();
		Strike::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_StrikeLogoTexture->Bind(); 
		// m_SquareLogo to adjust logo dimensions (should be m_SquareVA)
		Strike::Renderer::Submit(textureShader, m_SquareLogo, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		//Strike::Renderer::Submit(m_Shader, m_VertexArray);

		Strike::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
	
	void OnEvent(Strike::Event& e) override {
		m_CameraController.OnEvent(e);
	}

private:
	Strike::ShaderLibrary m_ShaderLibrary;
	Strike::Ref<Strike::Shader> m_Shader;
	Strike::Ref<Strike::VertexArray> m_VertexArray;

	Strike::Ref<Strike::Shader> m_FlatColorShader;
	Strike::Ref<Strike::VertexArray> m_SquareVA, m_SquareLogo; // Logo to adjust dimensions (could be replaced by SquareVA)

	Strike::Ref<Strike::Texture2D> m_Texture, m_StrikeLogoTexture;

	Strike::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Strike::Application {
public:
	Sandbox() {
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {

	}
};

Strike::Application* Strike::CreateApplication() {
	return new Sandbox();
}