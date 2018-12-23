#include "Sound.h"

Sound::Sound(HWND Hwnd)
{
	this->hwnd = Hwnd;
	this->dsound = NULL;

}

Sound::~Sound()
{

}

bool Sound::Init_DirectSound()
{
	HRESULT result;

	//Tạo 1 quản lý sound
	dsound = new GSoundManager();

	//Khởi tạo 1 dsound
	result = dsound->Initialize(hwnd, DSSCL_PRIORITY);

	if (result != DS_OK)
	{

		return false;
	}

	//Tạo định dạng đệm mặc định
	result = dsound->SetPrimaryBufferFormat(2, 22050, 16);

	if (result != DS_OK)
	{
		return false;
	}
	//Hoàn thành
	return true;
}

GSound* Sound::LoadSound(LPTSTR filename)
{
	HRESULT result;

	//Tạo dữ liệu nhạc
	GSound *wave;

	//Load 1 tệp nhạc lên
	result = dsound->Create(&wave, filename);

	if (result != DS_OK)
	{
		return NULL;
	}

	//Đã load đc nhạc
	return wave;
}

//Chạy nhạc
void Sound::PlaySound(GSound *sound)
{
	sound->Play();
}

//Lặp lại nhạc
void Sound::LoopSound(GSound *sound)
{
	sound->Play(0, DSBPLAY_LOOPING);
}

//Dừng nhạc
void Sound::StopSound(GSound *sound)
{
	sound->Stop();
}