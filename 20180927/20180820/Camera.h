#pragma once
#include "singletonBase.h"

class Camera : public singletonBase<Camera>
{
private:
	int m_nMiniMap_LocationX; // �̴ϸ� �����Ǵ� ��ġ
	int m_nMiniMap_LocationY; 

public:
	SYNTHESIZE(int, m_ptMoveCameraX, focusCameraX); // �Ѹ�
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

