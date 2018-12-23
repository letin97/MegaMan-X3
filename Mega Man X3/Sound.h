#pragma once

#include "dsutil.h"

class Sound
{
protected:
	HWND hwnd;
	GSoundManager *dsound;
public:
	Sound(HWND);
	~Sound();

	bool Init_DirectSound();
	GSound *LoadSound(LPTSTR);
	void PlaySound(GSound *);
	void LoopSound(GSound *);
	void StopSound(GSound *);

};

