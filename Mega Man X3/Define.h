#pragma once

namespace Define
{
	const float WinWidth = 500.0f;
	const float WinHeight = 500.0f;

	const float GameWidth = 256.0f;
	const float GameHeight = 224.0f;

	//MegaMan
	const char MegaManPNG[] = "./Resource Files/MegaMan.png";
	const char MegaManXML[] = "./Resource Files/MegaMan.xml";

	//Effect
	const char EffectPNG[] = "./Resource Files/Effect.png";
	const char EffectXML[] = "./Resource Files/Effect.xml";

	//Bullet
	const char WeaponsAndItemsPNG[] = "./Resource Files/Weapons and Items.png";
	const char WeaponsAndItemsEffectXML[] = "./Resource Files/Weapons and Items.xml";

	//Enemy
	const char EnemyPNG[] = "./Resource Files/Enemy.png";
	const char EnemyXML[] = "./Resource Files/Enemy.xml";

	//Map
	const char TileSetPNG[] = "./Resource Files/megaman_x3__blast_hornet_stage_by_darksamus993-d8lave3.png";
	const char MapXML[] = "./Resource Files/Map.tmx";

	//QuadTree
	const char QuadTreeXML[] = "./Resource Files/QuadTree.xml";

	//Speed
	const float RunSpeed = 2.0f;
	const float GlideSpeed = 3.0f;
	const float JumpSpeed = 3.0f;
	const float ClampSpeed = 0.8f;
	const float KickSpeed = 1.0f;
	const float BulletSpeed = 4.0f;
	const float Gravity = 1.0f;
	const float FallAcceleration = 0.05f;

	//Distance
	const float JumpMax = 80.0f;
	const float JumpMin = 50.0f;
	const float GlideMax = 150.0f;
	const float GlideMin = 30.f;

	//Time
	const float DelayAnimation = 0.2f;
	const float TimeBulletLv2 = 0.3f;
	const float TimeBulletLv3 = 1.0f;
	const float TimeItem = 4.0f;
}