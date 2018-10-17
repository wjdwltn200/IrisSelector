#pragma once
#include "singletonBase.h"

//화면은 WINSIZEX 와 WINSIZEY
// 처음 좌표는 0, 0

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

