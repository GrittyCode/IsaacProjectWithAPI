#pragma once
class CKey :
    public CItem
{
public:
    CKey(ObjectInfo obj);
    virtual ~CKey() {};
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void FixedUpdate() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC hdc) override;
    virtual void Release() override;
    virtual INT CheckCollisionState() override;
};

