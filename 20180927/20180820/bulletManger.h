#pragma once
#include <vector>
#include "bullet.h"

class animation;

class bulletManger
{
private:
	std::vector<bullet*>			m_vecBullet;
	std::vector<bullet*>::iterator	m_iter;

	std::vector<bullet*>			m_vecNextFire;
	std::vector<bullet*>::iterator	m_NextIter;

	tagBulletInfo m_tBulletInfo;
	animation * m_pAni;

public:
	HRESULT init(int vecMaxSize);
	void release();
	void update();
	void render(HDC hdc);

	void fire(const char * imageName, float posX, float posY, float angle, tagBulletInfo * bulletInfo, tagBulletInfo* bulletInfoSub);
	void NextFire(const char * imageName, float posX, float posY, float angle, tagBulletInfo * bulletInfo, tagBulletInfo* bulletInfoSub);
	void NextFireShoot();

	inline std::vector<bullet*> getVecBullet()
	{
		return m_vecBullet;
	}

	int getIter() { return m_vecBullet.size(); }

	bulletManger();
	~bulletManger();
};

