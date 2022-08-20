#pragma once
class CScene
{
public:
	CScene();
	CScene(wstring name, UINT row, UINT colmn);
	~CScene();

public:
	virtual void Init();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render(HDC hdc);
	virtual void Release();
	
	//Get
	UINT GetRow() { return m_row; }
	UINT GetColmn() { return m_colmn;}
	wstring const GetName() const { return m_Name; }

private:
	UINT m_row;
	UINT m_colmn;
	wstring m_Name;
	map < OBJECT_TYPE, list<CObject*>> m_MapObjectList;
};

