#include "core/Log.h"
#include "core/Window.h"
#include <glm/glm.hpp>
#include "core/Input.h"

int main()
{
	{
		Log::Init();
		Window *window = new Window();
		Input::Init(window);
		window->Run();
		delete window;
	}
	return 0;
}