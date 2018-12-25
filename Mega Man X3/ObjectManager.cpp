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
	delete sprite_LightEnergy;
	delete sprite_Spark;
	delete sprite_Smoke;
	delete sprite_Explosion;
	delete sprite_Weapons_And_Items;
	delete sprite_HeadGunner;
	delete sprite_NotorBanger;
	delete sprite_Helit;
	delete sprite_Genjibo;
	delete sprite_Byte;
	delete sprite_BlastHornet;
	delete sprite_Elevator;
	delete sprite_Port;

	delete mGenjibo;
	delete mByte;
	delete mBlastHornet;
	delete mElevator;

}

//Load Game
void ObjectManager::Init(Graphic* graphic, Sound *sound)
{
	this->sound = sound;
	soundBlastHornet = sound->LoadSound(BlastHornetSound);

	//Player
	sprite_MegaMan = new Sprite(graphic, MegaManPNG);
	spriteSheet_MegaMan = new SpriteSheet(MegaManXML);

	//Effect
	sprite_LightEnergy = new Sprite(graphic, LightEnergyPNG);
	sprite_Spark = new Sprite(graphic, SparkPNG);
	sprite_Smoke = new Sprite(graphic, SmokePNG);
	sprite_Explosion = new Sprite(graphic, ExplosionPNG);
	spriteSheet_LightEnergy = new SpriteSheet(LightEnergyXML);
	spriteSheet_Spark = new SpriteSheet(SparkXML);
	spriteSheet_Smoke = new SpriteSheet(SmokeXML);
	spriteSheet_Explosion = new SpriteSheet(ExplosionXML);

	//Bullet Item
	sprite_Weapons_And_Items = new Sprite(graphic, WeaponsAndItemsPNG);
	spriteSheet_Weapons_And_Items = new SpriteSheet(WeaponsAndItemsEffectXML);

	//Enemy
	sprite_HeadGunner = new Sprite(graphic, HeadGunnerPNG);
	sprite_NotorBanger = new Sprite(graphic, NotorBangerPNG);
	sprite_Helit = new Sprite(graphic, HelitPNG);
	spriteSheet_HeadGunner = new SpriteSheet(HeadGunnerXML);
	spriteSheet_NotorBanger = new SpriteSheet(NotorBangerXML);
	spriteSheet_Helit = new SpriteSheet(HelitXML);

	//Boss
	sprite_Genjibo = new Sprite(graphic, BossGenjiboPNG);
	sprite_Byte = new Sprite(graphic, BossBytePNG);
	sprite_BlastHornet = new Sprite(graphic, BossBlastHornetPNG);
	spriteSheet_Genjibo = new SpriteSheet(BossGenjiboXML);
	spriteSheet_Byte = new SpriteSheet(BossByteXML);
	spriteSheet_BlastHornet = new SpriteSheet(BossBlastHornetXML);

	//Elevator
	sprite_Elevator = new Sprite(graphic, ElevatorPNG);
	spriteSheet_Elevator = new SpriteSheet(ElevatorXML);

	//Port
	sprite_Port = new Sprite(graphic, PortPNG);
	spriteSheet_Port = new SpriteSheet(PortXML);

	//Lifebar
	sprite_Lifebar = new Sprite(graphic, WeaponsAndItemsPNG);
	
	megaMan = new MegaMan(sprite_MegaMan, sprite_LightEnergy, sprite_Spark, sprite_Smoke, sprite_Weapons_And_Items,
		spriteSheet_MegaMan, spriteSheet_LightEnergy, spriteSheet_Spark, spriteSheet_Smoke, spriteSheet_Weapons_And_Items,
		sound);

	//2480 870
	mGenjibo = new Genjibo(sprite_Genjibo, spriteSheet_Genjibo, D3DXVECTOR2(2480, 870));

	mByte = new Byte(sprite_Byte, sprite_Smoke, sprite_Explosion,spriteSheet_Byte, spriteSheet_Smoke, spriteSheet_Explosion, sound, D3DXVECTOR2(5830, 890));

	mBlastHornet = new BlastHornet(megaMan, sprite_BlastHornet, spriteSheet_BlastHornet, D3DXVECTOR2(7880, 180));

	mElevator = new Elevator(megaMan, sprite_Elevator, spriteSheet_Elevator, sound, D3DXVECTOR2(896, 1086));

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

	lifebar = new Lifebar(sprite_Lifebar, spriteSheet_Weapons_And_Items);
}

