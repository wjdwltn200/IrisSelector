#include "stdafx.h"
#include "EndingScene.h"
#include "image.h"
#include "animation.h"

HRESULT EndingScene::init()
{
	m_pImg_BG = IMAGEMANAGER->findImage("black");
	m_pImg_Alice = IMAGEMANAGER->findImage("alice_move"); // 600, 300
	m_pImg_Alice->setX(100);
	m_pImg_Alice->setY(250);

	m_pAni = new animation;
	m_pAni->init(m_pImg_Alice->getWidth(), m_pImg_Alice->getHeight(), 600, 300);
	m_pAni->setDefPlayFrame(false, true);
	m_pAni->setFPS(12);
	m_pAni->start();
	

	return S_OK;
}

void EndingScene::update()
{
	m_pAni->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void EndingScene::release()
{
}

void EndingScene::render(HDC hdc)
{
	m_pImg_BG->render(hdc, 0, 0);
	m_pImg_Alice->aniRender(hdc, m_pImg_Alice->getX(), m_pImg_Alice->getY(), m_pAni, 1);
}

EndingScene::EndingScene()
{
}


EndingScene::~EndingScene()
{
}
