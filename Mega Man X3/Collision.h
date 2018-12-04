#pragma once
#include "Object.h"
#include "Graphic.h"
#include <d3dx9.h>

class Collision
{
public:
	Collision();
	~Collision();

	static RECT GetBoard(RECT object, D3DXVECTOR2 distance);

	//Kiểm tra chạm 1 điểm và RECT
	static bool isCollision(float x, float y, RECT other);

	//Kiểm tra chạm 2 Rect
	static bool isCollision(RECT object, RECT other);

	//Kiểm tra lồng vào nhau
	static bool isNested(RECT object, RECT other);

	static float CollisionAABB(RECT object, RECT other, D3DXVECTOR2 distance, D3DXVECTOR2 &side);

};

