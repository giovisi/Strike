#include "strkpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Strike {
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:	STRK_CORE_ASSERT(false, "RendererAPI::API::None currently not supprorted!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(width, height);
		}


		STRK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:	STRK_CORE_ASSERT(false, "RendererAPI::API::None currently not supprorted!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(path);
		}


		STRK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}