//Update Game
void ObjectManager::Update(float dt, Keyboard* keyboard)
{
	megaMan->ChangeAnimation(dt, keyboard);

	//Kiểm tra dịch chuyển
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

#pragma region Object

	//Object
	for (size_t i = 0; i < listObjectCollison.size(); i++)
	{
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
		//Tường
		for (size_t j = 0; j < listWall.size(); j++)
		{
			D3DXVECTOR2 disEnemy = listObjectCollison.at(i)->Distance(dt);
			listObjectCollison.at(i)->OnCollision(listWall.at(j), disEnemy);
		}
		//Update
		listObjectCollison.at(i)->Update(dt, keyboard);
	}

#pragma endregion

#pragma region Genjibo

	//Boss Genjibo
	if (mGenjibo->GetAllowDraw())
	{
		//MegaMan
		D3DXVECTOR2 disMan = megaMan->Distance(dt);
		D3DXVECTOR2 distance = disMan - mGenjibo->Distance(dt);
		megaMan->OnCollision(mGenjibo, distance, disMan);

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
		//Tường
		for (size_t i = 0; i < listWall.size(); i++)
		{
			D3DXVECTOR2 disGenjibo = mGenjibo->Distance(dt);
			mGenjibo->OnCollision(listWall.at(i), disGenjibo);
		}
		//Update
		mGenjibo->Update(dt, keyboard);
	}

	//Kiểm tra xuất hiện
	if (Collision::isCollision(megaMan->GetPosition().x, megaMan->GetPosition().y, mGenjibo->stage))
		mGenjibo->SetAllowDraw(true);
	else
		mGenjibo->SetAllowDraw(false);

#pragma endregion

#pragma region Byte

	//Boss Byte
	if (mByte->GetAllowDraw())
	{
		//MegaMan
		D3DXVECTOR2 disMan = megaMan->Distance(dt);
		D3DXVECTOR2 distance = disMan - mByte->Distance(dt);
		megaMan->OnCollision(mByte, distance, disMan);

		//Đạn MegaMan
		for (int i = 0; i < 4; i++)
		{
			if (megaMan->bullets[i]->GetAllowDraw() && megaMan->bullets[i]->GetBulletState() == Bullet::Firing)
			{
				if (Collision::isCollision(megaMan->bullets[i]->GetBound(), mByte->GetBound()))
				{
					mByte->OnCollision(megaMan->bullets[i]);
					megaMan->bullets[i]->OnCollision();
				}
			}
		}
		
		//Tường
		for (size_t i = 0; i < listWall.size(); i++)
		{
			//Boss
			D3DXVECTOR2 disByte = mByte->Distance(dt);
			mByte->OnCollision(listWall.at(i), disByte);

			//Đạn boss
			D3DXVECTOR2 disBulletByte = mByte->bullet->Distance(dt);
			mByte->bullet->OnCollision(listWall.at(i), disBulletByte);
		}
		//Update
		mByte->Update(dt, keyboard);
	}

	//Kiểm tra xuất hiện
	if (Collision::isCollision(megaMan->GetPosition().x, megaMan->GetPosition().y, mByte->stage))
		mByte->SetAllowDraw(true);
	else
		mByte->SetAllowDraw(false);

#pragma endregion
		
#pragma region Blast Hornet

	//Boss BlastHornet
	if (mBlastHornet->GetAllowDraw())
	{
		//MegaMan
		D3DXVECTOR2 disMan = megaMan->Distance(dt);
		D3DXVECTOR2 distance = disMan - mBlastHornet->Distance(dt);
		megaMan->OnCollision(mBlastHornet, distance, disMan);

		//Đạn MegaMan
		for (int i = 0; i < 4; i++)
		{
			if (megaMan->bullets[i]->GetAllowDraw() && megaMan->bullets[i]->GetBulletState() == Bullet::Firing)
			{
				if (Collision::isCollision(megaMan->bullets[i]->GetBound(), mBlastHornet->GetBound()))
				{
					mBlastHornet->OnCollision(megaMan->bullets[i]);
					megaMan->bullets[i]->OnCollision();
				}

				for (int j = 0; j < 5; j++)
				{
					if (Collision::isCollision(megaMan->bullets[i]->GetBound(), mBlastHornet->listBee[j]->GetBound()))
					{
						megaMan->bullets[i]->OnCollision();
						mBlastHornet->listBee[j]->OnCollision(megaMan->bullets[i]);
					}
				}
			}
		}

		//Tường
		for (size_t i = 0; i < listWall.size(); i++)
		{
			D3DXVECTOR2 disBlastHornet = mBlastHornet->Distance(dt);
			mBlastHornet->OnCollision(listWall.at(i), disBlastHornet);

			for (int j = 0; j < 5; j++)
			{
				D3DXVECTOR2 disBee = mBlastHornet->listBee[j]->Distance(dt);
				mBlastHornet->listBee[j]->OnCollision(listWall.at(i), disBee);
			}
		}
		//Update
		mBlastHornet->Update(dt, keyboard);
	}

	//Kiểm tra xuất hiện
	if (Collision::isCollision(megaMan->GetPosition().x, megaMan->GetPosition().y, mBlastHornet->stage))
		mBlastHornet->SetAllowDraw(true);
	else
		mBlastHornet->SetAllowDraw(false);

#pragma endregion

#pragma region Elevator

	//Elevator
	if (mElevator->GetAllowDraw())
	{
		mElevator->OnCollision(megaMan);
		//MegaMan
		D3DXVECTOR2 disMan = megaMan->Distance(dt);
		D3DXVECTOR2 distance = disMan - mElevator->Distance(dt);
		megaMan->OnCollision(mElevator, distance, disMan);
		mElevator->Update(dt, keyboard);
	}

#pragma endregion

#pragma region MegaMan

	//Va chạm Man với tường
	for (size_t i = 0; i < listWall.size(); i++)
	{
		D3DXVECTOR2 disMan = megaMan->Distance(dt);
		megaMan->OnCollision(listWall.at(i), disMan, disMan);

		//Kiểm tra cổng
		if (listWall.at(i)->tag == Object::Port)
		{
			if (mGenjibo->GetAllowDraw() || mByte->GetAllowDraw())
				listWall.at(i)->OnCollision();
			else
				listWall.at(i)->New();
		}

		listWall.at(i)->Update(dt, keyboard);
	}

	megaMan->Update(dt, keyboard);

#pragma endregion

	viewport->Update(dt, keyboard, megaMan->GetPosition(), megaMan->GetVelocity(), map->listStage);

	sound->LoopSound(soundBlastHornet);
}

