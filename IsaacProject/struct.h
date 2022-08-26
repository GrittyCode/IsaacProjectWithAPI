#pragma once

typedef struct Vec2
{
	float x;
	float y;

public:
	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vec2& Normalize()
	{
		float flen = Length();
		// 0 이면 나누지 않겠다가 아닌 0이라면 문제라고 판단하여 중단.
		x /= flen;
		y /= flen;
		return *this;
	}

public:

	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
		return *this;
	}

	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	void operator += (Vec2 _vOhter)
	{
		x += _vOhter.x;
		y += _vOhter.y;
	}

	Vec2 operator - (Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	Vec2 operator / (Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}
	Vec2 operator / (float _f)
	{
		assert(!(0.f == _f));
		return Vec2(x / _f, y / _f);
	}
	Vec2 operator * (int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}

	Vec2 operator*(float _f)
	{
		return Vec2(x * _f, y * (float)_f);
	}
public:
	Vec2()
		:x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		:x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		:x((float)_x)
		, y((float)_y)
	{}
	Vec2(LONG _x, LONG _y)
		:x((float)_x)
		, y((float)_y)
	{}
	Vec2(const POINT& _pt)
		:x((float)_pt.x)
		, y((float)_pt.y)
	{
	}
}Vector2, VECTOR2;
// 힘 , 크기를 갖고 있는 벡터

typedef struct SquareTag
{
	SquareTag(float aleft, float atop, float aright, float abottom)
		: left(aleft),
		  right(aright),
		  top(atop),
		  bottom(abottom)
	{

	}

	SquareTag(Vector2 pos, Vector2 size)
	{
		left = pos.x - size.x;
		right = pos.x + size.x;
		top = pos.y - size.y;
		bottom = pos.y + size.y;
	}


	void SetSquare(Vector2 pos, Vector2 size)
	{
		left = pos.x - size.x;
		right = pos.x + size.x;
		top = pos.y - size.y;
		bottom = pos.y + size.y;
	}

	Vector2 GetCenter() const {};
	Vector2 GetRectSize() const {};

	float left;
	float right;
	float top;
	float bottom;

}Square;







typedef struct tagTileInfo
{
	//ground형태로 아무것도 없는 빈 박스 생성
	tagTileInfo()
	{
		path = L"";
		v_StartPos = Vec2{ 0.0f,0.0f };
		v_EndPos = Vec2{ 0.0f,0.0f };
		v_Size = Vec2{ 0.0f,0.0f };
		LAYER = SORTING_LAYER::TILE;
		TYPE = TILE_TYPE::NONE;
		isXFlip = false;
		isYFlip = false;
	}

	tagTileInfo(SORTING_LAYER layer)
	{
		path = L"";
		v_StartPos = Vec2{ 0.0f,0.0f };
		v_EndPos = Vec2{ 0.0f,0.0f };
		v_Size = Vec2{ 0.0f,0.0f };
		LAYER = layer;
		TYPE = TILE_TYPE::NONE;
		isXFlip = false;
		isYFlip = false;
	}

	tagTileInfo(wchar_t* _path, Vec2 _v_StartPos, Vec2 _v_EndPos, Vec2 _v_Size, SORTING_LAYER _LAYER,
		TILE_TYPE type, BOOL xFlip, BOOL yFlip) :
		path(_path),
		v_StartPos(_v_StartPos),
		v_EndPos(_v_EndPos),
		v_Size(_v_Size),
		LAYER(_LAYER),	
		TYPE(type),
		isXFlip(xFlip),
		isYFlip(yFlip)
	{
	}

	tagTileInfo(wstring _path, Vec2 _v_StartPos, Vec2 _v_EndPos, Vec2 _v_Size, SORTING_LAYER _LAYER,
		TILE_TYPE type, BOOL xFlip, BOOL yFlip) :
		path(_path),
		v_StartPos(_v_StartPos),
		v_EndPos(_v_EndPos),
		v_Size(_v_Size),
		LAYER(_LAYER),
		TYPE(type),
		isXFlip(xFlip),
		isYFlip(yFlip)
	{
	}

	~tagTileInfo()
	{

	}


	//파일 경로명
	wstring path = L"";
	Vec2 v_StartPos;
	Vec2 v_EndPos;
	Vec2 v_Size;
	SORTING_LAYER LAYER;
	TILE_TYPE TYPE;
	BOOL isXFlip;
	BOOL isYFlip;

}TileInfo, TileSprite;


