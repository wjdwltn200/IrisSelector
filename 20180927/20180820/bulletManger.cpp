#include "stdafx.h"
#include "bulletManger.h"


HRESULT bulletManger::init(int vecMaxSize)
{
	for (int i = 0; i < vecMaxSize; i++)
	{
		memset(&m_tBulletInfo, 0, sizeof(m_tBulletInfo));

		m_tBulletInfo.tIsAlive = false;

		bullet * pBullet = new bullet;
		pBullet->init("임시", 0, 0, 0, m_tBulletInfo, &m_tBulletInfo, this);
		m_vecBullet.push_back((pBullet));
	}
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
		if ((*m_iter)->getIsAlive())
		{
			(*m_iter)->update();
		}
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

void bulletManger::fire(const char * imageName, float posX, float posY, float angle, tagBulletInfo bulletInfo, tagBulletInfo* bulletInfoSub)
{
	//if (bulletInfo.tBulletBoom)
	//{
		for (m_iter = m_vecBullet.begin(); m_iter != m_vecBullet.end(); m_iter++)
		{
			if (!(*m_iter)->getIsAlive()) // 죽어있으면 재활용
			{
				(*m_iter)->init(imageName, posX, posY, angle, bulletInfo, bulletInfoSub, this);
				return;
			}
		}
	//}

	bullet * pBullet = new bullet;
	pBullet->init(imageName, posX, posY, angle, bulletInfo, bulletInfoSub, this);

	m_vecBullet.push_back((pBullet));
	return;
}

bulletManger::bulletManger()
{
}


bulletManger::~bulletManger()
{
}
