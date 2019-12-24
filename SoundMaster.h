#pragma once
enum SoundID {
	LIFT,
	DROP,
	CLICK,
	LINE_CONNECT,
	SLIDE
};

class SoundMaster
{
private:
	int bgmid = -1;

public:
	static SoundMaster* GetInstance();
	
	void PlayEffectSound(SoundID);
	void PlayBGM();
};