#pragma once

#include <Jai_Factory.h>
#include<vector>
#include"opencv.hpp"

using namespace std;


enum
{
	SoftWareTrig   =0,
	ContinuousTrig =1,
};

class camera_jai
{


public:
	camera_jai(void);
	~camera_jai(void);


	bool setParam(FACTORY_HANDLE  hFactory,vector<int8_t> cameraID,CWnd* pWnd=NULL,int trigSetting=ContinuousTrig,int index=-1);
	bool open();

	bool openCamera();
	bool settingCamera();
	bool startCapture();
	bool stopCapture();
	bool closeCamera();
	void OnBnClickedSwtriggerbutton();
	bool changeAcquitionModel(int trigSetting);
private:

	void StreamCBFunc(J_tIMAGE_INFO * pAqImageInfo);
	void PrepareContinuousSetting();
	void PrepareSwTrigSetting();
	void ShowErrorMsg(CString message, J_STATUS_TYPE error);


public:
	FACTORY_HANDLE  m_hFactory;     // Factory Handle
	int8_t          m_sCameraId[J_CAMERA_ID_SIZE];    // Camera ID
	CAM_HANDLE      m_hCam;         // Camera Handle
	THRD_HANDLE     m_hThread;      // Acquisition Thread Handle
	VIEW_HANDLE		m_hView;	// View handle
	CWnd			*m_pCWnd;
	int			    m_TrigSetting;   //软触发0，连续触发1
	int				m_camIndex;

	
	cv::Mat img;


};

