#pragma once

#include "Array2D.h"
#include "eObjects.h"

class Sokoban
{
public:
	Sokoban();
	Sokoban(const Sokoban&) = delete;
	Sokoban& operator=(const Sokoban&) = delete;
	~Sokoban() = default;

public:
	bool IsRunning() const;
	void PollInput();
	void Update();
	void Render() const;

private:
	void setSize(char *mazeData, int fileSize);	// Set mWidth and mHeight.
	bool isCleared();

private:
	int mWidth = 0;
	int mHeight = 0;
	Array2D<eObjects> mStates;
	Array2D<bool> mbGoalFlags;
	bool mbRunning = true;
	int mPlayerX = 0;
	int mPlayerY = 0;
	char mKey;
};