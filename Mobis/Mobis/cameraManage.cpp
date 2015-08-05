#include "stdafx.h"
#include "cameraManage.h"

cameraManage::cameraManage(void)
{
	openFactory();
}

cameraManage::~cameraManage(void)
{
	for (int i = 0; i < m_cameraList.size(); i++)
	{
		m_cameraList[i].~camera_jai();
	}
	closeFactory();
}

bool cameraManage::openFactory()
{
	J_STATUS_TYPE	status = J_ST_SUCCESS;
	status = J_Factory_Open((int8_t*)"", &m_hFactory);
	if(status != J_ST_SUCCESS) 
	{
		ShowErrorMsg(CString("Could not open factory!"), status);
		return FALSE;
	}
	return true;
}


bool cameraManage::findCamera()
{
	//Open Factory and get list of cameras
	J_STATUS_TYPE	status = J_ST_SUCCESS;
	bool8_t			bHasChanged = false;
	uint32_t		iNumOfCameras =	0;


	//closeFactory();
	//openFactory();

	//Look for cameras
	status = J_Factory_UpdateCameraList(m_hFactory, &bHasChanged); 
	if(status != J_ST_SUCCESS) 
	{
		ShowErrorMsg(CString("Could not update camera list!"), status);
		return FALSE;
	}

	if (status == J_ST_SUCCESS && bHasChanged)
	{

		m_cameraInfList.clear();
		m_cameraIDList.clear();
		m_cameraList.clear();
		//Get number of cameras
		status = J_Factory_GetNumOfCameras(m_hFactory, &iNumOfCameras);
		if(status != J_ST_SUCCESS) 
		{
			ShowErrorMsg(CString("Could not get number of cameras!"), status);
			return FALSE;
		}

		if(iNumOfCameras == 0)
		{
			//AfxMessageBox(_T("No camera found!"), MB_OK | MB_ICONINFORMATION);
			return FALSE;
		}
		else if(iNumOfCameras > 0)
		{

			for (uint32_t index = 0; index < iNumOfCameras; index++)
			{
				int8_t   m_CameraId[J_CAMERA_ID_SIZE];    // Camera ID
				uint32_t iCameraIdSize = J_CAMERA_ID_SIZE;
				status = J_Factory_GetCameraIDByIndex(m_hFactory, index, m_CameraId, &iCameraIdSize);
				if(status != J_ST_SUCCESS) 
				{
					ShowErrorMsg(CString("Could not get camera ID!"), status);
					return FALSE;
				}
				vector<int8_t> temp;
				for (int i = 0; i < J_CAMERA_ID_SIZE; i++)
				{
					temp.push_back(m_CameraId[i]);
				}	
				m_cameraIDList.push_back(temp);
				int8_t   sCameraInfo[J_CAMERA_INFO_SIZE];
				int8_t	 sSerialNumber[J_CAMERA_INFO_SIZE];
				uint32_t iCameraInfoSize = J_CAMERA_INFO_SIZE;
				CString ListItemStr;

				//get model name
				status = J_Factory_GetCameraInfo(m_hFactory, m_CameraId, CAM_INFO_MODELNAME, sCameraInfo, &iCameraInfoSize);
				if(status != J_ST_SUCCESS) 
				{
					ShowErrorMsg(CString("Could not get camera ModelName info!"), status);
					return FALSE;
				}

				//Get serial number
				iCameraInfoSize = sizeof(sSerialNumber); //Don't forget to reset the size for each call to J_Factory_GetCameraInfo!
				status = J_Factory_GetCameraInfo(m_hFactory, m_CameraId, CAM_INFO_SERIALNUMBER, sSerialNumber, &iCameraInfoSize);
				if (status != J_ST_SUCCESS)
				{
					ShowErrorMsg(CString("Could not get serial number of the camera!"), status);
					return FALSE;
				}

				ListItemStr = (char*)sCameraInfo;

				//check if the interface is filter driver or socket driver

				if (strstr((char*)m_CameraId, "INT=>FD"))
					ListItemStr += " (Filter Driver)";
				else if (strstr((char*)m_CameraId, "INT=>SD"))
					ListItemStr += " (Socket Driver)";


				m_cameraInfList.push_back(ListItemStr.GetBuffer(0)); 

				CString statusBar;
				statusBar.Format(_T("%d camera(s) found. Double click to connect to a camera"), iNumOfCameras);
			}//end of camera index

		}
	}

	return TRUE;
}

