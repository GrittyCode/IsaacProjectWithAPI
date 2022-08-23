#pragma once

class CSoundMgr
{
	SINGLETONE(CSoundMgr)

public:
	enum CHANNELID { BGM , TITLE_BGM, PLAYER_WALK, TEAR_FIRE, TEAR_DEAD,PLAYER_HURT, INTRO, MAXCHANNEL };
	enum CHANNELSOUND {BGM_S, UI};

public:
	void Init();

	void Release();
public:
	void MyPlaySound(const TCHAR* pSoundKey, CHANNELID eID);
	void PlayBGM(const TCHAR* pSoundKey, CHANNELID id);
	void StopSound(CHANNELID eID);
	void AllStop();
	void LoadSoundFile();
	void SetAllSound(float Sound = 1.f);

public:
	// FMOD_SOUND : 사운드 리소스 정보를 갖는 객체 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];
	// FMOD_SYSTEM : 사운드 채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem;
};

