#include "core/Log.h"
#include "core/Window.h"
#include <glm/glm.hpp>

int main()
{
	{
		Log::Init();
		Window* window = new Window();
		window->Run();
		delete window;
	}
  return 0;
}