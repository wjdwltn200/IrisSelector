#pragma once
#include "singletonBase.h"
#include "font.h"

#include <map>
#include <string>

class fontManager : public singletonBase<fontManager>
{
public:
	std::map<std::string, font*>	m_map;
	std::map<std::string, font*>::iterator m_iter;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void addFont();

	fontManager();
	~fontManager();
};