bool cameraManage::allocationCameraConnect()
{
	if(m_cameraIDList.size()==1||m_cameraIDList.size()==2)
	{
		//camera_jai camera1;
		//m_cameraList.push_back(camera1);

		m_cameraList.resize(1);
		CWnd *pWnd=CWnd::FindWindow(NULL,_T(" 螺丝检测"));//获取目标窗口

		m_cameraList[0].setParam(m_hFactory,m_cameraIDList[0],pWnd,ContinuousTrig,0);
		m_cameraList[0].open();	



		//if(m_cameraIDList.size()>=4)
		//{
		//	m_cameraList[1].setParam(m_hFactory,m_cameraIDList[2],pWnd,ContinuousTrig,1);
		//	m_cameraList[1].open();	
		//}
	}
	else if(m_cameraIDList.size()==4)
	{
		m_cameraList.resize(2);
		CWnd *pWnd=CWnd::FindWindow(NULL,_T(" 螺丝检测"));//获取目标窗口

		m_cameraList[0].setParam(m_hFactory,m_cameraIDList[0],pWnd,ContinuousTrig,0);
		m_cameraList[0].open();	




		m_cameraList[1].setParam(m_hFactory,m_cameraIDList[1],pWnd,ContinuousTrig,1);
		m_cameraList[1].open();	

	}


	return true;
}

void cameraManage::ShowErrorMsg(CString message, J_STATUS_TYPE error)
{
	CString errorMsg;
	errorMsg.Format(_T("%s: Error = %d: "), message, error);

	switch(error)
	{
	case J_ST_INVALID_BUFFER_SIZE:	errorMsg += "Invalid buffer size ";	                break;
	case J_ST_INVALID_HANDLE:		errorMsg += "Invalid handle ";		                break;
	case J_ST_INVALID_ID:			errorMsg += "Invalid ID ";			                break;
	case J_ST_ACCESS_DENIED:		errorMsg += "Access denied ";		                break;
	case J_ST_NO_DATA:				errorMsg += "No data ";				                break;
	case J_ST_ERROR:				errorMsg += "Generic error ";		                break;
	case J_ST_INVALID_PARAMETER:	errorMsg += "Invalid parameter ";	                break;
	case J_ST_TIMEOUT:				errorMsg += "Timeout ";				                break;
	case J_ST_INVALID_FILENAME:		errorMsg += "Invalid file name ";	                break;
	case J_ST_INVALID_ADDRESS:		errorMsg += "Invalid address ";		                break;
	case J_ST_FILE_IO:				errorMsg += "File IO error ";		                break;
	case J_ST_GC_ERROR:				errorMsg += "GenICam error ";		                break;
	case J_ST_VALIDATION_ERROR:		errorMsg += "Settings File Validation Error ";		break;
	case J_ST_VALIDATION_WARNING:	errorMsg += "Settings File Validation Warning ";    break;
	}

	AfxMessageBox(errorMsg, MB_OKCANCEL | MB_ICONINFORMATION);

}

bool cameraManage::closeFactory()
{
	J_STATUS_TYPE	status = J_ST_SUCCESS;

	if (m_hFactory)
	{
		// Close factory
		status = J_Factory_Close(m_hFactory);
		if(status != J_ST_SUCCESS) 
		{
			ShowErrorMsg(CString("Could not open camera!"), status);
			return false;
		}
		m_hFactory = NULL;
		TRACE("Closed factory\n");
	}
	return true;
}