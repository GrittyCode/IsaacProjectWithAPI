#pragma once

enum class ITEM_TYPE
{
    COIN,
    KEY,
    BOMB,
    ITEM_TYPE_END
};


class CItem :
    public CObject
{
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void FixedUpdate() = 0;
    virtual void LateUpdate() = 0;
    virtual void Render(HDC hdc) = 0;
    virtual void Release() = 0;
    virtual INT CheckCollisionState();

    ITEM_TYPE type;
};

