#pragma once

enum class ENEMY_TYPE
{
	FLY,
	ATTACKFLY,
	FATEISAAC,
	FLYBOSS,
	ENEMY_TYPE_END
};



class CEnemyFactory
{
public:
	static void CreateEnemyForType(ENEMY_TYPE type, Vector2 vecPos);


	/*
	template<typename T>
	static void Create(Vector2 vecPos)
	{
		switch (T.GetEnemyInfo().type)
		{
		default:
			break;
		}
	}
	*/
};