typedef struct TilePos
{
	TilePos()
	{
		WorldPos.x = 0;
		WorldPos.y = 0;
		LocalPos.x = 0;
		LocalPos.y = 0;
		row = 0;
		colmn = 0;
	};

	TilePos(int _row, int _colmn):
		row(_row),
		colmn(_colmn)
	{
		LocalPos.x = (float)row * (TILE_SIZE * Scale);
		LocalPos.y = (float)colmn * (TILE_SIZE * Scale);
		WorldPos = LocalPos;
	};

	//타일 인덱스 좌표
	UINT row = 0;
	UINT colmn = 0;

	//스크린 좌표
	VECTOR2 LocalPos;
	//실제 월드 좌표
	Vector2 WorldPos;


	void ChangeWindowScale()
	{
		
		LocalPos.x = (float)row * (TILE_SIZE * Scale);
		LocalPos.y = (float)colmn * (TILE_SIZE * Scale);
		WorldPos = LocalPos;

	}

	bool operator == (const TilePos& cmp) const
	{
		return row == cmp.row && colmn == cmp.colmn;
	}

	void operator = (const TilePos& cmp)
	{
		row = cmp.row;
		colmn = cmp.colmn;
		LocalPos.x = cmp.LocalPos.x;
		LocalPos.y = cmp.LocalPos.y;
		WorldPos.x = cmp.WorldPos.x;
		WorldPos.y = cmp.WorldPos.y;
	}

}TilePos, TILEPOS, Pos;


typedef struct ObjectInfoTag
{
	ObjectInfoTag()
	{
		wpath = L"";
		vecStartPos = Vec2(0.0f, 0.0f);
		vecEndPos = Vec2(0.0f, 0.0f);
		vecSize = Vec2(0.0f, 0.0f);
	}

	//Item의 경우에
	ObjectInfoTag(wstring path, Vector2 start, Vector2 end, Vector2 size,
		Vector2 WorldPos):
		wpath(path),
		vecStartPos(start),
		vecEndPos(end),
		vecSize(size),
		vecWorldPos(WorldPos)
	{
	
	}

	ObjectInfoTag(wstring path, OBJECT_TYPE atype, OBJECT_STATE astate)
	:
		type(atype),
		state(astate)
	{
		wpath = path;
		vecStartPos = Vec2(0.0f, 0.0f);
		vecEndPos = Vec2(0.0f, 0.0f);
		vecSize = Vec2(0.0f, 0.0f);
		vecWorldPos = Vec2(0.0f, 0.0f);
		vecScale = Vec2(0.0f, 0.0f);
	}

	ObjectInfoTag(wstring path, Vector2 start, Vector2 end, Vector2 size, 
		Vector2 WorldPos, Vector2 Scale, OBJECT_TYPE atype, OBJECT_STATE astate)
		:
		wpath(path),
		vecStartPos(start),
		vecEndPos(end),
		vecSize(size),
		vecWorldPos(WorldPos),
		vecScale(Scale),
		type(atype),
		state(astate)
	{
	}

	ObjectInfoTag(const wchar_t* path, Vector2 start, Vector2 end, Vector2 size,
		Vector2 WorldPos, Vector2 Scale, OBJECT_TYPE atype, OBJECT_STATE astate)
		:
		wpath(path),
		vecStartPos(start),
		vecEndPos(end),
		vecSize(size),
		vecWorldPos(WorldPos),
		vecScale(Scale),
		type(atype),
		state(astate)
	{
	}

	wstring wpath;
	Vector2 vecStartPos;
	Vector2 vecEndPos;
	Vector2 vecSize;
	Vector2 vecWorldPos;
	Vector2 vecScale;
	OBJECT_TYPE type;
	OBJECT_STATE state;

}ObjectInfo;




//파싱한 정보를 담고 있는 구조체
typedef struct SceneInfoTag
{
	wstring wSceneName;
	vector<ObjectInfo> vecObjectInfo;
	SCENE_TYPE type;
	SCENE_STATE state;

}SCENEINFO, SceneInfo;


struct tKeyInfo
{
	KEY_STATE	eState;//키의 현재 상태를 뜻함
	bool		bPrevPush;//이전 프레임에서 눌렀는지 여부를 따짐
};

typedef struct SpriteInfoTag
{
	wstring wPath;
	Vector2 vecStartPos;
	Vector2 vecSpriteSize;
	Vector2 vecOffset;
	bool bFilp;

	SpriteInfoTag()
	{
		wPath = L"";
		vecStartPos = Vector2(0,0);
		vecSpriteSize = Vector2(0,0);
		bFilp = false;
	}

	SpriteInfoTag(Vector2 startPos, bool filp)
		:vecStartPos(startPos)
		, bFilp(filp)
	{
	}

	SpriteInfoTag(wstring path, Vector2 startPos, Vector2 size, bool filp,Vector2 offset)
		:wPath(path),
		vecStartPos(startPos),
		vecSpriteSize(size),
		bFilp(filp),
		vecOffset(offset)
	{
	}
} SpriteInfo,SPRITEINFO;


