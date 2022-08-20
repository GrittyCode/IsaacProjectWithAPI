#include "stdafx.h"
#include "Animation.h"

CAnimation::CAnimation(SpriteInfo sprite, int framelimit, float framedelay, Vector2 Size)
	:m_fCurDelay(0),
	m_fFrameDelay(framedelay),
	m_iCurFrame(0),
	m_iFrameLimit(framelimit),
	m_tSpriteinfo(sprite),
	m_vecScreenSize(Size),
	m_vecWorldpos(Vector2(0, 0))

{
	m_image = Image::FromFile(sprite.wPath.c_str());

	if (m_tSpriteinfo.bFilp)
	{
		m_image->RotateFlip(Rotate180FlipY);
	}
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update(Vector2 pos)
{
	m_vecWorldpos = pos;

	if (m_fFrameDelay != 0)
	{
		m_fCurDelay += DELTA;

		if (m_fCurDelay > m_fFrameDelay)
		{
			++m_iCurFrame;
			m_fCurDelay = 0;
		}

		if (m_iCurFrame == m_iFrameLimit)
		{
			m_iCurFrame = 0;
		}
	}

	Render();
}

void CAnimation::Render()
{
	if (!m_tSpriteinfo.bFilp)
	{
		CImageMgr::GetInstance()->GetGraphics()->DrawImage(m_image,
			Rect((UINT)m_vecWorldpos.x - m_vecScreenSize.y + m_tSpriteinfo.vecOffset.x,
				(UINT)m_vecWorldpos.y - m_vecScreenSize.y + m_tSpriteinfo.vecOffset.y,
				(UINT)m_vecScreenSize.x * Scale,
				(UINT)m_vecScreenSize.y * Scale),
				(UINT)m_tSpriteinfo.vecStartPos.x + (m_iCurFrame * m_tSpriteinfo.vecSpriteSize.x),
				(UINT)m_tSpriteinfo.vecStartPos.y,
				(UINT)m_tSpriteinfo.vecSpriteSize.x,
				(UINT)m_tSpriteinfo.vecSpriteSize.y, UnitPixel);
	}
	else
	{
		CImageMgr::GetInstance()->GetGraphics()->DrawImage(m_image,
			Rect((UINT)m_vecWorldpos.x - m_vecScreenSize.y + m_tSpriteinfo.vecOffset.x,
				(UINT)m_vecWorldpos.y - m_vecScreenSize.y + m_tSpriteinfo.vecOffset.y,
				(UINT)m_vecScreenSize.x * Scale,
				(UINT)m_vecScreenSize.y * Scale),
				(UINT)m_tSpriteinfo.vecStartPos.x - (m_iCurFrame * m_tSpriteinfo.vecSpriteSize.x),
				(UINT)m_tSpriteinfo.vecStartPos.y,
				(UINT)m_tSpriteinfo.vecSpriteSize.x,
				(UINT)m_tSpriteinfo.vecSpriteSize.y, UnitPixel);
	}
}

void CAnimation::ResetDelay()
{
	m_fCurDelay = 0;
	m_iCurFrame = 0;
}
