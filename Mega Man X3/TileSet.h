#pragma once
#include "Sprite.h"
#include "Viewport.h"
#include <vector>
#include "Graphic.h"
using namespace std;

class TileSet
{
protected:
	Sprite* sprite;
	RECT rect_tile[22000];
	int tileWidth, tileHeight;
	int id, columns, tileCount;
	int margin;

public:
	TileSet();
	TileSet(Graphic* graphic, TiXmlElement *node);
	~TileSet();

	void ReadXML(TiXmlElement *node);
	int GetId();
	void Render(Viewport* view, int id, D3DXVECTOR2 position);
};

