#pragma once

class CEnemy;
class CState;

enum class AI_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATK,
	FLEE,
	DEAD,
	AI_STATE_END
};


class AI
{
public:
	AI();
	~AI();
	void Update();

private:
	CEnemy* m_pHost = nullptr;
	CState* m_currentState = nullptr;
	map<AI_STATE, CState*> m_MapState;

	friend class CEnemy;
};

