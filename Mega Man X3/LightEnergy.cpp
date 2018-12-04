#include "LightEnergy.h"


LightEnergy::LightEnergy()
{
}

LightEnergy::LightEnergy(Sprite* sprite_light, SpriteSheet* sprite_sheet)
{
	sprite = sprite_light;
	animationLight = new Animation(sprite_sheet, 11, 23, 1, true);
	allowDraw = false;

	lightType = LightType::BlueLight;

	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	transform = D3DXVECTOR2(0, 0);

}

LightEnergy::~LightEnergy()
{
	delete animationLight;
}

void LightEnergy::NewLight(D3DXVECTOR2 position, bool flipflag, int energyLevel)
{
	switch (energyLevel)
	{
	case 1:
	{
		lightType = BlueLight;
		allowDraw = true;
		break;
	}
	case 2:
	{
		lightType = OrangeLight;
		allowDraw = true;
		break;
	}
	default:
		allowDraw = false;
		break;
	}

	this->position = position;
	this->flipFlag = flipflag;
}

LightEnergy::LightType LightEnergy::GetLightType()
{
	return lightType;
}

void LightEnergy::SetLightType(LightEnergy::LightType lightType)
{
	this->lightType = lightType;
}

void LightEnergy::ChangeAnimation()
{
	switch (lightType)
	{
	case LightEnergy::BlueLight:
	{
		animationLight->SetFrame(position, flipFlag, 1, 11, 23);
		break;
	}

	case LightEnergy::OrangeLight:
	{
		animationLight->SetFrame(position, flipFlag, 1, 24, 39);
		break;
	}
	}
}

void LightEnergy::Update(float dt, Keyboard* key)
{
	if (allowDraw)
	{
		ChangeAnimation();
		animationLight->Update(dt, key);
	}
}

void LightEnergy::Render(Viewport* viewport)
{
	if (allowDraw)
	{
		sprite->SetData(
			animationLight->GetRect(),
			animationLight->GetCenter(),
			animationLight->GetPosition(),
			animationLight->GetScale(),
			animationLight->GetTransform(),
			animationLight->GetAngle()
		);
		sprite->Render(viewport);
	}
}
