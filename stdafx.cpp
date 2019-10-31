#include "stdafx.h"

Dir RotatedDir(Dir dir)
{
	switch (dir)
	{
	case (Dir::LEFT):
		return Dir::UP;
	case (Dir::DOWN):
		return Dir::LEFT;
	case (Dir::RIGHT):
		return Dir::DOWN;
	default:
		return Dir::RIGHT;
	}
}