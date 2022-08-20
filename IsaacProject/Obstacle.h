#pragma once
class CObstacle : public CObject
{
public:
    CObstacle();
    CObstacle(ObjectInfo objinfo);
    virtual void Init() override;
    virtual void Update() override;
    virtual void FixedUpdate() override;
    virtual void Render(HDC hdcd) override;
    virtual void Release() override;
    virtual INT CheckCollisionState() override;
    void PushMover(CObject* obj);

private:
    bool m_isCollision = false;

};

