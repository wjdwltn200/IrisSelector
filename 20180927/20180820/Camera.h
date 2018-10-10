#pragma once
#include "singletonBase.h"

class Camera : public singletonBase<Camera>
{
private:
	int m_nMiniMap_LocationX; // ¹Ì´Ï¸Ê »ý¼ºµÇ´Â À§Ä¡
	int m_nMiniMap_LocationY; 

	//POINT m_ptCamera;
	//POINT m_ptMiniCamera;

	/*RECT m_rcCamera;
	RECT m_rcMiniCamera;*/

public:
	SYNTHESIZE(int, m_ptMoveCameraX, focusCameraX); // °Ñ¸é
	SYNTHESIZE(int, m_ptCameraX, CameraX);
	SYNTHESIZE(int, m_ptMoveCameraY, focusCameraY);
	SYNTHESIZE(int, m_ptCameraY, CameraY);

	SYNTHESIZE(int, m_ptMiniCameraX, focusMiniCameraX);
	SYNTHESIZE(int, m_ptCameraMiniX, CameraMiniX);
	SYNTHESIZE(int, m_ptMiniCameraY, focusMiniCameraY);
	SYNTHESIZE(int, m_ptCameraMiniY, CameraMiniY);

	//SYNTHESIZE(POINT, m_ptCamera, CameraPoint); // °Ñ¸é
	//SYNTHESIZE(POINT, m_ptMiniCamera, MiniCameraPoint); // °Ñ¸é
	//SYNTHESIZE(RECT, m_rcCamera, CameraRect);
	//SYNTHESIZE(RECT, m_rcMiniCamera, MiniCameraRect);



	HRESULT init();
	void MiniMapRatioInit();
	
	void release();
	void update();
	void render(HDC hdc);
	Camera();
	~Camera();
};

