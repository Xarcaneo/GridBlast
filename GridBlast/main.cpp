#include "Engine.h"
#include "Bootstrapper.h"

int main()
{
	Bootstrapper::Setup();
	Engine engine("OpenGL Window", 854, 480);  // Create engine with window title and size
	engine.Run();

	return 0;
}