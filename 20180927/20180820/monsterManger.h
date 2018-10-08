#pragma once
#include <vector>
#include "monster.h"
class monsterManger
{
private:
	std::vector<monster*>				m_vecMonster;
	std::vector<monster*>::iterator		m_iter;


public:

	HRESULT init(int vecMaxSize);
	void release();
	void update();
	void Regeneration(const char*strKey, tagMonInfo moninfo, bulletManger* bulletInfo, PlayerCharacter* playerInfo);
	void render(HDC hdc);

	int getIter() { return m_vecMonster.size(); }

	inline std::vector<monster*> getVecMons()
	{
		return m_vecMonster;
	}

	monsterManger();
	~monsterManger();
};

