#include "stdafx.h"
#include "itemManager.h"


HRESULT itemManager::init(int vecMaxSize)
{
	m_vecItem.reserve(vecMaxSize);

	m_vecItemList = TXTDATA->txtLoad("ItemList.txt");
	m_currX = atoi(m_vecItemList[0].c_str());
	m_currY = atoi(m_vecItemList[0].c_str());

	return S_OK;
}

void itemManager::release()
{
	for (m_iter = m_vecItem.begin(); m_iter != m_vecItem.end(); m_iter++)
	{
		(*m_iter)->release();
	}
	m_vecItem.clear();
}

void itemManager::update()
{
	for (m_iter = m_vecItem.begin(); m_iter != m_vecItem.end(); m_iter++)
	{
		if ((*m_iter)->getIsAlive())
		{
			(*m_iter)->update();
		}
	}
}

void itemManager::render(HDC hdc)
{
	for (m_iter = m_vecItem.begin(); m_iter != m_vecItem.end(); m_iter++)
	{
		if ((*m_iter)->getIsAlive())
		{
			(*m_iter)->render(hdc);
		}
	}
}

void itemManager::itemDrop(const char * imageName, tagItemInfo itemInfo, effectManager * pEffMag)
{
	for (m_iter = m_vecItem.begin(); m_iter != m_vecItem.end(); m_iter++)
	{
		if (!(*m_iter)->getIsAlive()) // 죽어있으면 재활용
		{
			(*m_iter)->init(imageName, itemInfo, pEffMag, m_currX, m_currY);

			return;
		}
	}

	item * pItem = new item;
	pItem->init(imageName, itemInfo, pEffMag, m_currX, m_currY);

	m_vecItem.push_back((pItem));
	return;
}

itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}
