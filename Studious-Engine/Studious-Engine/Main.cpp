#include "Window.h"

using namespace std;

auto main() -> void
{
	auto window = new Window("Test", 600, 800);

	while(!window->closed())
	{
		window->update();
	}

	delete window;
}