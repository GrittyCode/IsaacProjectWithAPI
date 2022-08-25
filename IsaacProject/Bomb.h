#pragma once
class CBomb : public CObject
{
public:
    CBomb(ObjectInfo obj);
    virtual ~CBomb() {};
public:
    void Init();
    void Update();
    void FixedUpdate();
    void LateUpdate();
    void Render(HDC hdc);
    void Release();
    INT CheckCollisionState();
};

