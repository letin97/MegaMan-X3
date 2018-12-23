#include "Port.h"

Port::Port()
{
}

Port::Port(Map* *map, MegaMan *man, Sprite* sprite_port, SpriteSheet* spriteSheet_Port, Sound* sound)
{
	//sound
	this->sound = sound;
	tag = Tag::Port;
	sprite = sprite_port;
	animationPort = new Animation(spriteSheet_Port);
	allowDraw = false;
	transform = D3DXVECTOR2(0, 0);
}

Port::~Port()
{
	delete sprite;
	delete animationPort;

	delete sound;
}
void Port::New()
{
	allowDraw = true;
	HP = 5;
	SetBound(48, 48);
}
//Tạo port mới
void Port::NewPort(D3DXVECTOR2 pos)
{
	allowDraw = true;
	position = pos;
}

void Port::ChangeAnimation(Keyboard* key)
{
	
}

void  Port::OnCollision()
{
	
}

void Port::Update(float dt, Keyboard *key)
{
	ChangeAnimation(key);
	animationPort->Update(dt, key);
}

void Port::Render(Viewport *view)
{
	if (allowDraw)
	{
		sprite->SetData(
			animationPort->GetRect(),
			animationPort->GetCenter(),
			animationPort->GetPosition(),
			animationPort->GetScale(),
			animationPort->GetTransform(),
			animationPort->GetAngle()
		);
		sprite->Render(view);
	}
}