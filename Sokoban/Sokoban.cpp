#include <iostream>
#include <conio.h>

#include "Sokoban.h"
#include "File.h"
#include "ConsoleAPI.h"

Sokoban::Sokoban()
{
	ConsoleAPI::HideCursor();

	const char *filename = "Maze1.txt";
	char *mazeData = nullptr;
	int fileSize = 0;
	File::ReadFile(filename, &mazeData, &fileSize);

	setSize(mazeData, fileSize);

	mStates.SetSize(mWidth, mHeight);
	mbGoalFlags.SetSize(mWidth, mHeight);

	int dx = 0;
	int dy = 0;
	for (int index = 0; mazeData[index]; ++index)
	{
		eObjects obj;
		bool bGoalFlag = false;
		switch (mazeData[index])
		{
		case ' ':
			obj = eObjects::SPACE;
			break;
		case 'X':
			obj = eObjects::WALL;
			break;
		case 'p':
			obj = eObjects::PLAYER;
			mPlayerX = dx;
			mPlayerY = dy;
			break;
		case 'P':
			obj = eObjects::PLAYER;
			bGoalFlag = true;
			mPlayerX = dx;
			mPlayerY = dy;
			break;
		case 'o':
			obj = eObjects::BOX;
			break;
		case 'O':
			obj = eObjects::BOX;
			bGoalFlag = true;
			break;
		case '.':
			obj = eObjects::SPACE;
			bGoalFlag = true;
			break;
		case '\n':
			dx = 0;
			++dy;
			obj = eObjects::UNKNOWN;
			break;
		default:
			obj = eObjects::UNKNOWN;
			break;
		}

		if (obj != eObjects::UNKNOWN)
		{
			mStates(dx, dy) = obj;
			mbGoalFlags(dx, dy) = bGoalFlag;
			++dx;
		}
	}
}

bool Sokoban::IsRunning() const
{
	return mbRunning;
}

void Sokoban::PollInput()
{
	std::cout << "w: up, s: down, a: left, d: right";
	
	if (_kbhit())
	{
		mKey = _getch();
		if (mKey == -32)
		{
			mKey = _getch();
		}
	}
}

void Sokoban::Update()
{
	if (isCleared())
	{
		mbRunning = false;
		return;
	}

	int dx = 0;
	int dy = 0;
	switch (mKey)
	{
	case 'w':
		dy = -1;
		break;
	case 's':
		dy = 1;
		break;
	case 'a':
		dx = -1;
		break;
	case 'd':
		dx = 1;
		break;
	default:
		break;
	}

	int curPlayerX = mPlayerX;
	int curPlayerY = mPlayerY;
	int nextPlayerX = curPlayerX + dx;
	int nextPlayerY = curPlayerY + dy;

	if (mStates(nextPlayerX, nextPlayerY) == eObjects::WALL)
	{
		return;
	}

	if (mStates(nextPlayerX, nextPlayerY) == eObjects::SPACE)
	{
		mStates(nextPlayerX, nextPlayerY) = eObjects::PLAYER;
		mStates(curPlayerX, curPlayerY) = eObjects::SPACE;
	}
	else if (mStates(nextPlayerX, nextPlayerY) == eObjects::BOX)
	{
		int nextBoxX = nextPlayerX + dx;
		int nextBoxY = nextPlayerY + dy;

		if (mStates(nextBoxX, nextBoxY) == eObjects::WALL
			|| mStates(nextBoxX, nextBoxY) == eObjects::BOX)
		{
			return;
		}

		mStates(nextBoxX, nextBoxY) = eObjects::BOX;
		mStates(nextPlayerX, nextPlayerY) = eObjects::PLAYER;
		mStates(curPlayerX, curPlayerY) = eObjects::SPACE;
	}

	mPlayerX = nextPlayerX;
	mPlayerY = nextPlayerY;
}

void Sokoban::Render() const
{
	ConsoleAPI::GotoXY(0, 0);

	for (int y = 0; y < mHeight; ++y)
	{
		for (int x = 0; x < mWidth; ++x)
		{
			if (!mbGoalFlags(x, y))
			{
				switch (mStates(x, y))
				{
				case eObjects::SPACE:
					std::cout << ' ';
					break;
				case eObjects::WALL:
					std::cout << 'X';
					break;
				case eObjects::PLAYER:
					std::cout << 'p';
					break;
				case eObjects::BOX:
					std::cout << 'o';
					break;
				default:
					break;
				}
			}
			else
			{
				switch (mStates(x, y))
				{
				case eObjects::SPACE:
					std::cout << '.';
					break;
				case eObjects::WALL:
					std::cout << 'X';
					break;
				case eObjects::PLAYER:
					std::cout << 'P';
					break;
				case eObjects::BOX:
					std::cout << 'O';
					break;
				default:
					break;
				}
			}
		}
		std::cout << std::endl;
	}
}

void Sokoban::setSize(char *mazeData, int fileSize)
{
	int dx = 0;
	int dy = 1;
	for (int index = 0; mazeData[index]; ++index)
	{
		switch (mazeData[index])
		{
		case ' ': case 'X': case 'p': case 'P':
		case 'o': case 'O': case '.':
			++dx;
			break;
		case '\n':
			dx = 0;
			++dy;
			break;
		default:
			break;
		}
	}
	mWidth = dx;
	mHeight = dy;
}

bool Sokoban::isCleared()
{
	for (int y = 0; y < mHeight; ++y)
	{
		for (int x = 0; x < mWidth; ++x)
		{
			if (mStates(x, y) == eObjects::SPACE
				&& mbGoalFlags(x, y) == true)
			{
				return false;
			}
		}
	}

	return true;
}