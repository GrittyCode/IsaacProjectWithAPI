#pragma once
class CItem;

class CKey
{
public:
    CKey(ObjectInfo obj);
    virtual ~CKey() {};
public:
     void Init() ;
     void Update() ;
     void FixedUpdate() ;
     void LateUpdate() ;
     void Render(HDC hdc) ;
     void Release() ;
     INT CheckCollisionState() ;
};

