#pragma once

#define TILE_SIZE 26
#define TOOL_TILE_SIZE 32


#pragma region MAPSIZE

#define ROW	18
#define COLMN 12

#pragma endregion

#pragma region WINDOW RECT

#define WINDOW_X 936
#define WINDOW_Y 624

#define WINDOW_START_X 250
#define WINDOW_START_Y 150

#define PADDING_X 100
#define PADDING_Y 100

#pragma endregion


#pragma region STATE

#define ERROR_STATE -1
#define COMPLETE 1

#pragma endregion



#define DEGREETORADIAN(t) ((t) * (float)M_PI / (float)180.0f)
#define RADIANTODEGREE(t) (((float)180.0f / (float)M_PI) * (t))


#define NO_COPY(className)	private :\
							className(const className& obj);\
							className* operator = (className* obj)\
							{return nullptr;}

//½Ì±ÛÅæ ÆÐÅÏ
#define SINGLETONE(ClassName)	\
private:	\
NO_COPY(ClassName);\
ClassName(){}\
~ClassName(){}\
public:\
static ClassName* GetInstance()\
{\
	if(m_pInstance == NULL)\
	{\
		m_pInstance = new ClassName;\
		m_pInstance->Init();\
	}\
	return m_pInstance;	\
}\
static void DestroyInst()\
{\
	delete m_pInstance;\
	m_pInstance = nullptr;\
}\
private:\
static ClassName* m_pInstance;







#pragma region DELTA_TIME

#define DELTA CTimeMgr::GetInstance()->GetDeltaTime()

#pragma endregion




#pragma region FILE_PATH

#define FILE_PATH L"../Resources/BackGround/"

#pragma endregion



#pragma region NULLCHECK