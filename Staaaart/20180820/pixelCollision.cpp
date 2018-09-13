#include "stdafx.h"
#include "pixelCollision.h"
#include "font.h"

HRESULT pixelCollision::init()
{
	IMAGEMANAGER->addImage("image/background.bmp",
		"image/background.bmp", 600, 800, true, RGB(255, 0, 255));
	m_pImgMountain = IMAGEMANAGER->addImage("image/mountain.bmp",
		"image/mountain.bmp", 800, 600, true, RGB(255, 0, 255));
	m_pImgBall = IMAGEMANAGER->addImage("image/ball.bmp",
		"image/ball.bmp", 60, 60, true, RGB(255, 0, 255));

	m_position.x = WINSIZEX / 2;
	m_position.y = WINSIZEY / 2;

	m_rc = RectMakeCenter(m_position.x, m_position.y,
		m_pImgBall->getWidth(), m_pImgBall->getHeight());

	m_currY = m_position.y + m_pImgBall->getHeight() / 2;

	m_font->init(100.0f, 100.0f, "½Ã¹ß!", 200, 100, 0, 0, 2, 0, 0, 0, 1, _T("±¼¸²Ã¼"));

	return S_OK;
}

void pixelCollision::release()
{
}

void pixelCollision::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_position.x -= 2.0f;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_position.x += 2.0f;
	}

	m_currY = (int)m_position.y + m_pImgBall->getHeight() / 2;
	for (int i = m_currY - 50; i < m_currY + 50; i++)
	{
		COLORREF color = GetPixel(m_pImgMountain->getMemDC(),
			(int)m_position.x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			m_position.y = i - m_pImgBall->getHeight() / 2;
			break;
		}
	}

}

void pixelCollision::render(HDC hdc)
{
	IMAGEMANAGER->findImage("image/background.bmp")->render(hdc, 0, 0);

	m_font->render(hdc);

	m_pImgMountain->render(hdc, 0, 0);
	m_pImgBall->render(hdc, m_position.x, m_position.y);
}

pixelCollision::pixelCollision()
{
}


pixelCollision::~pixelCollision()
{
}
