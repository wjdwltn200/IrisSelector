#include "stdafx.h"
#include "bullet.h"
#include "animation.h"

HRESULT bullet::init(const char * imageName, float scale, float radius,
	float speed, float posX, float posY, float range, float expRadius, float dmage, float knokBack, float angle)
{
	IMAGEMANAGER->addImage();
	m_pImg = IMAGEMANAGER->findImage(imageName);
	m_pAni = new animation;
	m_pAni->init(m_pImg->getWidth() * scale, m_pImg->getHeight() * scale, m_pImg->getFrameWidth() * scale, m_pImg->getFrameHeight() * scale);
	m_pAni->setDefPlayFrame(false, true);
	m_pAni->setFPS(30);

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

	return S_OK;
}

void bullet::release()
{
	SAFE_DELETE(m_pAni);
}

void bullet::update()
{
}

void bullet::render(HDC hdc)
{
	//m_pImg->aniRender();
}

bullet::bullet()
{
}


bullet::~bullet()
{
}
