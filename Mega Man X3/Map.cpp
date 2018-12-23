#include "Map.h"
#pragma warning (disable : 4996)

void WriteNode(TiXmlElement *root, QuadTree *quadtree)
{
	if (quadtree == NULL)
		return;

	root->SetAttribute("level", quadtree->mLevel);
	root->SetAttribute("left", quadtree->Bound.left);
	root->SetAttribute("top", quadtree->Bound.top);
	root->SetAttribute("right", quadtree->Bound.right);
	root->SetAttribute("bottom", quadtree->Bound.bottom);
	root->SetAttribute("numObj", quadtree->mListObject.size());

	for (size_t i = 0; i < quadtree->mListObject.size(); i++)
	{
		TiXmlElement* obj = new TiXmlElement("obj");
		obj->SetAttribute("id", quadtree->mListObject.at(i)->id);
		obj->SetAttribute("name", (char *)quadtree->mListObject.at(i)->GetName().c_str());
		obj->SetAttribute("x", quadtree->mListObject.at(i)->GetPosition().x);
		obj->SetAttribute("y", quadtree->mListObject.at(i)->GetPosition().y);
		obj->SetAttribute("w", quadtree->mListObject.at(i)->GetWidth());
		obj->SetAttribute("h", quadtree->mListObject.at(i)->GetHeight());
		root->LinkEndChild(obj);
	}

	if (quadtree->Nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			//if (node->Nodes[i] != NULL)
			{
				TiXmlElement* node = new TiXmlElement("node");
				WriteNode(node, quadtree->Nodes[i]);
				root->LinkEndChild(node);
			}
		}
	}
}

void WriteQuadtree(QuadTree *quadtree)
{
	TiXmlDocument doc;
	TiXmlDeclaration *dec = new TiXmlDeclaration("1.0", "utf-8", "");
	doc.LinkEndChild(dec);
	TiXmlElement* root = new TiXmlElement("Node");
	WriteNode(root, quadtree);
	doc.LinkEndChild(root);
	doc.SaveFile("Resource Files/QuadTree.xml");
}

Map::Map()
{
}

Map::Map(Graphic* graphic)
{
	ReadXML(graphic, MapXML);
	position = D3DXVECTOR2(0, 0);
	
	RECT r;
	r.left = 0;
	r.right = r.left + width*tileWidth;
	r.bottom = 0;
	r.top = r.bottom + height*tileHeight;

	if (r.right < r.top)
		r.right = r.top;
	else
		r.top = r.right;

	mQuadTree = new QuadTree(1, r);

	for (int i = 0; i < numObjectGroups; i++)
	{
		for (int j = 0; j < objectGroups.at(i)->numObjects; j++)
		{
			Object *obj = new Object();
			float x = objectGroups.at(i)->objects.at(j)->x;
			float y = objectGroups.at(i)->objects.at(j)->y;
			float w = objectGroups.at(i)->objects.at(j)->width;
			float h = objectGroups.at(i)->objects.at(j)->height;
			D3DXVECTOR2 pos;
			pos.x = x + w / 2;
			pos.y = height * tileHeight - y - h / 2;
			obj->SetPosition(pos);
			obj->SetBound(w, h);
			obj->id = objectGroups.at(i)->objects.at(j)->id;
			obj->SetName(objectGroups.at(i)->objects.at(j)->name);
			mQuadTree->InsertObject(obj);
		}
	}
	//WriteQuadtree(mQuadTree);
}

Map::~Map()
{
	delete tileSet;
}

void Map::ReadXML(Graphic* graphic, const char *path)
{
	TiXmlDocument doc(path);
	if (!doc.LoadFile())
	{
		MessageBox(NULL, "Can't load Map xml file", "Error", MB_OK);
		return;
	}
	//map
	TiXmlElement* map = doc.RootElement();
	map->QueryIntAttribute("width", &width);
	map->QueryIntAttribute("height", &height);
	map->QueryIntAttribute("tilewidth", &tileWidth);
	map->QueryIntAttribute("tileheight", &tileHeight);

	//tileset
	TiXmlElement* tileset = map->FirstChildElement();
	tileSet = new TileSet(graphic, tileset);

	//layer
	TiXmlElement* layer = tileset->NextSiblingElement();

	//data
	TiXmlElement* data = layer->FirstChildElement();
	const char *dataText = data->GetText();

	//cắt chuỗi
	char *token;
	token = strtok((char *)(dataText), ",");
	int row = height - 1;
	int column = 0;
	while (token != NULL)
	{
		_data[row][column] = atoi(token);
		column++;
		if (column >= width)
		{
			row--;
			column = 0;
		}
		// strtok nhận vào NULL, để nó có thể tiếp tục tìm kiếm từ vị trí kết thúc trước đó.
		token = strtok(NULL, ",");
	}

	TiXmlElement* objStage = layer->NextSiblingElement();
	MapObjectGroup *stage = new MapObjectGroup(objStage);
	for (int i = 0; i < stage->numObjects; i++)
	{
		Object *obj = new Object();
		float x = stage->objects.at(i)->x;
		float y = stage->objects.at(i)->y;
		float w = stage->objects.at(i)->width;
		float h = stage->objects.at(i)->height;
		RECT r = { x, height * tileHeight - y, x + w, height * tileHeight - y - h };
		listStage.push_back(r);
	}

	TiXmlElement* indexml = NULL;
	numObjectGroups = 0;
	for (indexml = objStage->NextSiblingElement(); indexml != NULL; indexml = indexml->NextSiblingElement())
	{
		numObjectGroups++;
		MapObjectGroup *obj = new MapObjectGroup(indexml);
		objectGroups.push_back(obj);
	}
}

void Map::Update(float dt)
{

}

int Map::GetData(D3DXVECTOR2 position)
{
	int w = position.x / tileWidth;
	int h = position.y / tileHeight;
	return _data[h][w];
}
void Map::SetData(D3DXVECTOR2 position, int data)
{
	int w = position.x / tileWidth;
	int h = position.y / tileHeight;
	_data[h][w] = data;
}

void Map::Render(Viewport * viewport)
{
	int startH, startW, endH, endW;
	RECT r = viewport->GetBound();
	startH = r.bottom / tileHeight;
	endH = r.top / tileHeight + 1;
	startW = r.left / tileWidth;
	endW = r.right / tileWidth + 1;

	for (int h = startH; h < endH; h++)
		for (int w = startW; w < endW; w++)
		{
			int id = _data[h][w];
			if (id > 0)
			{
				D3DXVECTOR2 position(w * tileWidth, (h + 1) * tileHeight);
				tileSet->Render(viewport, id, position);
			}
		}
}
