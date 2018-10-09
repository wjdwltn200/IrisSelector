#pragma once
#include "singletonBase.h"

class Camera : public singletonBase<Camera>
{
private:
	int m_nMiniMap_LocationX; // 미니맵 생성되는 위치
	int m_nMiniMap_LocationY; 

public:
	SYNTHESIZE(int, m_ptMoveCameraX, focusCameraX); // 겉면
	SYNTHESIZE(int, m_ptCameraX, CameraX);
	SYNTHESIZE(int, m_ptMoveCameraY, focusCameraY);
	SYNTHESIZE(int, m_ptCameraY, CameraY);

	SYNTHESIZE(int, m_ptMiniCameraX, focusMiniCameraX);
	SYNTHESIZE(int, m_ptCameraMiniX, CameraMiniX);
	SYNTHESIZE(int, m_ptMiniCameraY, focusMiniCameraY);
	SYNTHESIZE(int, m_ptCameraMiniY, CameraMiniY);

	HRESULT init();
	void MiniMapRatioInit();
	
	void release();
	void update();
	void render(HDC hdc);
	Camera();
	~Camera();
};

