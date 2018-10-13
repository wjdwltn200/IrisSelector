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

void monsterManger::Regeneration(const char*strKey, tagMonInfo moninfo, bulletManger* bulletInfo, PlayerCharacter* playerInfo)
{
	for (m_iter = m_vecMonster.begin(); m_iter != m_vecMonster.end(); m_iter++)
	{
		if (!(*m_iter)->getMonInfo().tIsAlive)
		{
			(*m_iter)->init(strKey, moninfo, bulletInfo, playerInfo);
			return;
		}
	}
	//progressBar * pProgressBar = new progressBar;
	monster * pMonster = new monster;
	pMonster->init(strKey, moninfo, bulletInfo, playerInfo);
	m_vecMonster.push_back((pMonster));
	return;
}

void monsterManger::render(HDC hdc)
{
	for (m_iter = m_vecMonster.begin(); m_iter != m_vecMonster.end(); m_iter++)
	{
		if ((*m_iter)->getMonInfo().tIsAlive)
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
