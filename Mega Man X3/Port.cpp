#include "Port.h"

Port::Port()
{
}

Port::Port(MegaMan *man, Sprite* sprite_port, SpriteSheet* spriteSheet_Port, Sound* sound)
{
	//sound
	this->sound = sound;
	this->megaMan = man;
	tag = Tag::Port;
	sprite = sprite_port;
	animation = new Animation(spriteSheet_Port);
	allowDraw = false;
	transform = D3DXVECTOR2(0, 0);
}

Port::~Port()
{
	delete sprite;
	delete animation;

	delete sound;
}

void Port::New()
{
	if (state != Closing)
		active = false;
}

void Port::New(D3DXVECTOR2 pos)
{
	allowDraw = true;
	position = pos;
	SetBound(16, 48);
	state = Init;
}

void Port::ChangeAnimation(Keyboard* key)
{
	switch (state)
	{
	case Port::Init:
		animation->SetFrame(position, flipFlag, 0, 16, 16, false);
		break;
	case Port::Closing:
		animation->SetFrame(position, flipFlag, 3, 0, 16, false);
		break;
	case Port::Opening:
		animation->SetFrame(position, flipFlag, 3, 17, 33, false);
		break;
	}
}

void Port::OnCollision()
{
	if (!slip)
		active = true;
}

void Port::Update(float dt, Keyboard *key)
{
	ChangeAnimation(key);
	animation->Update(dt, key);

	if (active) return;

	if (!slip && Collision::isCollision(megaMan->GetBound(), GetBound()))
	{
		slip = true;
		state = Opening;
		megaMan->LockAnimation(true);
	}

	if (slip)
	{
		if (megaMan->GetPosition().x > position.x && moveStage)
			megaMan->SetVelocityX(0.0f);
		else
			megaMan->SetVelocityX(0.2f);

		if (megaMan->GetBound().left > position.x + 32)
		{
			megaMan->LockAnimation(false);
			slip = false;
			active = true;
			position.x += 16;
			state = Closing;
		}
	}
}

void Port::Render(Viewport *view)
{
	if (position.x > view->GetStart())
		moveStage = false;
	else
		moveStage = true;

	if (allowDraw)
	{
		sprite->SetData(
			animation->GetRect(),
			animation->GetCenter(),
			animation->GetPosition(),
			animation->GetScale(),
			animation->GetTransform(),
			animation->GetAngle()
		);
		sprite->Render(view);
	}
}