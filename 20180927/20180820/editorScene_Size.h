#pragma once

#include "scene.h"

class image;
class button;

#define ID_EDIT               100
#define ID_BUTTON_CONTROL     1000
#define ID_BUTTON_OK          1001

class editorScene_Size : public scene
{
private:
	image * m_pImg_SizeBox;
	image * m_pImg_Box5;

	button * m_pBtn800x;
	button * m_pBtn1600x;
	button * m_pBtn2000x;
	button * m_pBtn2400x;
	button * m_pBtnSizeCheck;


	static bool m_bIsSizeCheck;
	static int m_nMapSize;
public:

	void SetSize();

	editorScene_Size();
	~editorScene_Size();
};

