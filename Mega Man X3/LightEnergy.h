#pragma once
#include "Object.h"
#include "Animation.h"
#include "Define.h"
using namespace Define;

class LightEnergy : public Object
{
protected:

	Animation* animationLight;

public:
	enum LightType
	{
		BlueLight,
		OrangeLight,
	};
	LightType lightType;

	LightEnergy();
	LightEnergy(Sprite* sprite_light, SpriteSheet* sprite_sheet);
	~LightEnergy();

	void NewLight(D3DXVECTOR2 position, bool flipflag, int energyLevel);

	LightType GetLightType();
	void SetLightType(LightType lightType);
	void ChangeAnimation();
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
};