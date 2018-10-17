#pragma once
#include <vector>
#include "monster.h"
#include "animation.h"
#include "progressBar.h"

class effectManager;

class monsterManger
{
private:
	std::vector<monster*>				m_vecMonster;
	std::vector<monster*>::iterator		m_iter;

	effectManager * m_pEffMag;

	//animation * m_monsterMove;
	//tagMonInfo m_tMonInfo;
	//image * m_monsterType;
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

	void setEffMagPoint(effectManager * effPoint) { m_pEffMag = effPoint; }

	monsterManger();
	~monsterManger();
};

