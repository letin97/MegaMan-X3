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
	const char LightEnergyPNG[] = "./Resource Files/Light Energy.png";
	const char LightEnergyXML[] = "./Resource Files/Light Energy.xml";
	const char SparkPNG[] = "./Resource Files/Spark.png";
	const char SparkXML[] = "./Resource Files/Spark.xml";
	const char SmokePNG[] = "./Resource Files/Smoke.png";
	const char SmokeXML[] = "./Resource Files/Smoke.xml";
	const char ExplosionPNG[] = "./Resource Files/Explosion.png";
	const char ExplosionXML[] = "./Resource Files/Explosion.xml";

	//Bullet
	const char WeaponsAndItemsPNG[] = "./Resource Files/Weapons and Items.png";
	const char WeaponsAndItemsEffectXML[] = "./Resource Files/Weapons and Items.xml";

	//Enemy
	const char HeadGunnerPNG[] = "./Resource Files/HeadGunner.png";
	const char HeadGunnerXML[] = "./Resource Files/HeadGunner.xml";
	const char NotorBangerPNG[] = "./Resource Files/NotorBanger.png";
	const char NotorBangerXML[] = "./Resource Files/NotorBanger.xml";
	const char HelitPNG[] = "./Resource Files/Helit.png";
	const char HelitXML[] = "./Resource Files/Helit.xml";

	//Boss
	const char BossGenjiboPNG[] = "./Resource Files/Genjibo.png";
	const char BossGenjiboXML[] = "./Resource Files/Genjibo.xml";
	const char BossBytePNG[] = "./Resource Files/Byte.png";
	const char BossByteXML[] = "./Resource Files/Byte.xml";
	const char BossBlastHornetPNG[] = "./Resource Files/BlastHornet.png";
	const char BossBlastHornetXML[] = "./Resource Files/BlastHornet.xml";

	//Map
	const char TileSetPNG[] = "./Resource Files/Blast Hornet Stage.png";
	const char MapXML[] = "./Resource Files/Map.tmx";

	//Sound
	const LPTSTR BlastHornetSound = "./Resource Files/Sound/09 Blast Hornet.wav";
	const LPTSTR Bullet1Sound = "./Resource Files/Sound/SE_01.wav";
	const LPTSTR Bullet2Sound = "./Resource Files/Sound/SE_05.wav";
	const LPTSTR Bullet3Sound = "./Resource Files/Sound/SE_06.wav";

	//Port
	const char PortPNG[] = "./Resource Files/Port.png";
	const char PortXML[] = "./Resource Files/Port.xml";

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
	const float GlideMax = 100.0f;
	const float GlideMin = 30.f;

	//Time
	const float DelayAnimation = 0.2f;
	const float TimeBulletLv2 = 0.3f;
	const float TimeBulletLv3 = 1.0f;
	const float TimeItem = 4.0f;
}