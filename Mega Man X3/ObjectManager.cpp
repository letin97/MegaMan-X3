#include "ObjectManager.h"
#include "string.h"

ObjectManager::ObjectManager()
{
}
ObjectManager::~ObjectManager()
{
	delete megaMan;
	delete map;
	delete viewport;
	mQuadTree->Clear();
	delete mQuadTree;
	delete lifebar;

	delete sprite_MegaMan;
	delete sprite_Effect;
	delete sprite_Weapons_And_Items;
	delete sprite_Enemy;

	delete mGenjibo;

}

//Load Game
void ObjectManager::Init(Graphic* graphic)
{
	sprite_MegaMan = new Sprite(graphic, MegaManPNG);
	sprite_Effect = new Sprite(graphic, EffectPNG);
	sprite_Weapons_And_Items = new Sprite(graphic, WeaponsAndItemsPNG);
	sprite_Enemy = new Sprite(graphic, EnemyPNG);
	sprite_Lifebar = new Sprite(graphic, WeaponsAndItemsPNG);
	sprite_Boss_Genjibo = new Sprite(graphic, BossGenjiboPNG);

	spriteSheetMegaMan = new SpriteSheet(MegaManXML);
	spriteSheetEffect = new SpriteSheet(EffectXML);
	spriteSheetWeaponsAndItems = new SpriteSheet(WeaponsAndItemsEffectXML);
	spriteSheetEnemy = new SpriteSheet(EnemyXML);
	spriteSheetBossGenjibo = new SpriteSheet(BossGenjiboXML);

	megaMan = new MegaMan(sprite_MegaMan, sprite_Effect, sprite_Weapons_And_Items,
		spriteSheetMegaMan, spriteSheetEffect, spriteSheetWeaponsAndItems);

	mGenjibo = new Genjibo(sprite_Boss_Genjibo, spriteSheetBossGenjibo, D3DXVECTOR2(2480, 870));

	viewport = new Viewport(0, 1248);

	map = new Map(graphic);

	//Tạo quadtree và đọc
	mQuadTree = new QuadTree();
	TiXmlDocument doc(QuadTreeXML);
	if (!doc.LoadFile())
	{
		MessageBox(NULL, "Can't load QuadTree.xml file", "Error", MB_OK);
		return;
	}
	TiXmlElement* root = doc.RootElement();
	ReadQuadTree(root, mQuadTree, NULL, -1);
	mQuadTree->GetObjectsCollideAble(listObjectCollison, listWall, viewport->GetBound());
	prePosView = viewport->GetPosition();

	lifebar = new Lifebar(sprite_Lifebar, spriteSheetWeaponsAndItems);
}

//Update Game
void ObjectManager::Update(float dt, Keyboard* keyboard)
{
	megaMan->ChangeAnimation(dt, keyboard);

	//Kiểm tra va chạm
	if (prePosView != viewport->GetPosition())
	{
		prePosView = viewport->GetPosition();
		listWall.clear();
		//List lưu đối tượng quái còn trong màn hình trước đó
		mQuadTree->GetObjectsCollideAble(listObject, listWall, viewport->GetBound());
		//Đổi 2 vector
		listObjectCollison.swap(listObject);
	}
	listObject.clear();

	//Va chạm Man với tường
	for (size_t i = 0; i < listWall.size(); i++)
	{
		D3DXVECTOR2 disMan = megaMan->Distance(dt);
		megaMan->OnCollision(listWall.at(i), disMan, disMan);
	}

	//Va chạm Object
	for (size_t i = 0; i < listObjectCollison.size(); i++)
	{

		for (size_t j = 0; j < listWall.size(); j++)
		{
			D3DXVECTOR2 disEnemy = listObjectCollison.at(i)->Distance(dt);
			listObjectCollison.at(i)->OnCollision(listWall.at(j), disEnemy);
		}

		//Va chạm của quái
		if (listObjectCollison.at(i)->tag == Object::Tag::Enemys && listObjectCollison.at(i)->GetAllowDraw())
		{
			//Mega Man
			D3DXVECTOR2 disMan = megaMan->Distance(dt);
			D3DXVECTOR2 distance = disMan - listObjectCollison.at(i)->Distance(dt);
			megaMan->OnCollision(listObjectCollison.at(i), distance, disMan);

			//Đạn Mega Man
			for (int j = 0; j < 4; j++)
			{	
				if (megaMan->bullets[j]->GetAllowDraw() && megaMan->bullets[j]->GetBulletState() == Bullet::Firing)
				{
					if (Collision::isCollision(megaMan->bullets[j]->GetBound(), listObjectCollison.at(i)->GetBound()))
					{
						listObjectCollison.at(i)->OnCollision(megaMan->bullets[j]);
						megaMan->bullets[j]->OnCollision();
					}
				}
			}
			//Kiểm tra con quái nào còn trong màn hình và chưa chết
			if (viewport->isContains(listObjectCollison.at(i)->GetBound()))
				listObject.push_back(listObjectCollison.at(i));
		}

		//Update
		listObjectCollison.at(i)->Update(dt, keyboard);
	}

	//Boss
	if (mGenjibo->GetAllowDraw())
	{
		//Va chạm boss với tường
		for (size_t i = 0; i < listWall.size(); i++)
		{
			D3DXVECTOR2 disGenjibo = mGenjibo->Distance(dt);
			mGenjibo->OnCollision(listWall.at(i), disGenjibo);
		}

		//Đạn Mega Man
		for (int i = 0; i < 4; i++)
		{
			if (megaMan->bullets[i]->GetAllowDraw() && megaMan->bullets[i]->GetBulletState() == Bullet::Firing)
			{
				if (Collision::isCollision(megaMan->bullets[i]->GetBound(), mGenjibo->GetBound()))
				{
					mGenjibo->OnCollision(megaMan->bullets[i]);
					megaMan->bullets[i]->OnCollision();
				}
			}
		}
		mGenjibo->Update(dt, keyboard);
	}

	megaMan->Update(dt, keyboard);

	viewport->Update(dt, keyboard, megaMan->GetPosition(), megaMan->GetVelocity(), map->listStage);
}

