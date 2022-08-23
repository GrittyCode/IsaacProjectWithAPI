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
	// FMOD_SOUND : ���� ���ҽ� ������ ���� ��ü 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];
	// FMOD_SYSTEM : ���� ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem;
};