//Vẽ
void ObjectManager::Render()
{
	map->Render(viewport);

	megaMan->Render(viewport);

	mGenjibo->Render(viewport);

	mByte->Render(viewport);

	mBlastHornet->Render(viewport);

	mElevator->Render(viewport);

	//Vẽ Object
	for (size_t i = 0; i < listObjectCollison.size(); i++)
		listObjectCollison.at(i)->Render(viewport);

	//Vẽ Port
	for (size_t i = 0; i < listWall.size(); i++)
		listWall.at(i)->Render(viewport);

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
				HeadGunner *enemy = new HeadGunner(megaMan, sprite_HeadGunner, sprite_Weapons_And_Items, sprite_Explosion,
					spriteSheet_HeadGunner, spriteSheet_Weapons_And_Items, spriteSheet_Explosion, sound);
				enemy->New(D3DXVECTOR2(x, y));
				enemy->SetName(name);
				enemy->id = id;
				node->mListObject.push_back(enemy);
			}
			else if (name == "HeadGunnerFlip")
			{
				HeadGunner *enemy = new HeadGunner(megaMan, sprite_HeadGunner, sprite_Weapons_And_Items, sprite_Explosion,
					spriteSheet_HeadGunner, spriteSheet_Weapons_And_Items, spriteSheet_Explosion, sound);
				enemy->SetFlipFlag(true);
				enemy->New(D3DXVECTOR2(x, y));
				enemy->SetName(name);
				enemy->id = id;
				node->mListObject.push_back(enemy);
			}
			else if (name == "NotorBanger")
			{
				NotorBanger *enemy = new NotorBanger(megaMan, sprite_NotorBanger, sprite_Weapons_And_Items, sprite_Explosion,
					spriteSheet_NotorBanger, spriteSheet_Weapons_And_Items, spriteSheet_Explosion, sound);
				enemy->New(D3DXVECTOR2(x, y));
				enemy->SetName(name);
				enemy->id = id;
				node->mListObject.push_back(enemy);
			}
			else if (name == "NotorBangerFlip")
			{
				NotorBanger *enemy = new NotorBanger(megaMan, sprite_NotorBanger, sprite_Weapons_And_Items, sprite_Explosion,
					spriteSheet_NotorBanger, spriteSheet_Weapons_And_Items, spriteSheet_Explosion, sound);
				enemy->SetFlipFlag(true);
				enemy->New(D3DXVECTOR2(x, y));
				enemy->SetName(name);
				enemy->id = id;
				node->mListObject.push_back(enemy);
			}
			else if (name == "Helit")
			{
				Helit *enemy = new Helit(megaMan, sprite_Helit, sprite_Weapons_And_Items, sprite_Explosion,
					spriteSheet_Helit, spriteSheet_Weapons_And_Items, spriteSheet_Explosion, sound);
				enemy->New(D3DXVECTOR2(x, y));
				enemy->SetName(name);
				enemy->id = id;
				node->mListObject.push_back(enemy);
			}
			else if (name == "HelitFlip")
			{
				Helit *enemy = new Helit(megaMan, sprite_Helit, sprite_Weapons_And_Items, sprite_Explosion,
					spriteSheet_Helit, spriteSheet_Weapons_And_Items, spriteSheet_Explosion, sound);
				enemy->SetFlipFlag(true);
				enemy->New(D3DXVECTOR2(x, y));
				enemy->SetName(name);
				enemy->id = id;
				node->mListObject.push_back(enemy);
			}
			else if (name == "Port")
			{
				Port *port = new Port(megaMan, sprite_Port, spriteSheet_Port, sound);
				port->New(D3DXVECTOR2(x, y));
				port->SetName(name);
				port->id = id;
				node->mListObject.push_back(port);
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
