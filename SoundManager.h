#pragma once

using namespace std;
using namespace std::experimental::filesystem;

#define     BUFSIZE    1048576*60

enum SoundType {
	ST_Wave,
	ST_Ogg,
};

struct Sound {
	SoundType type;
	Sound(SoundType type) :type(type) {}
	virtual ~Sound() {}
};
struct OggSound : public Sound
{
	LPDIRECTSOUNDBUFFER	buffer;
	BOOL				isLoaded;
	BOOL				isLoop;
	int					id;

	OggSound()
		:Sound(ST_Ogg)
	{
		isLoaded = FALSE;
		isLoop = FALSE;
		buffer = NULL;
		id = NULL;
	}
	~OggSound()
	{
		buffer->Release();
	}

};
struct WaveSound : public Sound
{
	LPDIRECTSOUNDBUFFER	buffer;
	BOOL				isLoaded;
	int				isLoop;
	DWORD			dwSize;
	BYTE*			pData;
	int				id;
	WAVEFORMATEX		format;

	WaveSound()
		:Sound(ST_Wave)
	{
		isLoaded = FALSE;
		isLoop = FALSE;
		buffer = NULL;
		id = NULL;
		dwSize = 0;
	}
	~WaveSound()
	{
		buffer->Release();
	}
};
class SoundManager
{
private:
	map<SoundID, Sound*> sounds_;

	LPDIRECTSOUND8		dsound_;
	OggVorbis_File		oggVorbisFile_;

public:
	SoundManager();
	~SoundManager();

	//OnCreate(HWND hWnd);
	//OnRelease();

public:
	int volume;

	Sound* Load(SoundID id, const path& filePath);
	void Unload(SoundID id);
	//loop : 반복할지 
	//reset : 이미 재생되고 있으면 멈추고 다시 재생할지 
	void Play(SoundID id, bool loop = false, bool reset = false);
	void Stop(SoundID id);
	bool IsPlaying(SoundID id);
	void UnloadAll();
	//loop= true인 것들 갱신
	void Update();
};