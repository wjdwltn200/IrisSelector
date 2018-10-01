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
		(*m_iter)->render(hdc);
	}
}

bulletManger::bulletManger()
{
}


bulletManger::~bulletManger()
{
}
