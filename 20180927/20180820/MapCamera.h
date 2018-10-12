#pragma once
#include "singletonBase.h"

class editorScene_re;

#define CAMERA_WIDTH 518 
#define CAMERA_HEIGHT 684

#define LOC_MINIMAPX_MAP 267
#define LOC_MINIMAPY_MAP 190

//////////////////////////////



#define SAMPLE_COUNTX 5
#define SAMPLE_COUNTY 9

#define CAMERA_destX 260
#define CAMERA_destY 105
#define CAMERA_SPEED 5
#define MINIMAP_destX 10
#define MINIMAP_destY 110
#define MINIMAP_WIDTH 180
#define MINIMAP_HEIGHT 180

#define MAX_TILECOUNTX 60
#define MAX_TILECOUNTY 60


class MapCamera : public singletonBase<Camera>
{
private:
	int m_nMiniMap_LocationX; // �̴ϸ� �����Ǵ� ��ġ
	int m_nMiniMap_LocationY;

	editorScene_re m_pEdtior;

	//POINT m_ptCamera;
	//POINT m_ptMiniCamera;

	/*RECT m_rcCamera;
	RECT m_rcMiniCamera;*/

public:
	SYNTHESIZE(float, m_ptMoveCameraX, focusCameraX); // �Ѹ�
	SYNTHESIZE(float, m_ptCameraX, CameraX);
	SYNTHESIZE(float, m_ptMoveCameraY, focusCameraY);
	SYNTHESIZE(float, m_ptCameraY, CameraY);

	SYNTHESIZE(float, m_ptMiniCameraX, focusMiniCameraX);
	SYNTHESIZE(float, m_ptCameraMiniX, CameraMiniX);
	SYNTHESIZE(float, m_ptMiniCameraY, focusMiniCameraY);
	SYNTHESIZE(float, m_ptCameraMiniY, CameraMiniY);

	//SYNTHESIZE(POINT, m_ptCamera, CameraPoint); // �Ѹ�
	//SYNTHESIZE(POINT, m_ptMiniCamera, MiniCameraPoint); // �Ѹ�
	//SYNTHESIZE(RECT, m_rcCamera, CameraRect);
	//SYNTHESIZE(RECT, m_rcMiniCamera, MiniCameraRect);



	HRESULT init();
	void MiniMapRatioInit();

	void release();
	void update();
	void keyUpdate();

	void render(HDC hdc);
	MapCamera();
	~MapCamera();
};
