#include"Moveable.h"

bool Moveable::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	//��ʼ�������
	prev_walk_orientation = 5;
	prev_head_orientation = 5;
	moveSpeed = 3;
	widthSize = 10;
	moving = false;

	return true;
}

Rect Moveable::boundingBox()
{
	return Rect(getPositionX() - widthSize / 2, getPositionY() + widthSize / 2,
		widthSize, widthSize);
}