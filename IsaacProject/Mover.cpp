#include "stdafx.h"
#include "Mover.h"

CMover::CMover()
{
}

CMover::CMover(ObjectInfo objInfo, MoverInfo moverInfo)
	: CObject(objInfo),
	  m_MoverInfo(moverInfo)
{
	
}

CMover::~CMover()
{
}
