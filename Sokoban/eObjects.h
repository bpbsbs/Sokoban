#pragma once

enum class eObjects
{
	SPACE = 0b000,	// 0
	WALL = 0b001,	// 1
	PLAYER = 0b010,	// 2
	BOX = 0b100,	// 4
	
	UNKNOWN = -1
};

inline eObjects operator|(eObjects obj1, eObjects obj2)
{
	return obj1 | obj2;
}

inline eObjects operator&(eObjects obj1, eObjects obj2)
{
	return obj1 & obj2;
}