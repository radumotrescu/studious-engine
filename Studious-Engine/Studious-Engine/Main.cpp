#include "Window.h"

using namespace std;

void main()
{
	auto window = new Window("Test", 600, 800);

	while(!window->closed())
	{
		window->update();
	}
}