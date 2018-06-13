#include "Sokoban.h"

int main(void)
{
	Sokoban *sokoban = new Sokoban();

	sokoban->Render();
	while (sokoban->IsRunning())
	{
		sokoban->PollInput();
		sokoban->Update();
		sokoban->Render();
	}
	delete sokoban;
	sokoban = nullptr;

	return 0;
}