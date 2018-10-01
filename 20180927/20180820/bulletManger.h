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

	bulletManger();
	~bulletManger();
};

