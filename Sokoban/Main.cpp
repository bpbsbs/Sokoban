#include "Sokoban.h"

int main(void)
{
	Sokoban *sokoban = new Sokoban();

	while (sokoban->IsRunning())
	{
		sokoban->Render();
		sokoban->PollInput();
		sokoban->Update();
	}
	delete sokoban;
	sokoban = nullptr;

	return 0;
}