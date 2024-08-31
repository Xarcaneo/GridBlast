#include "Engine.h"

int main()
{
	Engine engine("OpenGL Window", 800, 600);  // Create engine with window title and size
	engine.Run();

	return 0;
}