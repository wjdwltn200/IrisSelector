#include "stdafx.h"
#include "titleScene.h"


HRESULT titleScene::init()
{
	m_titleScene = IMAGEMANAGER->addImage("titleScene", WINSIZEX, WINSIZEY);
	return S_OK;
}

void titleScene::release()
{
	
}

void titleScene::update()
{

}

void titleScene::render(HDC hdc)
{
}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
