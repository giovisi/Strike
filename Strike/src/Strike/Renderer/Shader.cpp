#include "strkpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Strike {
	Shader* Shader::Create(const std::string& filepath) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:		STRK_CORE_ASSERT(false, "RendererAPI::API::None currently not supprorted!"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLShader(filepath);
		}


		STRK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:		STRK_CORE_ASSERT(false, "RendererAPI::API::None currently not supprorted!"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLShader(vertexSrc, fragmentSrc);
		}


		STRK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}