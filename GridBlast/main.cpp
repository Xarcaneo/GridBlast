#include "Engine.h"

int main()
{
	Engine engine("OpenGL Window", 854, 480);  // Create engine with window title and size
	engine.Run();

	return 0;
}