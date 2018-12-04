#include "Spark.h"


Spark::Spark()
{
}

Spark::Spark(Sprite* sprite_spark, SpriteSheet* sprite_sheet)
{
	sprite = sprite_spark;
	animationSpark = new Animation(sprite_sheet, 6, 10, 10, false);
	allowDraw = false;
	isDone = false;

	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	transform = D3DXVECTOR2(0, 0);

}

Spark::~Spark()
{
	delete animationSpark;
}

void Spark::NewSpark(D3DXVECTOR2 position, bool flipflag)
{
	this->allowDraw = true;
	this->position = position;
	this->flipFlag = flipflag;
}

bool Spark::GetIsDone()
{
	return isDone;
}

void Spark::SetIsDone(bool b)
{
	isDone = b;
}


void Spark::ChangeAnimation()
{
	animationSpark->SetFrame(position, flipFlag, 10, 6, 10);
	if (animationSpark->GetIndex() == animationSpark->GetEnd())
	{
		allowDraw = false;
		isDone = true;
		animationSpark->SetIndex(animationSpark->GetStart());
	}
}

void Spark::Update(float dt, Keyboard* key)
{
	if (allowDraw)
	{
		ChangeAnimation();
		animationSpark->Update(dt, key);
	}
}

void Spark::Render(Viewport* viewport)
{
	if (allowDraw)
	{
		sprite->SetData(
			animationSpark->GetRect(),
			animationSpark->GetCenter(),
			animationSpark->GetPosition(),
			animationSpark->GetScale(),
			animationSpark->GetTransform(),
			animationSpark->GetAngle()
		);
		sprite->Render(viewport);
	}
}
