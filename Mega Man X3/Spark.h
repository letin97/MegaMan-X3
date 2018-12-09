#pragma once
#include "Object.h"
#include "Animation.h"
#include "Define.h"
using namespace Define;

class Spark : public Object
{
protected:

	Animation* animationSpark;
	bool isDone = false;

public:

	enum SparkType
	{
		Dash,
		Jounce,
	};
	SparkType sparkType;

	Spark();
	Spark(Sprite* sprite_spark, SpriteSheet* sprite_sheet);
	~Spark();

	void NewSpark(D3DXVECTOR2 position, bool flipflag, int type);

	bool GetIsDone();
	void SetIsDone(bool b);

	void ChangeAnimation();
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
};
