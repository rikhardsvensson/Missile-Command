#include "Game.h"

int main()
{
#ifdef _DEBUG
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(flag);
	//_CrtSetBreakAlloc(434);
#endif

	std::random_device rd;
	std::mt19937 mt(rd());

	Game g = Game(&mt);
	g.init();
	return g.run();
}
