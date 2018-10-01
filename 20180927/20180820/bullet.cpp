#include "stdafx.h"
#include "bullet.h"
#include "animation.h"

HRESULT bullet::init(const char * imageName, float scale, float radius,
	float speed, float posX, float posY, float range, float expRadius, float dmage, float knokBack, float angle)
{
	// 최초 초기화
	memset(&m_rc, NULL, sizeof(m_rc));

	// 이미지 초기화
	m_pImg = IMAGEMANAGER->findImage(imageName);
	m_pAni = new animation;
	m_pAni->init(m_pImg->getWidth() * scale, m_pImg->getHeight() * scale, m_pImg->getFrameWidth() * scale, m_pImg->getFrameHeight() * scale);
	m_pAni->setDefPlayFrame(false, true);
	m_pAni->setFPS(30);
	m_pAni->start();

	// RECT 초기화 (이미지 프레임 크기)
	RectMakeCenter(m_fX, m_fY, m_pImg->getFrameWidth(), m_pImg->getFrameHeight());

	// 멤버 초기화
	m_fScale = scale;
	m_fRadius = radius;
	m_fSpeed = speed;
	m_fX = posX;
	m_fY = posY;
	m_fRange = range;
	m_fExpRadius = expRadius;
	m_fDmage = dmage;
	m_fKnockBack = knokBack;
	m_fAngle = angle;

	m_isAlive = true;
	return S_OK;
}

void bullet::release()
{
	SAFE_DELETE(m_pAni);
}

void bullet::update()
{
	movement();

	m_pAni->frameUpdate();
}

void bullet::render(HDC hdc)
{
	m_pImg->aniRender(hdc, m_fX - (m_pImg->getFrameWidth() / 2) * m_fScale,
		m_fY - (m_pImg->getFrameHeight() / 2) * m_fScale, m_pAni, m_fScale, true, 255);
}

void bullet::movement()
{
	if (m_fSpeed == 0.0f || m_fSpeed == NULL) return;

	m_fX += cosf(m_fAngle) * m_fSpeed;
	m_fY += -sinf(m_fAngle) * m_fSpeed;
}

bullet::bullet()
{
}


bullet::~bullet()
{
}
