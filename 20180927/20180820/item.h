#pragma once
class image;
class animation;

#define ITEM_IDLE_Y_SIZE 5.0f

class item
{
private:
	image * m_pImg;
	image * m_pImgShadow;

	animation * m_pAni;

	RECT	m_rc;
	//float	m_fAngle;

	//float	m_fMoveAngle;
	//float	m_fAngleRadius;

	float m_fItemIdleY;
	float m_fItemIdleCurrY;
	bool m_isItemIdle;
	int m_ItemAlphaNum;

	bool	m_isAlive;
	tagItemInfo m_tItemInfo;

public:
	HRESULT init(const char * imageName, tagItemInfo itemInfo);
	void release();
	void update();
	void render(HDC hdc);
	
	int getItemSkill() { return m_tItemInfo.tSkillType; }
	float getItemRadius() { return m_tItemInfo.tRadius; }

	tagItemInfo getItemInfo() { return m_tItemInfo; }

	bool getIsAlive() { return m_isAlive; }
	void setIsAlive(bool alive) { m_isAlive = alive; }
	item();
	~item();
};

