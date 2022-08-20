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

	UINT GetRow() { return m_row; }
	UINT GetColmn() { return m_colmn; }
public:
	wstring GetName() { return m_Name; }

protected:
	wstring m_Name;
	UINT m_row;
	UINT m_colmn;
};

