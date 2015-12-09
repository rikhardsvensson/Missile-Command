#include "Game.h"

int main()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	Game g = Game(&mt);
	g.init();
	return g.run();
}
