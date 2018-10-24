#include "stdafx.h"
#include "CreatorScene.h"
#include "image.h"
#include "button.h"


bool CreatorScene::buttonInput = false;

static void Func_button1(void)
{
	CreatorScene::buttonInput = true; // �ó����� ����
}



HRESULT CreatorScene::init()
{
	m_pImg_BG = IMAGEMANAGER->findImage("black");
	m_pButton1 = new button;
	//m_pButton1->init()


	return S_OK;
}

void CreatorScene::update()
{
}

void CreatorScene::release()
{
}

void CreatorScene::render(HDC hdc)
{
	m_pImg_BG->render(hdc, 0, 0);


	AddFontResourceA("BMHANNAAir_ttf.ttf");

	char SzText1[128];
	// TRANSPARENT : ����, OPAQUE : ������
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 240, 200));
	MY_UTIL::FontOption(hdc, 42, 0);


	char SzText2[256];
	int temp = 58;
	// TRANSPARENT : ����, OPAQUE : ������
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 240, 200));
	MY_UTIL::FontOption(hdc, 42, 0);

	sprintf_s(SzText1, "%s : ", "�� �� �� ��");
	TextOut(hdc, WINSIZEX / 2 - 110, 100 + temp, SzText1, strlen(SzText1)); temp += 58;

	sprintf_s(SzText2, "%s  ", "������");
	TextOut(hdc, WINSIZEX / 2 - 70, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	sprintf_s(SzText2, "%s  ", "���ο�");
	TextOut(hdc, WINSIZEX / 2 - 70, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	sprintf_s(SzText2, "%s  ", "�̼���");
	TextOut(hdc, WINSIZEX / 2 - 70, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	sprintf_s(SzText2, "%s :  ", "������α׷�");
	TextOut(hdc, WINSIZEX / 2 - 124, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	SetTextColor(hdc, RGB(255, 140, 200));
	sprintf_s(SzText2, "%s  ", "�����Ʃ��� (winAPI)");
	TextOut(hdc, WINSIZEX / 2 - 202, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	SetTextColor(hdc, RGB(255, 240, 200));
	sprintf_s(SzText2, "%s  ", "���۱Ⱓ : ");
	TextOut(hdc, WINSIZEX / 2 - 95, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	SetTextColor(hdc, RGB(255, 240, 200));
	sprintf_s(SzText2, "%s  ", "3�� (3 week)");
	TextOut(hdc, WINSIZEX / 2 - 123, 100 + temp, SzText2, strlen(SzText2)); temp += 33;

	MY_UTIL::FontOption(hdc, 29, 0);
	SetTextColor(hdc, RGB(255, 200, 188));
	sprintf_s(SzText2, "%s  ", "2018.10.01 ~ 2018.10.22");
	TextOut(hdc, WINSIZEX / 2 - 163, 100 + temp, SzText2, strlen(SzText2)); temp += 58;

	MY_UTIL::FontDelete(hdc);
}




CreatorScene::CreatorScene()
{
}


CreatorScene::~CreatorScene()
{
}