//Vẽ
void ObjectManager::Render()
{
	map->Render(viewport);

	megaMan->Render(viewport);

	mGenjibo->Render(viewport);

	//Vẽ Object
	for (size_t i = 0; i < listObjectCollison.size(); i++)
	{
		listObjectCollison.at(i)->Render(viewport);
	}

	lifebar->Render(megaMan->GetHP(),megaMan->GetHPMax());

}

bool IsExist(int id, int indexNode, QuadTree *node, QuadTree *father)
{
	if (!father)
		return false;
	for (int i = 0; i < indexNode; i++)
	{
		for (size_t j = 0; j < father->Nodes[i]->mListObject.size(); j++)
		{
			if (father->Nodes[i]->mListObject.at(j)->id == id)
			{
				node->mListObject.push_back(father->Nodes[i]->mListObject.at(j));
				return true;
			}
		}
	}

	return false;
}

void ObjectManager::ReadQuadTree(TiXmlElement *root, QuadTree *node, QuadTree *father, int indexNode)
{
	if (!root)
		return;
	RECT r;
	int left, top, right, bottom, numObj;
	root->QueryIntAttribute("left", &left);
	root->QueryIntAttribute("top", &top);
	root->QueryIntAttribute("right", &right);
	root->QueryIntAttribute("bottom", &bottom);
	r.left = left;
	r.right = right;
	r.top = top;
	r.bottom = bottom;
	node->Bound = r;
	root->QueryIntAttribute("level", &node->mLevel);
	root->QueryIntAttribute("numObj", &numObj);
	TiXmlElement *child = root->FirstChildElement();
	for (size_t i = 0; i < numObj; i++)
	{
		int id;
		child->QueryIntAttribute("id", &id);
		if (!IsExist(id, indexNode, node, father))
		{

			float x, y, w, h;
			child->QueryFloatAttribute("x", &x);
			child->QueryFloatAttribute("y", &y);
			child->QueryFloatAttribute("w", &w);
			child->QueryFloatAttribute("h", &h);

			string name = (char*)child->Attribute("name");
			Object::Tag tag = Object::GetTag(name);
			
			if (name == "HeadGunner")
			{
				HeadGunner *enemy = new HeadGunner(megaMan, sprite_Enemy, sprite_Weapons_And_Items, spriteSheetEnemy, spriteSheetWeaponsAndItems);
				enemy->New(D3DXVECTOR2(x, y));
				enemy->SetName(name);
				enemy->id = id;
				//node->mListObject.push_back(enemy);
			}
			else if (name == "NotorBanger")
			{
				NotorBanger *enemy = new NotorBanger(megaMan, sprite_Enemy, sprite_Weapons_And_Items, spriteSheetEnemy, spriteSheetWeaponsAndItems);
				enemy->New(D3DXVECTOR2(x, y));
				enemy->SetName(name);
				enemy->id = id;
				node->mListObject.push_back(enemy);
			}
			else if (name == "Helit")
			{
				Helit *enemy = new Helit(megaMan, sprite_Enemy, sprite_Weapons_And_Items, spriteSheetEnemy, spriteSheetWeaponsAndItems);
				enemy->New(D3DXVECTOR2(x, y));
				enemy->SetName(name);
				enemy->id = id;
				//node->mListObject.push_back(enemy);
			}
			else
			{
				Object *obj = new Object();
				child->QueryIntAttribute("id", &obj->id);
				obj->SetTag(name);
				obj->SetPosition(D3DXVECTOR2(x, y));
				obj->SetBound(w, h);
				obj->SetName(name);
				obj->SetPositionStart(D3DXVECTOR2(x, y));
				obj->id = id;
				node->mListObject.push_back(obj);
			}
		}
		child = child->NextSiblingElement();
	}
	if (child)
	{
		node->Nodes = new QuadTree*[4];
		for (int i = 0; i < 4; i++)
		{
			node->Nodes[i] = new QuadTree();
			ReadQuadTree(child, node->Nodes[i], node, i);
			child = child->NextSiblingElement();
		}
	}
}
