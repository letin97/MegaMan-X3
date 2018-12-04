#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Graphic.h"

class Text
{
protected:
	Graphic *graphic;
	ID3DXFont *font;
public:
	Text(Graphic *graphic, int size);
	~Text();
	void Render(char * text, RECT r, D3DCOLOR color);
};