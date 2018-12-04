#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include "Viewport.h"
#include "Object.h"

class QuadTree
{
protected:

	int GetIndex(RECT r);
	void Split();				 //thuc hien chia ra cac node
	bool IsContain(RECT r);

public:
	QuadTree();
	QuadTree(int level, RECT bound);
	~QuadTree();
	void Clear();
	void InsertObject(Object *object);

	/*lay danh sach nhung Entity co kha nang xay ra va cham*/
	void GetObjectsCollideAble(std::vector<Object*> &listObject, std::vector<Object*> &listWall, RECT rect);

	void GetAllObject(std::vector<Object*> &listObject, RECT rect);

	int GetTotalObject();

	RECT Bound;

	int mLevel;

	std::vector<Object*> mListObject;

	QuadTree **Nodes;

};