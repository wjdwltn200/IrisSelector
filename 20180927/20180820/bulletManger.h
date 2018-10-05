#pragma once
#include <vector>
#include "bullet.h"

class bulletManger
{
private:
	std::vector<bullet*>			m_vecBullet;
	std::vector<bullet*>::iterator	m_iter;

	tagBulletInfo m_tBulletInfo;

public:
	HRESULT init(int vecMaxSize);
	void release();
	void update();
	void render(HDC hdc);

	void fire(const char * imageName, float posX, float posY, float angle, tagBulletInfo bulletInfo, tagBulletInfo* bulletInfoSub);
	
	int getIter() { return m_vecBullet.size(); }

	bulletManger();
	~bulletManger();
};

