#pragma once

class CEnemy;
class CState;

enum class AI_STATE
{
	IDLE,
	PATROL,
	TRACE,
	FLYTRACE,
	ATK,
	FLEE,
	DEAD,
	AI_STATE_END
};

class AI
{
public:
	AI(CEnemy* host);
	~AI();

	void Update();
	void AddState(CState* state);
	void ChangeState(AI_STATE state);

	//Get
	CState* GetState(AI_STATE state);
	CEnemy* GetHost() { return m_pHost; }

private:
	CEnemy* m_pHost = nullptr;
	CState* m_currentState = nullptr;
	map<AI_STATE, CState*> m_MapState;

	friend class CEnemy;
};

