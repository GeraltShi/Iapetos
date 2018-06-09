#include "Moveable.h"

#ifndef _ROOT2_
#define ROOT2 1.41421356
#endif // !_ROOT2_



bool Moveable::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	prev_walk_orientation = 5;
	prev_head_orientation = 5;
	colClog = ColClogTime;

	return true;
}

Vec2 Moveable::calSpeed(int dir)
{
	Vec2 speed(0,0);
	switch (dir)
	{
		//123
		//456
		//789
	case 4: //左
		speed.x = -moveSpeed;
		speed.y = 0;
		break;
	case 6://右
		speed.x = moveSpeed;
		speed.y = 0;
		break;
	case 2://上
		speed.x = 0;
		speed.y = moveSpeed;
		break;
	case 8://下
		speed.x = 0;
		speed.y = -moveSpeed;
		break;
	case 1://左上
		speed.x = -moveSpeed / ROOT2;
		speed.y = moveSpeed / ROOT2;
		break;
	case 3://右上
		speed.x = moveSpeed / ROOT2;
		speed.y = moveSpeed / ROOT2;
		break;
	case 7://左下
		speed.x = -moveSpeed / ROOT2;
		speed.y = -moveSpeed / ROOT2;
		break;
	case 9://右下
		speed.x = moveSpeed / ROOT2;
		speed.y = -moveSpeed / ROOT2;
		break;
	case 5://无，头要默认复位
		speed.x = 0;
		speed.y = 0;
		break;
	}
	return speed;
}


