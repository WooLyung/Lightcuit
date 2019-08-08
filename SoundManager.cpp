#include "stdafx.h"
#include "SoundManager.h"
#include "Engine.h"

SoundManager::SoundManager()
{
	volume = 3;
	DirectSoundCreate8(NULL, &dsound_, NULL);

	dsound_->Initialize(NULL);
	dsound_->SetCooperativeLevel(RG2R_WindowM->GetHwnd(), DSSCL_PRIORITY);
}

SoundManager::~SoundManager()
{
	UnloadAll();
	dsound_->Release();
}

Sound* SoundManager::Load(SoundID id, const path& filePath)
{

	if (!sounds_[id])
	{
		if (filePath.extension() == ".ogg")
		{
			sounds_[id] = new OggSound();

			LPDIRECTSOUNDBUFFER  pTemp;

			FILE *f;
			fopen_s(&f, filePath.string().c_str(), "rb");

			if (!f) return nullptr;


			ov_open(f, &oggVorbisFile_, NULL, 0);

			// vorbis의 ov_info()함수를 이용 Ogg 정보 얻어오기
			vorbis_info *vi = ov_info(&oggVorbisFile_, -1);

			// DX SDK에서 지원하는 wave헤더 구조체
			WAVEFORMATEX        wfm;

			// wave header 셋팅 후 Ogg파일에서 가져온 정보를 이용하여 채워준다
			memset(&wfm, 0, sizeof(wfm));
			wfm.cbSize = sizeof(wfm);
			wfm.nChannels = vi->channels;
			wfm.wBitsPerSample = 16;									// ogg vorbis는 항상 16bit
			wfm.nSamplesPerSec = vi->rate;
			wfm.nAvgBytesPerSec = wfm.nSamplesPerSec*wfm.nChannels * 2;	// 테이터사이즈 셋팅
			wfm.nBlockAlign = 2 * wfm.nChannels;
			wfm.wFormatTag = 1;

			// set up the buffer
			DSBUFFERDESC desc;

			desc.dwSize = sizeof(desc);
			desc.dwFlags = 0;
			desc.lpwfxFormat = &wfm;
			desc.dwReserved = 0;
			desc.dwBufferBytes = BUFSIZE;


			// CREATE TEMPORARY BUFFER
			dsound_->CreateSoundBuffer(&desc, &pTemp, NULL);

			DWORD   size = BUFSIZE;
			DWORD   pos = 0;
			int     sec = 0;
			int     ret = 1;

			char    *buf;
			char    *buf2;

			pTemp->Lock(0, size, (LPVOID*)&buf, &size, NULL, NULL, DSBLOCK_ENTIREBUFFER);

			// 위에서 채워논 Ogg->wav 컨버전 헤더파일과
			// vorbis의 ov_read함수를 이용 Ogg->wav파일로 컨버팅 한다
			while (ret && pos<size)
			{
				ret = ov_read(&oggVorbisFile_, buf + pos, size - pos, 0, 2, 1, &sec);
				pos += ret;
			}

			pTemp->Unlock(buf, size, NULL, NULL);

			//CREATE BUFFER TO MATCH ACTUAL SIZE OF FILE
			desc.dwBufferBytes = pos;

			dsound_->CreateSoundBuffer(&desc, &((OggSound*)sounds_[id])->buffer, NULL);
			((OggSound*)sounds_[id])->buffer->Lock(0, pos, (LPVOID*)&buf2, &pos, NULL, NULL, DSBLOCK_ENTIREBUFFER);
			CopyMemory(buf2, buf, pos);
			((OggSound*)sounds_[id])->buffer->Unlock(buf2, size, NULL, NULL);

			//DUMP THE TEMP BUFFER
			pTemp->Release();

			((OggSound*)sounds_[id])->id = id;

			// vorbis를 이용 Ogg정보를 다 사용한후 삭제해준다.
			ov_clear(&oggVorbisFile_);
			fclose(f);

			buf = NULL;
		}
		else if (filePath.extension() == ".wav")
		{
			HMMIO wavefile;
			wavefile = mmioOpenA(const_cast<LPSTR>(filePath.string().c_str()), 0, MMIO_READ | MMIO_ALLOCBUF);

			if (wavefile == NULL)
			{
				return nullptr;
			}

			MMCKINFO parent;
			memset(&parent, 0, sizeof(MMCKINFO));
			parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
			if (mmioDescend(wavefile, &parent, 0, MMIO_FINDRIFF))
			{
				mmioClose(wavefile, 0);
				return nullptr;
			}

			MMCKINFO child;
			memset(&child, 0, sizeof(MMCKINFO));
			child.fccType = mmioFOURCC('f', 'm', 't', ' ');
			if (mmioDescend(wavefile, &child, &parent, 0))
			{
				mmioClose(wavefile, 0);
				return nullptr;
			}


			mmioRead(wavefile, (char*)&((WaveSound*)sounds_[id])->format, sizeof(WAVEFORMATEX));

			if (((WaveSound*)sounds_[id])->format.wFormatTag != WAVE_FORMAT_PCM)
			{
				mmioClose(wavefile, 0);
				return nullptr;
			}

			mmioAscend(wavefile, &child, 0);
			child.ckid = mmioFOURCC('d', 'a', 't', 'a');
			if (mmioDescend(wavefile, &child, &parent, MMIO_FINDCHUNK))
			{
				mmioClose(wavefile, 0);
				return nullptr;
			}

			((WaveSound*)sounds_[id])->dwSize = child.cksize;
			((WaveSound*)sounds_[id])->pData = (BYTE*)malloc(((WaveSound*)sounds_[id])->dwSize);

			if (((WaveSound*)sounds_[id])->pData == NULL)
			{
				mmioClose(wavefile, 0);
				return nullptr;
			}

			DSBUFFERDESC bufdesc;
			memset(&bufdesc, 0, sizeof(DSBUFFERDESC));
			bufdesc.dwSize = sizeof(DSBUFFERDESC);
			bufdesc.dwFlags = 0;
			bufdesc.dwBufferBytes = ((WaveSound*)sounds_[id])->dwSize;
			bufdesc.lpwfxFormat = &((WaveSound*)sounds_[id])->format;

			if ((dsound_->CreateSoundBuffer(&bufdesc, &((WaveSound*)sounds_[id])->buffer, NULL)) != DS_OK)
			{
				mmioClose(wavefile, 0);
				return nullptr;
			}

			void *write1 = 0, *write2 = 0;
			unsigned long length1, length2;
			((WaveSound*)sounds_[id])->buffer->Lock(0, ((WaveSound*)sounds_[id])->dwSize, &write1, &length1, &write2, &length2, 0);
			if (write1 > 0)
				mmioRead(wavefile, (char*)write1, length1);
			if (write2 > 0)
				mmioRead(wavefile, (char*)write1, length2);
			((WaveSound*)sounds_[id])->buffer->Unlock(write1, length1, write2, length2);

			mmioClose(wavefile, 0);

			((WaveSound*)sounds_[id])->id = id;
		}

	}

	return sounds_[id];
}
void SoundManager::Unload(SoundID id)
{
	delete sounds_[id];
}

