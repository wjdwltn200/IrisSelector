#include "stdafx.h"
#include "item.h"
#include "animation.h"

HRESULT item::init(const char * imageName, tagItemInfo itemInfo)
{
	// 최초 초기화
	memset(&m_rc, NULL, sizeof(m_rc));

	// 이미지 초기화
	m_pImg = IMAGEMANAGER->findImage(imageName);
	m_pImgShadow = IMAGEMANAGER->findImage("ItemShadow");

	// 멤버 초기화
	m_tItemInfo.tScale = itemInfo.tScale;
	m_tItemInfo.tRadius = (m_pImg->getFrameWidth() / 2) * itemInfo.tScale;

	m_tItemInfo.tTimer = itemInfo.tTimer;
	m_tItemInfo.tImageCurrX = itemInfo.tImageCurrX;
	m_tItemInfo.tImageCurrY = itemInfo.tImageCurrY;
	m_tItemInfo.tSkillType = itemInfo.tSkillType;

	m_tItemInfo.posX = itemInfo.posX;
	m_tItemInfo.posY = m_fItemIdleY = itemInfo.posY;
	m_fItemIdleCurrY = m_tItemInfo.posY;
	//m_fMoveAngle = 0.0f;
	//m_fAngleRadius = 0.0f;
	m_isItemIdle = true;
	m_ItemAlphaNum = 0;
		// RECT 초기화 (이미지 프레임 크기)
	RectMakeCenter(m_tItemInfo.posX, m_tItemInfo.posY, m_pImg->getFrameWidth(), m_pImg->getFrameHeight());

	m_isAlive = true;

	return S_OK;
}

void item::release()
{
}

void item::update()
{
	if (!m_isAlive) return;

	if (m_isItemIdle)
	{

		m_ItemAlphaNum += 2;
		if (m_ItemAlphaNum > 155)
			m_ItemAlphaNum = 155;

		if (m_fItemIdleY < m_fItemIdleCurrY - ITEM_IDLE_Y_SIZE)
		{
			m_isItemIdle = false;
		}

		m_fItemIdleY -= 0.1f;
	}
	else
	{
		m_ItemAlphaNum -= 2;
		if (m_ItemAlphaNum < 0)
			m_ItemAlphaNum = 0;

		if (m_fItemIdleY > m_fItemIdleCurrY + ITEM_IDLE_Y_SIZE)
		{
			m_isItemIdle = true;
		}


		m_fItemIdleY += 0.1f;
	}

	if (m_tItemInfo.tTimer <= 0)
	{
		m_isAlive = false;
	}
	m_tItemInfo.tTimer--;

	m_rc = RectMakeCenter(
		m_tItemInfo.posX,
		m_tItemInfo.posY,
		(m_pImg->getFrameWidth() * m_tItemInfo.tScale),
		(m_pImg->getFrameHeight() * m_tItemInfo.tScale));
}

void item::render(HDC hdc)
{
	if (!m_isAlive) return;
	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	Ellipse(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	//EllipseMakeCenter(hdc, m_fX, m_fY, m_pImg->getFrameWidth() + 5, m_pImg->getFrameHeight() + 5);

	m_pImgShadow->frameAlphaRender(hdc,
		m_tItemInfo.posX - (m_pImgShadow->getFrameWidth() / 2),
		m_tItemInfo.posY - (m_pImgShadow->getFrameHeight() / 2) + 20.0f,
		m_tItemInfo.tImageCurrX,
		m_tItemInfo.tImageCurrY,
		m_tItemInfo.tScale,
		m_ItemAlphaNum);

	m_pImg->frameAlphaRender(hdc,
		m_tItemInfo.posX - (m_pImg->getFrameWidth() / 2 * m_tItemInfo.tScale),
		m_fItemIdleY - (m_pImg->getFrameHeight() / 2 * m_tItemInfo.tScale),
		m_tItemInfo.tImageCurrX,
		m_tItemInfo.tImageCurrY,
		m_tItemInfo.tScale,
		0);

	char szText[256];

	// TRANSPARENT : 투명, OPAQUE : 불투명
	SetBkMode(hdc, TRANSPARENT);

	SetTextColor(hdc, RGB(255, 0, 255));

	sprintf_s(szText, "m_fX : %f / m_fY : %f",
		m_tItemInfo.posX, m_tItemInfo.posY);
	TextOut(hdc, 200, 100, szText, strlen(szText));

	sprintf_s(szText, "tImageCurrX / Y : %d, %d",
		m_tItemInfo.tImageCurrX, m_tItemInfo.tImageCurrY);
	TextOut(hdc, 200, 120, szText, strlen(szText));

	sprintf_s(szText, "tMoveTypeCount : %f",
		m_tItemInfo.tScale);
	TextOut(hdc, 200, 140, szText, strlen(szText));

	sprintf_s(szText, "tTimer : %d",
		m_tItemInfo.tTimer);
	TextOut(hdc, 200, 160, szText, strlen(szText));
	
	sprintf_s(szText, "tRadius : %f",
		m_tItemInfo.tRadius);
	TextOut(hdc, 200, 180, szText, strlen(szText));

}

item::item()
{
}


item::~item()
{
}
