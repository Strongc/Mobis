#pragma once
#include <Jai_Factory.h>
#include<vector>

#include"camera_jai.h"
using namespace std;
class cameraManage
{
public:
	cameraManage(void);
	~cameraManage(void);
	bool findCamera();
	bool allocationCameraConnect();
private:
	void ShowErrorMsg(CString message, J_STATUS_TYPE error);
	bool closeFactory();
	bool openFactory();
public:
	FACTORY_HANDLE  m_hFactory;     // Factory Handle
	vector<string> m_cameraInfList;
	vector<vector<int8_t> >m_cameraIDList;
	vector<camera_jai> m_cameraList;
	
};

