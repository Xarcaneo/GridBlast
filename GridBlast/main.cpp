#include "Engine.h"
#include "Bootstrapper.h"

int main()
{
	Bootstrapper::Setup();
	Engine engine("OpenGL Window", 960, 540);  // Create engine with window title and size
	engine.Run();

	return 0;
}