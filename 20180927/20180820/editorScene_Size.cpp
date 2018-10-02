#include "stdafx.h"
#include "editorScene_Size.h"
#include "button.h"
#include "image.h"

static void Func_MapSize1(void)
{
	editorScene_Size::m_nMapSize = 800;
}

static void Func_MapSize2(void)
{
	editorScene_Size::m_nMapSize = 1600;
}

static void Func_MapSize3(void)
{
	editorScene_Size::m_nMapSize = 2000;
}

static void Func_MapSize4(void)
{
	editorScene_Size::m_nMapSize = 2400;
}

static void Func_MapCheck(void)
{
	editorScene_Size::m_bIsSizeCheck = true;
}


void editorScene_Size::SetSize()
{

	m_pImg_Box5 = IMAGEMANAGER->addImage("box5", "image/wook/white.bmp", 320, 84, true, RGB(255, 0, 255));

	m_pBtn800x = new button;
	m_pBtn800x->init("800x", WINSIZEX / 2, 80, PointMake(0, 1), PointMake(0, 0), Func_MapSize1);

	m_pBtn1600x = new button;
	m_pBtn1600x->init("1600x", WINSIZEX / 2, 180, PointMake(0, 1), PointMake(0, 0), Func_MapSize2);

	m_pBtn2000x = new button;
	m_pBtn2000x->init("2000x", WINSIZEX / 2, 280, PointMake(0, 1), PointMake(0, 0), Func_MapSize3);

	m_pBtn2400x = new button;
	m_pBtn2400x->init("2400x", WINSIZEX / 2, 380, PointMake(0, 1), PointMake(0, 0), Func_MapSize4);

	m_pBtnSizeCheck = new button;
	m_pBtnSizeCheck->init("size_check", WINSIZEX / 2 + m_pImg_SizeBox->getWidth() / 2 - IMAGEMANAGER->findImage("size_check")->getWidth() / 2, WINSIZEY / 2 + m_pImg_SizeBox->getHeight() / 2 - (IMAGEMANAGER->findImage("size_check")->getHeight() / 2 + 84), PointMake(0, 1), PointMake(0, 0), Func_MapCheck);

}

editorScene_Size::editorScene_Size()
{
}


editorScene_Size::~editorScene_Size()
{
}
