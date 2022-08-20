#pragma once

class CState
{
public:
	CState(AI_STATE type);
	virtual ~CState();

	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update() = 0;

	//Set
	void SetAI(AI* pai) { m_pAI = pai; }

	AI_STATE GetType() { return m_type; }
	AI* GetAI() { return m_pAI; }

private:
	AI_STATE		m_type;
	AI*				m_pAI;
};

