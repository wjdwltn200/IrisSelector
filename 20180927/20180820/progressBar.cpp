#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(float x, float y, float width, float height)
{
	m_fX = x;
	m_fY = y;
	m_tMonInfo.tHp = width;
	m_fWidth = m_tMonInfo.tHp;
	m_fHeight = height;
	
	m_rc = RectMake(m_fX, m_fY, m_fWidth, m_fHeight);

	m_imgTop = IMAGEMANAGER->addImage("barTop", 
		"image/resources/UI_image/Progress_Bar/hpBarTop.bmp", m_fWidth, m_fHeight, true, RGB(255, 0, 255));
	m_imgBottom = IMAGEMANAGER->addImage("barBottom",
		"image/resources/UI_image/Progress_Bar/hpBarBottom.bmp", m_fWidth, m_fHeight, true, RGB(255, 0, 255));

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
}

void progressBar::render(HDC hdc)
{
	IMAGEMANAGER->findImage("barBottom")->render(hdc, m_fX, m_fY);
	IMAGEMANAGER->findImage("barTop")->render(hdc, m_fX, m_fY,
		0, 0, m_fWidth, m_imgTop->getHeight());
}

void progressBar::setGauge(float currGauge, float maxGauge)
{
	m_tMonInfo.tHpMax = maxGauge;
	m_fCurrGauge = currGauge;
	m_tMonInfo.tcurrGauge = m_fCurrGauge;
	m_fWidth = (m_fCurrGauge / m_tMonInfo.tHpMax) * m_imgTop->getWidth();
}

void progressBar::monHpSub(float minGaugeSub, float maxGaugeSub, int minGaugeInfo, int maxGaugeInfo)
{
	m_fGaugeSub = minGaugeSub;
	m_fMaxGaugeSub = maxGaugeSub;
	if (m_fCurrGauge >= m_fGaugeSub)
	{
		switch (minGaugeInfo)
		{
		case MONSTER_SUB::MONSTER_ATT_UP:
			m_tMonInfo.tDamageSub += 10.0f;
			break;
		case MONSTER_SUB::_MONSTER_DEF_UP:
			m_tMonInfo.tcurrGauge -= 5.0f;
			break;
		case MONSTER_SUB::MONSTER_SPEED_UP:
			m_tMonInfo.tMoveSpeed += 5.0f;
			break;
		case MONSTER_SUB::MONSTER_POWER_UP:
			m_tMonInfo.tDamageSub += 10.0f;
			m_tMonInfo.tcurrGauge -= 5.0f;
			break;
		}
	}
	else if (m_fCurrGauge >= m_fMaxGaugeSub)
	{
		switch (maxGaugeInfo)
		{
		case MONSTER_SUB::MONSTER_HP_HEALING:
			m_tMonInfo.tHp += 5.0f;
			break;
		case MONSTER_SUB::MONSTER_RESURRECTION:
			if (m_tMonInfo.tIsAlive == false)
			{
				m_tMonInfo.tIsAlive = true;
			}
			break;
		case MONSTER_SUB::MONSTER_BOOM:
			if (m_tMonInfo.tIsAlive == false)
			{

			}
			break;
		}
	}
}

progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}
