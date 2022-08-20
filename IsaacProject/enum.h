#pragma once


enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	AI_STATE_CHANGE
};

#pragma region COMPONENT

enum class COMPONENT_TYPE
{
	TRANSFORM,
	BOXCOLLIDE2D,
	SPRITE,
	COMPONENT_TYPE_END
};

#pragma endregion


#pragma region  OBJECT 

enum class OBJECT_STATE
{
	NONE,
	IDLE,
	COLLISION,
	DEAD,
	OBJECT_STATE_END
};

enum class OBJECT_TYPE
{
	BACKGROUND,
	OBSTACLE,
	PLAYER_TEAR, 
	ENEMY_TEAR,
	BOMB,
	DOOR,
	ITEM,
	ENEMY,
	PLAYER,
	BOSS,
	OBJECT_TYPE_END
};

enum class COLLISION_FLAG
{
	BACKGROUND = 0,
	OBSTACLE = 1,
	PLAYER_TEAR = 2,
	ENEMY_TEAR = 4,
	BOMB = 8,
	DOOR = 16,
	ITEM = 32,
	ENEMY = 64,
	PLAYER = 128,
	BOSS = 256,
	OBJECT_TYPE_END
};


enum class OBJECT_INFO
{
	PATH,
	START_X,
	START_Y,
	END_X,
	END_Y,
	SIZE_X,
	SIZE_Y,
	POSITION_X,
	POSITION_Y,
	SCALE_X,
	SCALE_Y,
	TYPE,
	STATE,
	OBJECT_INFO_END
};

enum class TRANSFORM
{
	POSITION_X,
	POSITION_Y,
	SIZE_X,
	SIZE_Y,
	TRANSFORM_END
};

enum class PLAYER_STATE
{
	IDLE,
	MOVE,
	HUNT,
	DEAD
};

#pragma endregion



#pragma region LAYER

enum class COLLISION_LAYER
{
	OBJECT,
	ENEMY,
	TEAR,
	PLAYER
};

enum class SORTING_LAYER
{
	TILE,
	BACKGROUND,
	OBJECT,
	FLYING,
	OBJECT_LAYER_END
};

#pragma endregion


#pragma region TYPE


enum class TILE_TYPE
{
	NONE,
	DOOR,
	TILE_TYPE_END
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	DEFAULT,
	BOSS,
	SCENE_TYPE_END
};

enum class SCENE_STATE
{
	CLOSE,
	OPEN,
	CSENE_STATE_END
};


#pragma endregion


#pragma region MODE

enum class GAME_MODE
{
	GAME,
	TOOL,
	DEBUG,
	GAME_MODE_END
};

enum class TILE_MODE
{
	MAP,
	OBJECT,
	ENEMY
};

#pragma endregion


#pragma region KEY

enum class KEY_STATE
{
	NONE,//눌리지 않았고 이전에도 눌리지 않은 상태
	TAP,//막누른 상태
	HOLD,//누르고 있는
	AWAY//막 땐 시점
};

enum class KEY
{
	//공격키
	LEFT,
	RIGHT,
	UP,
	DOWN,
	//이동
	W,
	A,
	S,
	D,
	//특정키
	SPCAE,
	ENTER,
	ESC,
	LBUTTON,
	F1,
	F2,
	F3,
	LAST
};



#pragma endregion



#pragma region FILE IO SYSTEM

enum class TILE_POS
{
	IDX_ROW,
	IDX_COLMN,
	WORLDPOS_X,
	WORLDPOS_Y,
	LOCALPOS_X,
	LOCALPOS_Y,
	TILE_POS_END
};


enum class TILE_INFO
{
	PATH,
	STARTPOS_X,
	STARTPOS_Y,
	ENDPOS_X,
	ENDPOS_Y,
	SIZE_X,
	SIZE_Y,
	LAYER,
	TYPE,
	FLIP_X,
	FLIP_Y,
	TILE_INFO_END
};

#pragma endregion

#pragma region Ani

enum class DIRECTION
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

enum class ANISTATE
{
	IDLE,
	UPMOVE,
	DOWNMOVE,
	LEFTMOVE,
	RIGHTMOVE,
	UPATTACK,
	DOWNATTACK,
	LEFTATTACK,
	RIGHTATTACK,
	HUNT
};

#pragma endregion
