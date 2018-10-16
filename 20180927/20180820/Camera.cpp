#include "stdafx.h"
#include "Camera.h"
#include "PlayerCharacter.h"

HRESULT Camera::init()
{
	
	m_pCharacter = new PlayerCharacter;
	m_pCharacter->init();

	MiniMapRatioInit();

	return S_OK;
}

void Camera::MiniMapRatioInit()
{
	m_nMiniMap_LocationX = LOC_MINIMAPX;
	m_nMiniMap_LocationY = LOC_MINIMAPY;
	m_ptMoveCameraX = WINSIZEX / 2;
	m_ptMoveCameraY = WINSIZEY / 2;

	//m_rcCamera.left = 0;
	//m_rcCamera.right = WINSIZEX;
	//m_rcCamera.top = 0;
	//m_rcCamera.bottom = WINSIZEY;

	//m_rcMiniCamera.top = 0;
	//m_rcMiniCamera.bottom = WINSIZEY;


	m_ptCameraMiniX = LOC_MINIMAPX;
	m_ptCameraMiniY = LOC_MINIMAPY;
}





void Camera::release()
{
}

void Camera::update()
{
	if (m_ptMoveCameraX < WINSIZEX / 2) m_ptMoveCameraX = WINSIZEX / 2;
	if (m_ptMoveCameraX > (g_saveData.gTileMaxCountX * TILE_SIZEX)) (g_saveData.gTileMaxCountX * TILE_SIZEX);
	if (m_ptMoveCameraY < WINSIZEY / 2) m_ptMoveCameraY = WINSIZEY / 2;
	if (m_ptMoveCameraY > (g_saveData.gTileMaxCountY * TILE_SIZEY)) (g_saveData.gTileMaxCountY * TILE_SIZEY);

	m_ptCameraX = m_ptMoveCameraX - WINSIZEX / 2;
	if (m_ptCameraX < 0) m_ptCameraX = 0;
	if (m_ptCameraX > (g_saveData.gTileMaxCountX * TILE_SIZEX) - WINSIZEX) m_ptCameraX = (g_saveData.gTileMaxCountX * TILE_SIZEX) - WINSIZEX;

	m_ptCameraY = m_ptMoveCameraY - WINSIZEY / 2;
	if (m_ptCameraY < 0) m_ptCameraY = 0;
	if (m_ptCameraY > (g_saveData.gTileMaxCountY * TILE_SIZEY) - WINSIZEY) m_ptCameraY = (g_saveData.gTileMaxCountY * TILE_SIZEY) - WINSIZEY;

	// 미니맵
	//if (m_ptCameraMiniX < 0) m_ptCameraMiniX = 0; // 0보다 작을시 끝에 고정
	//if (m_ptCameraMiniX > LOC_MINIMAPX) m_ptCameraMiniX = LOC_MINIMAPX;  
	//if (m_ptCameraMiniY < 0) m_ptCameraMiniY = 0; 
	//if (m_ptCameraMiniY > LOC_MINIMAPY) m_ptCameraMiniY = LOC_MINIMAPY;

	//m_ptMiniCameraX = m_ptCameraMiniX - LOC_MINIMAPX;
	//if (m_ptMiniCameraX < 0) m_ptMiniCameraX = 0;
	//if (m_ptMiniCameraX > WINSIZEX - LOC_MINIMAPX) m_ptMiniCameraX = WINSIZEX - LOC_MINIMAPX;

	//m_ptMiniCameraY = m_ptCameraMiniY - LOC_MINIMAPY;
	//if (m_ptMiniCameraY < 0) m_ptMiniCameraY = 0;
	//if (m_ptMiniCameraY > WINSIZEY - LOC_MINIMAPY) m_ptMiniCameraY = WINSIZEY - LOC_MINIMAPY;
}

void Camera::keyUpdate()
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		m_ptMoveCameraX -= m_pCharacter->getSpeed();
		m_ptCameraMiniX -= m_pCharacter->getSpeed();
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		m_ptMoveCameraX += m_pCharacter->getSpeed();
		m_ptCameraMiniX += m_pCharacter->getSpeed();
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		m_ptMoveCameraY -= m_pCharacter->getSpeed();
		m_ptCameraMiniY -= m_pCharacter->getSpeed();
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		m_ptMoveCameraY += m_pCharacter->getSpeed();
		m_ptCameraMiniY += m_pCharacter->getSpeed();
	}

}

void Camera::render(HDC hdc)
{
}

Camera::Camera()
{
}


Camera::~Camera()
{
}
