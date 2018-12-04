#include "Collision.h"


Collision::Collision()
{
}

Collision::~Collision()
{
}


RECT Collision::GetBoard(RECT object, D3DXVECTOR2 distance)
{
	RECT board = object;

	if (distance.x < 0)
		board.left = object.left + distance.x;
	else if (distance.x > 0)
		board.right = object.right + distance.x;

	if (distance.y < 0)
		board.bottom = object.bottom + distance.y;
	else if (distance.y > 0)
		board.top = object.top + distance.y;

	return board;
}

//Kiểm tra chạm 1 điểm và RECT
bool Collision::isCollision(float x, float y, RECT other)
{
	return !(x < other.left || x > other.right || y > other.top || y < other.bottom);
}

//Kiểm tra chạm 2 RECT 
bool Collision::isCollision(RECT object, RECT other)
{
	return !(object.right < other.left || object.left > other.right || object.top < other.bottom || object.bottom > other.top);
}

//Kiểm tra có lồng nhau không
bool Collision::isNested(RECT object, RECT other)
{
	return !(object.right <= other.left || object.left >= other.right || object.top <= other.bottom || object.bottom >= other.top);
}

//Kiểm tra để lấy thông tin va chạm
float Collision::CollisionAABB(RECT object, RECT other, D3DXVECTOR2 distance, D3DXVECTOR2 &side)//distance là khoảng cách tối đa object đi
{
	if (distance.y == 0.0f && object.bottom >= other.top || distance.x == 0.0f && object.right <= other.left
		|| distance.y == 0.0f && object.top <= other.bottom || distance.x == 0.0f && object.left >= other.right)
	{
		side.x = 0.0f;
		side.y = 0.0f;
		return 1.0f;
	}
	
	float dxEntry, dxExit;
	float dyEntry, dyExit;

	if (distance.x > 0)
	{
		dxEntry = other.left - object.right;
		dxExit = other.right - object.left;
	}
	else
	{
		dxEntry = other.right - object.left;
		dxExit = other.left - object.right;
	}

	if (distance.y > 0)
	{
		dyEntry = other.bottom - object.top;
		dyExit = other.top - object.bottom;
	}
	else
	{
		dyEntry = other.top - object.bottom;
		dyExit = other.bottom - object.top;
	}

	float xEntry, xExit;
	float yEntry, yExit;

	if (distance.x == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = dxEntry / distance.x;
		xExit = dxExit / distance.x;
	}

	if (distance.y == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = dyEntry / distance.y;
		yExit = dyExit / distance.y;
	}

	float Entry = max(xEntry, yEntry);
	float Exit = min(xExit, yExit);

	if (Entry > Exit || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		side.x = 0.0f;
		side.y = 0.0f;
		return 1.0f;
	}

	//Nếu va chạm

	if (xEntry > yEntry)
	{
		if (distance.x < 0.0f)
		{
			side.x = -1.0f;		//trái
			side.y = 0.0f;
		}
		else
		{
			side.x = 1.0f;		//phải
			side.y = 0.0f;
		}
	}
	else
	{
		if (distance.y < 0.0f)
		{
			side.x = 0.0f;
			side.y = 1.0f;		//dưới 
		}
		else
		{
			side.x = 0.0f;
			side.y = -1.0f;		//trên
		}
	}

	//Trả về tỉ số;
	return Entry;
}