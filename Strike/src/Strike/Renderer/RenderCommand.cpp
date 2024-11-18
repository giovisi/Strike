#include "strkpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Strike {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}