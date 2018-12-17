#include "Spark.h"


Spark::Spark()
{
}

Spark::Spark(Sprite* sprite_spark, SpriteSheet* sprite_sheet)
{
	sprite = sprite_spark;
	animationSpark = new Animation(sprite_sheet, 0, 4, 5, false);
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

void Spark::NewSpark(D3DXVECTOR2 position, bool flipflag, int type)
{
	switch (type)
	{
	case 1:
	{
		sparkType = Dash;
		allowDraw = true;
		break;
	}
	case 2:
	{
		sparkType = Jounce;
		allowDraw = true;
		break;
	}
	default:
		allowDraw = false;
		break;
	}

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
	switch (sparkType)
	{
	case SparkType::Dash:
	{
		animationSpark->SetFrame(position, flipFlag, 5, 0, 4);
		break;
	}
	case SparkType::Jounce:
	{
		animationSpark->SetFrame(position, flipFlag, 5, 5, 13);
		break;
	}
	}
	
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
