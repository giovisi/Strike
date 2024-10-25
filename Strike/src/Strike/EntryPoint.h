#pragma once

#ifdef STRK_PLATFORM_WINDOWS
extern Strike::Application* Strike::CreateApplication();

int main(int argc, char** argv) {
	Strike::Log::Init();
	STRK_CORE_WARN("Initialized Log!");
	int a = 8;
	STRK_INFO("Hello! Var={0}", __cplusplus);


	auto app = Strike::CreateApplication();
	app->Run();
	delete app;
}

#endif