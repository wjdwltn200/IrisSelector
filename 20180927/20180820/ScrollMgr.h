#pragma once
#include "singletonBase.h"

//ȭ���� WINSIZEX �� WINSIZEY
// ó�� ��ǥ�� 0, 0

class ScrollMgr : public singletonBase<ScrollMgr>
{
private:
	float m_fX;
	float m_fY;
	float m_fMaxofX;
	float m_fMaxofY;
	


public:
	HRESULT init();
	//void MiniMapRatioInit();

	void release();
	void update(float TileX, float TileY);
	void keyUpdate();

	void render(HDC hdc);

	ScrollMgr();
	~ScrollMgr();
};

