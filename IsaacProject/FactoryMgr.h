#pragma once

template<class T>
class CFactoryMgr
{
public:
	static T* CreateFactory(ObjectInfo obj) { CreateObject(new T(obj)); }
};