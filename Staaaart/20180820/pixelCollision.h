#pragma once
#include "scene.h"

class font;

class pixelCollision : public scene
{
private:
	image * m_pImgBall;
	image * m_pImgMountain;

	font * m_font;

	RECT	m_rc;
	FPOINT	m_position;
	float	m_currY;
	bool	m_isCollision;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	pixelCollision();
	~pixelCollision();
};

