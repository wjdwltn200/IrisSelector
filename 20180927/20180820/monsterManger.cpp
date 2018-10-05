#include "stdafx.h"
#include "monster.h"
#include "monsterManger.h"


HRESULT monsterManger::init(int vecMaxSize)
{

	m_vecMonster.reserve(vecMaxSize);
	return S_OK;
}

void monsterManger::release()
{
	for (m_iter = m_vecMonster.begin(); m_iter != m_vecMonster.end(); m_iter++)
	{
		delete (*m_iter);
	}
	m_vecMonster.clear();
}

void monsterManger::update()
{
	for (m_iter = m_vecMonster.begin(); m_iter != m_vecMonster.end(); m_iter++)
	{
		(*m_iter)->update();
	}
}

void monsterManger::Regeneration(const char*strKey, int fX, int fY, float speed)
{
	for (m_iter = m_vecMonster.begin(); m_iter != m_vecMonster.end(); m_iter++)
	{
		if (!(*m_iter)->getAlive())
		{
			(*m_iter)->init(strKey, fX, fY, speed);
			return;
		}
	}
	monster * pMonster = new monster;
	pMonster->init(strKey, fX, fY, speed);
	m_vecMonster.push_back((pMonster));
	return;
}

void monsterManger::render(HDC hdc)
{
	for (m_iter = m_vecMonster.begin(); m_iter != m_vecMonster.end(); m_iter++)
	{
		if ((*m_iter)->getAlive() )
		{
		(*m_iter)->render(hdc);
		}
	}

}

monsterManger::monsterManger()
{
}


monsterManger::~monsterManger()
{
}