VOID SoundManager::UnloadAll()
{
	for (auto i : sounds_)
	{
		delete i.second;
	}
}

void SoundManager::Play(SoundID id, bool loop, bool reset)
{
	if (reset)
	{
		if (sounds_[id]->type == ST_Ogg)
			((OggSound*)sounds_[id])->buffer->SetCurrentPosition(0);
		else if (sounds_[id]->type == ST_Wave)
			((WaveSound*)sounds_[id])->buffer->SetCurrentPosition(0);
	}
	if (IsPlaying(id))
	{
		return;
	}
	if (sounds_[id]->type == ST_Ogg)
	{
		((OggSound*)sounds_[id])->buffer->SetVolume(volume);
		((OggSound*)sounds_[id])->buffer->Play(0, 0, NULL);
		((OggSound*)sounds_[id])->isLoop = loop;
	}
	else if (sounds_[id]->type == ST_Wave)
	{
		((WaveSound*)sounds_[id])->buffer->SetVolume(volume);
		((WaveSound*)sounds_[id])->buffer->Play(0, 0, NULL);
		((WaveSound*)sounds_[id])->isLoop = loop;
	}
	return;
}

bool SoundManager::IsPlaying(SoundID id)
{
	if (sounds_[id]->type == ST_Ogg)
	{
		DWORD dwStatus;
		((OggSound*)sounds_[id])->buffer->GetStatus(&dwStatus);
		if (dwStatus & DSBSTATUS_PLAYING)
		{
			return true;
		}
		return false;
	}
	else if (sounds_[id]->type == ST_Wave)
	{
		DWORD dwStatus;

		((OggSound*)sounds_[id])->buffer->GetStatus(&dwStatus);

		if (dwStatus & DSBSTATUS_PLAYING)
		{
			return true;
		}
		return false;
	}
	return false;
}

VOID SoundManager::Stop(SoundID id)
{
	if (sounds_[id]->type == ST_Ogg)
	{
		((OggSound*)sounds_[id])->buffer->Stop();
		((OggSound*)sounds_[id])->isLoop = false;
	}
	else if (sounds_[id]->type == ST_Wave)
	{
		((WaveSound*)sounds_[id])->buffer->Stop();
		((WaveSound*)sounds_[id])->isLoop = false;
	}
}

void SoundManager::Update()
{
	for (auto i : sounds_)
	{
		if (!IsPlaying(i.first))
		{
			if (i.second->type == ST_Ogg)
			{
				if (((OggSound*)i.second)->isLoop)
				{			
					Play(i.first, true, true);
				}
			}
			else if (i.second->type == ST_Wave)
			{
				if (((WaveSound*)i.second)->isLoop)
				{
					Play(i.first, true, true);
				}
			}
		}
	}
}
