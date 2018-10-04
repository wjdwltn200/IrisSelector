#pragma once
class image;
class animation;

class item
{
private:
	image * m_pImg;
	animation * m_pAni;

	RECT	m_rc;
	float	m_fX, m_fY;
	//float	m_fAngle;

	//float	m_fMoveAngle;
	//float	m_fAngleRadius;

	bool	m_isAlive;
	tagItemInfo m_tItemInfo;

public:
	HRESULT init(const char * imageName, float posX, float posY, tagItemInfo itemInfo);
	void release();
	void update();
	void render(HDC hdc);
	
	int getItemSkill() { return m_tItemInfo.tSkillType; }
	float getItemRadius() { return m_tItemInfo.tRadius; }

	float getX() { return m_fX; }
	float getY() { return m_fY; }

	bool getIsAlive() { return m_isAlive; }
	void setIsAlive(bool alive) { m_isAlive = alive; }
	item();
	~item();
};

