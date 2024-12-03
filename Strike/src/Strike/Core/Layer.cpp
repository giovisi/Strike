#include "strkpch.h"
#include "Layer.h"

namespace Strike {
	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName) {}

	Layer::~Layer() {}
}