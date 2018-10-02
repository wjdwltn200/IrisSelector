#include "stdafx.h"
#include "bulletManger.h"


HRESULT bulletManger::init(int vecMaxSize)
{
	m_vecBullet.reserve(vecMaxSize);

	return S_OK;
}

void bulletManger::release()
{
	for (m_iter = m_vecBullet.begin(); m_iter != m_vecBullet.end(); m_iter++)
	{
		delete (*m_iter);
	}

	m_vecBullet.clear();
}

void bulletManger::update()
{
	for (m_iter = m_vecBullet.begin(); m_iter != m_vecBullet.end(); m_iter++)
	{
		(*m_iter)->update();
	}
}

void bulletManger::render(HDC hdc)
{
	for (m_iter = m_vecBullet.begin(); m_iter != m_vecBullet.end(); m_iter++)
	{
		if ((*m_iter)->getIsAlive())
		{
			(*m_iter)->render(hdc);
		}
	}
}

void bulletManger::fire(const char * imageName, float scale, float radius,
	float speed, float posX, float posY, float range, float expRadius, float dmage, float knokBack, float angle, tagBulletInfo bulletInfo)
{
	for (m_iter = m_vecBullet.begin(); m_iter != m_vecBullet.end(); m_iter++)
	{
		if (!(*m_iter)->getIsAlive()) // �׾������� ��Ȱ��
		{
			(*m_iter)->init(imageName, scale, radius,
				speed, posX, posY, range, expRadius, dmage, knokBack, angle, bulletInfo);

			return;
		}
	}

	bullet * pBullet = new bullet;
	pBullet->init(imageName, scale, radius,
		speed, posX, posY, range, expRadius, dmage, knokBack, angle, bulletInfo);

	m_vecBullet.push_back((pBullet));
	return;
}

bulletManger::bulletManger()
{
}


bulletManger::~bulletManger()
{
}
