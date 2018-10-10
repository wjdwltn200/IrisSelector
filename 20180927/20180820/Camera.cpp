#include "stdafx.h"
#include "Camera.h"


HRESULT Camera::init()
{
	

	MiniMapRatioInit();

	return S_OK;
}

void Camera::MiniMapRatioInit()
{
	m_nMiniMap_LocationX = LOC_MINIMAPX;
	m_nMiniMap_LocationY = LOC_MINIMAPY;

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
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_ptMoveCameraX -= 10;
		m_ptCameraMiniX -= 10;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_ptMoveCameraX += 10;
		m_ptCameraMiniX += 10;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		m_ptMoveCameraY -= 10;
		m_ptCameraMiniY -= 10;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		m_ptMoveCameraY += 10;
		m_ptCameraMiniY += 10;
	}


	if (m_ptMoveCameraX < 0) m_ptMoveCameraX = 0;
	if (m_ptMoveCameraX > (g_saveData.gTileMaxCountX * 40)) (g_saveData.gTileMaxCountX * 40);
	if (m_ptMoveCameraY < 0) m_ptMoveCameraY = 0;
	if (m_ptMoveCameraY > (g_saveData.gTileMaxCountY * 40)) (g_saveData.gTileMaxCountY * 40);

	m_ptCameraX = m_ptMoveCameraX - WINSIZEX / 2;
	if (m_ptCameraX < 0) m_ptCameraX = 0;
	if (m_ptCameraX > (g_saveData.gTileMaxCountX * 40) - WINSIZEX) m_ptCameraX = (g_saveData.gTileMaxCountX * 40) - WINSIZEX;

	m_ptCameraY = m_ptMoveCameraY - WINSIZEY / 2;
	if (m_ptCameraY < 0) m_ptCameraY = 0;
	if (m_ptCameraY > (g_saveData.gTileMaxCountY * 40) - WINSIZEY) m_ptCameraY = (g_saveData.gTileMaxCountY * 40) - WINSIZEY;

	// ¹Ì´Ï¸Ê
	if (m_ptCameraMiniX < 0) m_ptCameraMiniX = 0;
	if (m_ptCameraMiniX > LOC_MINIMAPX) m_ptCameraMiniX = LOC_MINIMAPX;
	if (m_ptCameraMiniY < 0) m_ptCameraMiniY = 0;
	if (m_ptCameraMiniY > LOC_MINIMAPY) m_ptCameraMiniY = LOC_MINIMAPY;

	m_ptMiniCameraX = m_ptCameraMiniX - LOC_MINIMAPX;
	if (m_ptMiniCameraX < 0) m_ptMiniCameraX = 0;
	if (m_ptMiniCameraX > WINSIZEX - LOC_MINIMAPX) m_ptMiniCameraX = WINSIZEX - LOC_MINIMAPX;

	m_ptMiniCameraY = m_ptCameraMiniY - LOC_MINIMAPY;
	if (m_ptMiniCameraY < 0) m_ptMiniCameraY = 0;
	if (m_ptMiniCameraY > WINSIZEY - LOC_MINIMAPY) m_ptMiniCameraY = WINSIZEY - LOC_MINIMAPY;
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
