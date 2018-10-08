#pragma once
class animation;
class PlayerCharacter;
class bulletManger;
class PlayerCharacter;

class monster
{
private:
	image * m_monsterType;
	animation * m_monsterMove;
	PlayerCharacter * m_player;

	tagBulletInfo m_tBulletInfo;
	tagBulletInfo * m_tBulletInfoPoint;
	tagBulletInfo m_tBulletInfoSub;
	tagBulletInfo * m_tBulletInfoSubPoint;

	bulletManger* m_pBulletMag;
	PlayerCharacter* m_PlayerCharPoint;

	tagMonInfo m_tMonInfo;
public:
	HRESULT init(const char * strKey, tagMonInfo monInfo, bulletManger* bulletP, PlayerCharacter* playerPoint);
	void release();
	void update();
	void Move();
	void fireAtk();
	void render(HDC hdc);

	tagMonInfo getMonInfo() { return m_tMonInfo; }
	void setAlive(bool Alive) { m_tMonInfo.tIsAlive = Alive; };
	monster();
	~monster();
};

