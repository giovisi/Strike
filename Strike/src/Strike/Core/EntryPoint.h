#pragma once

#ifdef STRK_PLATFORM_WINDOWS

extern Strike::Application* Strike::CreateApplication();

int main(int argc, char** argv) {
	Strike::Log::Init();
	int a = 8;

	STRK_PROFILE_BEGIN_SESSION("Startup", "StrikeProfile-Startup.json");
	auto app = Strike::CreateApplication();
	STRK_PROFILE_END_SESSION();

	STRK_PROFILE_BEGIN_SESSION("Runtime", "StrikeProfile-Runtime.json");
	app->Run();
	STRK_PROFILE_END_SESSION();
	
	STRK_PROFILE_BEGIN_SESSION("Shutdown", "StrikeProfile-Shutdown.json");
	delete app;
	STRK_PROFILE_END_SESSION();
}

#endif