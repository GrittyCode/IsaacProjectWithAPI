#pragma once
class CBackground :
    public CObject
{
public:
    CBackground();
    CBackground(ObjectInfo objinfo);
    virtual void Init() override;
    virtual void Update() override;
    virtual void FixedUpdate() override;
    virtual void Render(HDC hdcd) override;
    virtual void Release() override;
    virtual INT CheckCollisionState() { return ERROR_STATE; }
};

