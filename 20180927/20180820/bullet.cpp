#include "stdafx.h"
#include "bullet.h"
#include "animation.h"

// 테스트

HRESULT bullet::init(const char * imageName, float posX, float posY, float angle, tagBulletInfo bulletInfo)
{
	// 최초 초기화
	memset(&m_rc, NULL, sizeof(m_rc));


	// 이미지 초기화
	tImageType = bulletInfo.tImageType;
	switch (tImageType)
	{
	case BULLET_IMAGE_TYPE::COLOR_Y:
		m_pImg = IMAGEMANAGER->findImage("Bullet_Y");
		break;
	case BULLET_IMAGE_TYPE::COLOR_B:
		m_pImg = IMAGEMANAGER->findImage("Bullet_B");
		break;
	case BULLET_IMAGE_TYPE::COLOR_P:
		m_pImg = IMAGEMANAGER->findImage("Bullet_P");
		break;
	case BULLET_IMAGE_TYPE::COLOR_G:
		m_pImg = IMAGEMANAGER->findImage("Bullet_G");
		break;
	}
	m_pAni = new animation;
	m_pAni->init(m_pImg->getWidth(), m_pImg->getHeight(), m_pImg->getFrameWidth(), m_pImg->getFrameHeight());
	m_pAni->setDefPlayFrame(false, true);
	m_pAni->setFPS(30);
	m_pAni->start();

	// RECT 초기화 (이미지 프레임 크기)
	RectMakeCenter(m_fX, m_fY, m_pImg->getFrameWidth(), m_pImg->getFrameHeight());

	// 멤버 초기화
	m_fScale = bulletInfo.tScale;
	m_fRadius = bulletInfo.tRadius;
	m_fExpRadius = bulletInfo.tExpRadius;
	m_fSpeed = bulletInfo.tMoveSpeed;
	m_fKnockBack = bulletInfo.tKnokBack;
	m_fDmage = bulletInfo.tDmage;
	m_fRange = bulletInfo.tRange;
	m_fX = posX;
	m_fY = posY;
	m_fAngle = angle;
	m_fMoveAngle = 0.0f;
	m_fAngleRadius = 0.0f;
	tMoveTypeCount = 0;
	tImageType = 0;

	m_isAlive = true;

	tMoveType = bulletInfo.tMoveType;
	switch (tMoveType)
	{
	case BULLET_MOVE_TYPE::ONE_LINE:
		break;
	case BULLET_MOVE_TYPE::CENTER_CENTRIFUGAL:
		m_fMoveAngle = angle + 90.0f;
		break;
	case BULLET_MOVE_TYPE::MOVE_CENTRIFUGAL:
		break;
	case BULLET_MOVE_TYPE::MOVE_NUM:
		break;
	}


	return S_OK;
}

void bullet::release()
{
	SAFE_DELETE(m_pAni);
}

void bullet::update()
{
	if (!m_isAlive) return;
	movement();

	m_pAni->frameUpdate();
}

void bullet::render(HDC hdc)
{
	m_pImg->aniRender(hdc, m_fX - (m_pImg->getFrameWidth() / 2) * m_fScale,
		m_fY - (m_pImg->getFrameHeight() / 2) * m_fScale, m_pAni, m_fScale, true, 255);

	char szText[256];

	// TRANSPARENT : 투명, OPAQUE : 불투명
	SetBkMode(hdc, TRANSPARENT);

	SetTextColor(hdc, RGB(255, 0, 255));

	sprintf_s(szText, "m_fAngle : %f",
		m_fAngle);
	TextOut(hdc, 10, 100, szText, strlen(szText));

	sprintf_s(szText, "m_fMoveAngle : %f",
		m_fMoveAngle);
	TextOut(hdc, 10, 120, szText, strlen(szText));

	sprintf_s(szText, "tMoveTypeCount : %d",
		tMoveTypeCount);
	TextOut(hdc, 10, 140, szText, strlen(szText));
}

void bullet::movement()
{
	if (m_fSpeed == 0.0f || m_fSpeed == NULL) return;

	moveTypeAct(tMoveType);


	// 거리만큼 이동하면 삭제
	if (m_fRange < 0.0f)
	{
		m_isAlive = false;
	}
}

void bullet::moveTypeAct(int moveType)
{
	if (tMoveType == BULLET_MOVE_TYPE::MOVE_NUM) return;

	switch (tMoveType)
	{
	case BULLET_MOVE_TYPE::ONE_LINE:
		m_fMoveAngle = 0.0f;

		m_fX += cosf(m_fAngle) * m_fSpeed;
		m_fY += -sinf(m_fAngle) * m_fSpeed;
		m_fRange -= m_fSpeed;

		break;
	case BULLET_MOVE_TYPE::CENTER_CENTRIFUGAL:
		if (tMoveTypeCount >= 5)
		{
			m_fAngleRadius += 0.5f;
			m_fMoveAngle += 0.5f;
			tMoveTypeCount = 0;
		}
		if (m_fMoveAngle >= 360.0f)
		{
			m_fMoveAngle = 0.0f;
		}
		m_fX = m_fX + cosf(m_fMoveAngle) * m_fAngleRadius;
		m_fY = m_fY - sinf(m_fMoveAngle) * m_fAngleRadius;
		tMoveTypeCount++;

		m_fRange -= m_fAngleRadius;
		

		break;
	case BULLET_MOVE_TYPE::MOVE_CENTRIFUGAL:
		if (tMoveTypeCount >= 5)
		{
			m_fMoveAngle += 1.0f;
			tMoveTypeCount = 0;
		}
		if (m_fMoveAngle >= 360.0f)
		{
			m_fMoveAngle = 0.0f;
		}
		m_fX += cosf(m_fMoveAngle) * 10.0f;
		m_fY += -sinf(m_fMoveAngle) * 10.0f;
		tMoveTypeCount++;

		m_fX += cosf(m_fAngle) * m_fSpeed;
		m_fY += -sinf(m_fAngle) * m_fSpeed;
		m_fRange -= m_fSpeed;
		break;
	}
}

bullet::bullet()
{
}


bullet::~bullet()
{
}
