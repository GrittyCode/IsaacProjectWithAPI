#include "stdafx.h"
#include "ImageMgr.h"

CImageMgr* CImageMgr::m_pInstance = nullptr;

void CImageMgr::Init()
{
	m_graphics = new Graphics(CGameMgr::GetInstance()->GetMemDC());
};


Image* CImageMgr::GetImage(wstring path)
{
	m_iter = m_mapImage.find(path);

	//파일이 존재하지 않는다면
	if (m_iter == m_mapImage.end())
	{
		m_mapImage.insert({ path, Image::FromFile(path.c_str()) });
		m_iter = m_mapImage.find(path);
	}

	return (*m_iter).second;
}

void CImageMgr::Release()
{
	m_iter = m_mapImage.begin();

	while (m_iter != m_mapImage.end())
	{
		delete (*m_iter).second;
		(*m_iter).second = nullptr;
		m_iter++;
	}

	m_mapImage.clear();


	m_graphics->ReleaseHDC(CGameMgr::GetInstance()->GetMemDC());

	delete m_graphics;

}

