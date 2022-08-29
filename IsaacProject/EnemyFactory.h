#pragma once

enum class ENEMY_TYPE
{
	FLY,
	ATTACKFLY,
	FATEISAAC,
	FLYBOSS,
	ENEMY_TYPE_END
};




class EnemyFactory
{
public:
	static void CreateEnemyForType(ENEMY_TYPE type, Vector2 vecPos);
private:


};

