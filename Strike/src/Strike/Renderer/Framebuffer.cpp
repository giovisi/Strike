#include "strkpch.h"
#include "Framebuffer.h"

#include "Strike/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Strike {
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:		STRK_CORE_ASSERT(false, "RendererAPI::API::None currently not supprorted!"); return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLFramebuffer>(spec);
		}


		STRK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}