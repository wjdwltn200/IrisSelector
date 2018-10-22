#include "stdafx.h"
#include "uiManager.h"


HRESULT uiManager::init(int vecMaxSize)
{
	m_vecUIObjects.reserve(vecMaxSize);
	return E_NOTIMPL;
}

void uiManager::release()
{
	for (m_iter = m_vecUIObjects.begin(); m_iter != m_vecUIObjects.end(); m_iter++)
	{
		delete (*m_iter);
	}
	m_vecUIObjects.clear();
}

void uiManager::update()
{
	if (g_saveData.gGamePause) return;

	for (m_iter = m_vecUIObjects.begin(); m_iter != m_vecUIObjects.end(); m_iter++)
	{
		(*m_iter)->update();
	}
}

void uiManager::render(HDC hdc)
{
	for (m_iter = m_vecUIObjects.begin(); m_iter != m_vecUIObjects.end(); m_iter++)
	{
	}
}

void uiManager::addUIObject(uiObject * pUI)
{
	((uiButton*)pUI)->setDelegate(this);
}

void uiManager::OnClick(uiButton * pSender)
{
}

uiManager::uiManager()
{
}


uiManager::~uiManager()
{
}


UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}
