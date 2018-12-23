#include "QuadTree.h"

QuadTree::~QuadTree()
{
}
QuadTree::QuadTree()
{

}
QuadTree::QuadTree(int level, RECT bound)
{
	//chia lam 4

	this->Bound = bound;
	this->mLevel = level;
}

void QuadTree::Clear()
{
	if (Nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (Nodes[i])
			{
				Nodes[i]->Clear();
				delete Nodes[i];
				Nodes[i] = nullptr;
			}
		}

		delete[] Nodes;
	}
}

void QuadTree::InsertObject(Object *object)
{
	if (Nodes)
	{
		if (Nodes[0]->IsContain(object->GetBound()))
			Nodes[0]->InsertObject(object);
		if (Nodes[1]->IsContain(object->GetBound()))
			Nodes[1]->InsertObject(object);
		if (Nodes[2]->IsContain(object->GetBound()))
			Nodes[2]->InsertObject(object);
		if (Nodes[3]->IsContain(object->GetBound()))
			Nodes[3]->InsertObject(object);

		return; //Thoát ra luôn
	}

	//Thêm đối tượng vào quadtree
	if (this->IsContain(object->GetBound()))
		this->mListObject.push_back(object);


	//Chia nhỏ và chèn đối tượng tiếp 1 là số đối tượng tối thiểu trong 1 node 6 là level tối đa
	if (mListObject.size() > 5 && mLevel < 6)
	{
		Split();

		while (!mListObject.empty())
		{
			if (Nodes[0]->IsContain(mListObject.back()->GetBound()))
				Nodes[0]->InsertObject(mListObject.back());
			if (Nodes[1]->IsContain(mListObject.back()->GetBound()))
				Nodes[1]->InsertObject(mListObject.back());
			if (Nodes[2]->IsContain(mListObject.back()->GetBound()))
				Nodes[2]->InsertObject(mListObject.back());
			if (Nodes[3]->IsContain(mListObject.back()->GetBound()))
				Nodes[3]->InsertObject(mListObject.back());

			mListObject.pop_back();
		}
	}
}

bool QuadTree::IsContain(RECT r)
{
	return !(r.right < Bound.left || r.left > Bound.right || r.top < Bound.bottom || r.bottom > Bound.top);
}

void QuadTree::Split()
{
	//cat phan region (ranh gioi) ra thanh 4 phan bang nhau
	Nodes = new QuadTree *[4];

	RECT bound;

	int width = (Bound.right - Bound.left) / 2;
	int height = (Bound.top - Bound.bottom) / 2;

	//phan goc trai tren
	bound.left = Bound.left;
	bound.right = bound.left + width;
	bound.top = Bound.top;
	bound.bottom = bound.top - height;
	Nodes[0] = new QuadTree(mLevel + 1, bound);

	//phan goc phai tren
	bound.left = Bound.left + width;
	bound.right = bound.left + width;
	bound.top = Bound.top;
	bound.bottom = bound.top - height;
	Nodes[1] = new QuadTree(mLevel + 1, bound);

	//phan goc trai duoi
	bound.left = Bound.left;
	bound.right = bound.left + width;
	bound.top = Bound.top - height;
	bound.bottom = bound.top - height;
	Nodes[2] = new QuadTree(mLevel + 1, bound);

	//phan goc phai duoi
	bound.left = Bound.left + width;
	bound.right = bound.left + width;
	bound.top = Bound.top - height;
	bound.bottom = bound.top - height;
	Nodes[3] = new QuadTree(mLevel + 1, bound);
}

int QuadTree::GetTotalObject()
{
	int total = mListObject.size();

	if (Nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			total += Nodes[i]->GetTotalObject();
		}
	}

	return total;
}

int QuadTree::GetIndex(RECT rect)
{
	/*lay vi tri cua Entity
	0: nam trong Node con goc trai tren
	1: nam trong Node con goc phai tren
	2: nam trong Node con goc trai duoi
	3: nam trong Node con goc phai duoi
	-1: bi dinh > 2 node con*/

	float middleVerticle = Bound.left + (Bound.right - Bound.left) / 2.0f;
	float middleHorizontal = Bound.top - (Bound.top - Bound.bottom) / 2.0f;

	if (rect.top < Bound.top && rect.bottom > middleHorizontal)
	{
		//nam phia ben tren
		if (rect.left > Bound.left && rect.right < middleVerticle)
		{
			//nam phia ben trai
			return 0;
		}
		else if (rect.left > middleVerticle && rect.right < Bound.right)
		{
			//nam phia ben phai
			return 1;
		}
	}
	else if (rect.top < middleHorizontal && rect.bottom > Bound.bottom)
	{
		//nam phia ben duoi
		if (rect.left > Bound.left && rect.right < middleVerticle)
		{
			//nam phia ben trai
			return 2;
		}
		else if (rect.left > middleVerticle && rect.right < Bound.right)
		{
			//nam phia ben phai
			return 3;
		}
	}

	return -1;
}

void QuadTree::GetAllObject(std::vector<Object*> &listObject, RECT rect)
{
	for (auto child : mListObject)
	{
		RECT r = child->GetBound();
		if (!(r.right < rect.left || r.left > rect.right || r.top < rect.bottom || r.bottom > rect.top) || child->tag == Object::Tag::Port)
		{
			listObject.push_back(child);			
		}
	}

	if (Nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			Nodes[i]->GetAllObject(listObject, rect);
		}
	}
}

void QuadTree::GetObjectsCollideAble(std::vector<Object*> &listObject, std::vector<Object*> &listWall, RECT rect)
{
	if (Nodes)
	{
		if (Nodes[0]->IsContain(rect))
			Nodes[0]->GetObjectsCollideAble(listObject, listWall, rect);
		if (Nodes[1]->IsContain(rect))
			Nodes[1]->GetObjectsCollideAble(listObject, listWall, rect);
		if (Nodes[2]->IsContain(rect))
			Nodes[2]->GetObjectsCollideAble(listObject, listWall, rect);
		if (Nodes[3]->IsContain(rect))
			Nodes[3]->GetObjectsCollideAble(listObject, listWall, rect);

		return;
	}

	//Lấy tất cả đối tượng trong vùng
	if (IsContain(rect))
	{
		for (auto child : mListObject)
		{
			bool isExists = false;
			for (size_t i = 0; i < listObject.size(); i++)
			{
				if (child->id == listObject.at(i)->id)
				{
					isExists = true;
					break;
				}
			}

			for (size_t i = 0; i < listWall.size(); i++)
			{
				if (child->id == listWall.at(i)->id)
				{
					isExists = true;
					break;
				}
			}


			if (!isExists)
			{
				if (child->tag == Object::Tag::Wall || child->tag == Object::Tag::Port)
				{
					listWall.push_back(child);
				}

				else
				{
					RECT r = child->GetBound();
					if (!(r.right < rect.left || r.left > rect.right || r.top < rect.bottom || r.bottom > rect.top))
					{
						listObject.push_back(child);					
					}
				}
			}
		}
	}
}
