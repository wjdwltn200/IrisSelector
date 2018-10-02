#pragma once
#include <vector>
#include "bullet.h"

class bulletManger
{
private:
	std::vector<bullet*>			m_vecBullet;
	std::vector<bullet*>::iterator	m_iter;

public:
	HRESULT init(int vecMaxSize);
	void release();
	void update();
	void render(HDC hdc);

	void fire(const char * imageName, float scale, float radius,
		float speed, float posX, float posY, float range, float expRadius, float dmage, float knokBack, float angle, tagBulletInfo bulletInfo);

	bulletManger();
	~bulletManger();
};

