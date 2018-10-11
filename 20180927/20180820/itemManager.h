#pragma once
#include <vector>
#include "item.h"

class itemManager
{
private:
	std::vector<item*>			m_vecItem;
	std::vector<item*>::iterator	m_iter;

public:
	HRESULT init(int vecMaxSize);
	void release();
	void update();
	void render(HDC hdc);

	void itemDrop(const char * imageName, tagItemInfo bulletInfo, effectManager * pEffMag);

	inline std::vector<item*> getVecItem()
	{
		return m_vecItem;
	}

	itemManager();
	~itemManager();
};

