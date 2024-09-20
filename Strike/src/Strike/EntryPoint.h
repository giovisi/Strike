#pragma once

#ifdef STRK_PLATFORM_WINDOWS

extern Strike::Application* Strike::CreateApplication();

int main(int argc, char** argv) {
	auto app = Strike::CreateApplication();
	app->Run();
	delete app;
}

#endif