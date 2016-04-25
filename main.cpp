#include "main.hpp"

Engine engine(84, 48);

int main() {
	while (!TCODConsole::isWindowClosed()) 
	{
		engine.update();
		engine.render();
		TCODConsole::flush();
	}
	return 0;
}