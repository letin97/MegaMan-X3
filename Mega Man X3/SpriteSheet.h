#pragma once
#include <d3dx9.h>
#include "TinyXML\tinyxml.h"

class SpriteSheet
{
protected:
	float width, height;
	struct Tile
	{
		float x;
		float y;
		float w;
		float h;
		float tx;
		float ty;
		float gx;
		float gy;
		float sx;
		float sy;
	};
	
public:
	SpriteSheet(const char* path);
	~SpriteSheet();

	Tile tile[200];

	float GetWidth();
	float GetHeight();

	void ReadXML(const char* path);
	RECT GetRect(int index);
	D3DXVECTOR2 GetTransform(int index);
	D3DXVECTOR2 GetGun(int index);
	D3DXVECTOR2 GetSpark(int index);
};

