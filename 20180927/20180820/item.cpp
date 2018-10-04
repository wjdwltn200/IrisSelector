#include "stdafx.h"
#include "item.h"
#include "animation.h"

HRESULT item::init(const char * imageName, float posX, float posY, tagItemInfo itemInfo)
{
	// ���� �ʱ�ȭ
	memset(&m_rc, NULL, sizeof(m_rc));

	// �̹��� �ʱ�ȭ
	m_pImg = IMAGEMANAGER->findImage(imageName);

	//m_pAni = new animation;
	//m_pAni->init(m_pImg->getWidth(), m_pImg->getHeight(), m_pImg->getFrameWidth(), m_pImg->getFrameHeight());
	//m_pAni->setDefPlayFrame(false, true);
	//m_pAni->setFPS(30);
	//m_pAni->start();

	// RECT �ʱ�ȭ (�̹��� ������ ũ��)
	RectMakeCenter(m_fX, m_fY, m_pImg->getFrameWidth(), m_pImg->getFrameHeight());

	// ��� �ʱ�ȭ
	m_tItemInfo.tScale = itemInfo.tScale;
	m_tItemInfo.tRadius = (m_pImg->getFrameWidth() / 2) * itemInfo.tScale;

	m_tItemInfo.tTimer = itemInfo.tTimer;
	m_tItemInfo.tImageCurrX = itemInfo.tImageCurrX;
	m_tItemInfo.tImageCurrY = itemInfo.tImageCurrY;
	m_tItemInfo.tSkillType = itemInfo.tSkillType;

	m_fX = posX;
	m_fY = posY;
	//m_fMoveAngle = 0.0f;
	//m_fAngleRadius = 0.0f;

	m_isAlive = true;

	return S_OK;
}

void item::release()
{
}

void item::update()
{
	if (!m_isAlive) return;

	if (m_tItemInfo.tTimer <= 0)
	{
		m_isAlive = false;
	}
	m_tItemInfo.tTimer--;

	m_rc = RectMakeCenter(
		m_fX,
		m_fY,
		(m_pImg->getFrameWidth() * m_tItemInfo.tScale),
		(m_pImg->getFrameHeight() * m_tItemInfo.tScale));
}

void item::render(HDC hdc)
{
	if (!m_isAlive) return;
	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	Ellipse(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	//EllipseMakeCenter(hdc, m_fX, m_fY, m_pImg->getFrameWidth() + 5, m_pImg->getFrameHeight() + 5);

	m_pImg->frameAlphaRender(hdc,
		m_fX - (m_pImg->getFrameWidth() / 2 * m_tItemInfo.tScale),
		m_fY - (m_pImg->getFrameHeight() / 2 * m_tItemInfo.tScale),
		m_tItemInfo.tImageCurrX,
		m_tItemInfo.tImageCurrY,
		m_tItemInfo.tScale,
		0);

	char szText[256];

	// TRANSPARENT : ����, OPAQUE : ������
	SetBkMode(hdc, TRANSPARENT);

	SetTextColor(hdc, RGB(255, 0, 255));

	sprintf_s(szText, "m_fX : %f / m_fY : %f",
		m_fY, m_fY);
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
