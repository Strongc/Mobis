#include "stdafx.h"
#include "camera_jai.h"
#include"opencv.hpp"
#include"resource.h"
#include "types.h"

camera_jai::camera_jai(void)
{
	m_hFactory = NULL;
	m_hCam = NULL;
	memset(m_sCameraId,0,sizeof(m_sCameraId));
	m_hThread = NULL;
	m_hView = NULL;
	m_pCWnd =NULL;
	m_TrigSetting =ContinuousTrig;

	m_camIndex=-1;
}

camera_jai::~camera_jai(void)
{
	stopCapture();
	closeCamera();
}

bool camera_jai::setParam(FACTORY_HANDLE  Factory,vector<int8_t> cameraID,CWnd* pWnd ,int trigSetting,int index)
{
	m_hFactory = Factory;

	memset(m_sCameraId,0,sizeof(m_sCameraId));
	for (int i = 0; i < cameraID.size(); i++)
	{
		m_sCameraId[i] = cameraID[i];
	}
	m_pCWnd = pWnd;
	m_TrigSetting = trigSetting;

	m_camIndex = index;
	return true;
}

bool camera_jai::open()
{
	openCamera();
	settingCamera();
	startCapture();
	return true;
}

bool camera_jai::openCamera()
{

	// close a previous camera and open a selected camera
	J_STATUS_TYPE	status = J_ST_SUCCESS;

	if(!m_hCam)
	{

		//open the selected camera
		status = J_Camera_Open(m_hFactory, m_sCameraId, &m_hCam);
		if(status != J_ST_SUCCESS) 
		{
			ShowErrorMsg(CString("Could not open camera!"), status);
			return false;
		}

		//Make sure streaming is supported!
		uint32_t numStreams = 0;
		status = J_Camera_GetNumOfDataStreams(m_hCam, &numStreams);
		if (status != J_ST_SUCCESS)
		{
			ShowErrorMsg(CString("Error with J_Camera_GetNumOfDataStreams."), status);
			return false;
		}

	}
	return true;

}

bool camera_jai::startCapture()
{
	uint32_t        nNodes;
	J_STATUS_TYPE   retval;
	NODE_HANDLE     hNode;
	int8_t          sNodeName[256];
	uint32_t        size;// Get the number of nodes
	vector<CString> s;

	retval = J_Camera_GetNumOfNodes(m_hCam, &nNodes);
	if (retval == J_ST_SUCCESS)
	{  
		CString t1;
		t1.Format("%u nodes were found\n", nNodes);
		s.push_back(t1);
		for (uint32_t index = 0; index < nNodes; ++index)  
		{    // Get node handle    
			retval = J_Camera_GetNodeByIndex(m_hCam, index, &hNode);    
			if (retval == J_ST_SUCCESS)    
			{      // Get node name      
				size = sizeof(sNodeName);      
				retval = J_Node_GetName(hNode, sNodeName, &size, 0);      
				if (retval == J_ST_SUCCESS)      
				{        // Print out the name        
					//printf("%u NodeName = %s\n", index, sNodeName); 
					CString t2;
					t2.Format("%u NodeName = %s\n", index, sNodeName);
					s.push_back(t2);

				}    
			}  
		}
	}




	J_STATUS_TYPE	status = J_ST_SUCCESS;

	int64_t int64Val;
	int64_t pixelFormat;

	SIZE	ViewSize;
	POINT	TopLeft;


	// Get Width from the camera
	status = J_Camera_GetValueInt64(m_hCam, (int8_t*)"Width", &int64Val);
	ViewSize.cx = (LONG)int64Val;     // Set window size cx

	// Get Height from the camera
	status = J_Camera_GetValueInt64(m_hCam, (int8_t*)"Height", &int64Val);
	ViewSize.cy = (LONG)int64Val;     // Set window size cy

	// Get pixelformat from the camera
	status = J_Camera_GetValueInt64(m_hCam, (int8_t*)"PixelFormat", &int64Val);
	pixelFormat = int64Val;

	// Calculate number of bits (not bytes) per pixel using macro
	int bpp = J_BitsPerPixel(pixelFormat);

	// Set window position
	TopLeft.x = 100;
	TopLeft.y = 50;

	////////////////////////////////////////////////////////////////////////////////////////
	//retval = J_Image_OpenViewWindow(_T("GigE Image Viewer"), &TopLeft, &ViewSize, &m_hView);
	//if(retval != J_ST_SUCCESS) 
	//{
	//	ShowErrorMsg(CString("Could not open View Window!"), retval);
	//	return;
	//}
	//retval = J_Image_OpenStreamLight(m_hCam, 0, &m_hThread);
	//if(retval != J_ST_SUCCESS) 
	//{
	//	ShowErrorMsg(CString("Could not open StreamLight!"), retval);
	//	return;
	//}
	//retval = J_Camera_ExecuteCommand(m_hCam, (int8_t*)"AcquisitionStart");
	//if(retval != J_ST_SUCCESS) 
	//{
	//	ShowErrorMsg(CString("Could not Start Acquisition!"), retval);
	//	return;
	//}
	////////////////////////////////////////////////////////////////////////////////////////


	// Open stream
	status = J_Image_OpenStream(m_hCam, 0, reinterpret_cast<J_IMG_CALLBACK_OBJECT>(this), reinterpret_cast<J_IMG_CALLBACK_FUNCTION>(&camera_jai::StreamCBFunc), &m_hThread,(ViewSize.cx*ViewSize.cy*bpp)/8);
	if (status != J_ST_SUCCESS)
	{
		AfxMessageBox(CString("Could not open stream!"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	TRACE("Opening stream succeeded\n");

	// Start Acquisition
	status = J_Camera_ExecuteCommand(m_hCam, (int8_t*)"AcquisitionStart");
	if (status != J_ST_SUCCESS)
	{
		AfxMessageBox(CString("Could not open stream!"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	TRACE("AcquisitionStart succeeded\n");
	return true;
}

bool camera_jai::stopCapture()
{

	J_STATUS_TYPE	status = J_ST_SUCCESS;

	// Stop Acquisition
	if (m_hCam) 
	{
		status = J_Camera_ExecuteCommand(m_hCam, (int8_t*)"AcquisitionStop");
		if(status != J_ST_SUCCESS) 
		{
			ShowErrorMsg(CString("Could not close camera!"), status);
		}
	}

	if(m_hThread)
	{
		// Close stream
		status = J_Image_CloseStream(m_hThread);
		if(status != J_ST_SUCCESS) 
		{
			ShowErrorMsg(CString("Could not close camera!"), status);
		}
		m_hThread = NULL;
		TRACE("Closed stream\n");
	}
	return true;
}

bool camera_jai::closeCamera()
{
	J_STATUS_TYPE	status = J_ST_SUCCESS;
	if (m_hCam)
	{
		// Close camera
		status = J_Camera_Close(m_hCam);
		if(status != J_ST_SUCCESS) 
		{
			ShowErrorMsg(CString("Could not close camera!"), status);
		}
		m_hCam = NULL;
		TRACE("Closed camera\n");
	}
	return true;
}

bool camera_jai::settingCamera()
{
	if(m_TrigSetting == ContinuousTrig )
		PrepareContinuousSetting();
	else if(m_TrigSetting == SoftWareTrig )
		PrepareSwTrigSetting();
	return true;
}

void camera_jai::PrepareContinuousSetting()
{
	J_STATUS_TYPE status;

	if(m_hCam)
	{
		// We have two possible ways of setting up triggers: JAI or GenICam SFNC
		// The JAI trigger setup uses a node called "ExposureMode" and the SFNC uses a node
		// called "TriggerSelector". Therefor we have to determine which way to use here.
		// First we see if a node called "TriggerSelector" exists.
		NODE_HANDLE hNode = NULL;
		status = J_Camera_GetNodeByName(m_hCam, (int8_t*)"TriggerSelector", &hNode);

		// Does the "TriggerSelector" node exist?
		if ((status == J_ST_SUCCESS) && (hNode != NULL))
		{
			// Here we assume that this is GenICam SFNC trigger so we do the following:
			// TriggerSelector=FrameStart
			// TriggerMode=Off
			status = J_Camera_SetValueString(m_hCam, (int8_t*)"TriggerSelector", (int8_t*)"FrameStart");
			if (status != J_ST_SUCCESS)
			{
				ShowErrorMsg(CString("Could not set TriggerSelector!"), status);
				return;
			}
			status = J_Camera_SetValueString(m_hCam, (int8_t*)"TriggerMode", (int8_t*)"Off");
			if (status != J_ST_SUCCESS)
			{
				ShowErrorMsg(CString("Could not set TriggerMode!"), status);
				return;
			}
		}
		else
		{
			// Here we assume that this is JAI trigger so we do the following:
			// ExposureMode=Continuous

			// Set ExposureMode="Continuous"		
			status = J_Camera_SetValueString(m_hCam, (int8_t*)"ExposureMode", (int8_t*)"Continuous");
			if(status != J_ST_SUCCESS) 
			{
				ShowErrorMsg(CString("Could not set ExposureMode!"), status);
				return;
			}
		}
	} // end of if(m_hCamera)


}

void camera_jai::PrepareSwTrigSetting()
{
	J_STATUS_TYPE status;
	if(m_hCam)
	{
		NODE_HANDLE hNode;
		uint32_t iNumOfEnumEntries = 0;
		int64_t int64Val = 0;

		// We have two possible ways of setting up triggers: JAI or GenICam SFNC
		// The JAI trigger setup uses a node called "ExposureMode" and the SFNC uses a node
		// called "TriggerSelector". Therefor we have to determine which way to use here.
		// First we see if a node called "TriggerSelector" exists.
		hNode = NULL;
		status = J_Camera_GetNodeByName(m_hCam, (int8_t*)"TriggerSelector", &hNode);

		// Does the "TriggerSelector" node exist?
		if ((status == J_ST_SUCCESS) && (hNode != NULL))
		{
			// Here we assume that this is GenICam SFNC trigger so we do the following:
			// TriggerSelector=FrameStart
			// TriggerMode=On
			// TriggerSource=Software
			// SequenceMode=Off

			// Set TriggerSelector="FrameStart"
			status = J_Camera_SetValueString(m_hCam, (int8_t*)"TriggerSelector", (int8_t*)"FrameStart");
			if(status != J_ST_SUCCESS) 
			{
				ShowErrorMsg(CString("Could not set TriggerSelector!"), status);
				return;
			}

			// Set TriggerMode="On"
			status = J_Camera_SetValueString(m_hCam, (int8_t*)"TriggerMode", (int8_t*)"On");
			if(status != J_ST_SUCCESS) 
			{
				ShowErrorMsg(CString("Could not set TriggerMode!"), status);
				return;
			}

			// Set TriggerSource="Software" 
			status = J_Camera_SetValueString(m_hCam, (int8_t*)"TriggerSource", (int8_t*)"Software");
			if(status != J_ST_SUCCESS) 
			{
				ShowErrorMsg(CString("Could not set TriggerSource!"), status);
				return;
			}

			//这个相机可能没有这个节点  会出错
			// Set SequenceMode="Off" 
			//status = J_Camera_SetValueString(m_hCam, (int8_t*)"SequenceMode", (int8_t*)"Off");
			//if(status != J_ST_SUCCESS) 
			//{
			//	ShowErrorMsg(CString("Could not set SequenceMode!"), status);
			//	return;
			//}
		}
		else
		{
			// Here we assume that this is JAI trigger so we do the following:
			// ExposureMode=EdgePreSelect
			// LineSelector=CameraTrigger0
			// LineSource=SoftwareTrigger0

			// Set ExposureMode="SequentialEPSTrigger"
			status = J_Camera_SetValueString(m_hCam, (int8_t*)"ExposureMode", (int8_t*)"EdgePreSelect");
			if(status != J_ST_SUCCESS) 
			{
				ShowErrorMsg(CString("Could not set ExposureMode!"), status);
				return;
			}

			// Set LineSelector="CameraTrigger0" 
			status = J_Camera_SetValueString(m_hCam, (int8_t*)"LineSelector", (int8_t*)"CameraTrigger0");
			if(status != J_ST_SUCCESS) 
			{
				ShowErrorMsg(CString("Could not set LineSelector!"), status);
				return;
			}

			// Set LineSource="SoftwareTrigger0" 
			status = J_Camera_SetValueString(m_hCam, (int8_t*)"LineSource", (int8_t*)"SoftwareTrigger0");
			if(status != J_ST_SUCCESS) 
			{
				ShowErrorMsg(CString("Could not set LineSource!"), status);
				return;
			}
		}


	} // end of if(m_hCamera)
}

void camera_jai::StreamCBFunc(J_tIMAGE_INFO * pAqImageInfo)
{


	img.create(cvSize(pAqImageInfo->iSizeX,pAqImageInfo->iSizeY), CV_8UC1);
	if(m_camIndex>=g_CamNum)  //保证g_CamBufs[m_camIndex]，g_CamAcqs[m_camIndex] 不越界
		return ;
	EnterCriticalSection(&g_CamBufs[m_camIndex]); 
	memcpy(img.data,pAqImageInfo->pImageBuffer,img.total());
	cv::Mat test =img;
	LeaveCriticalSection(&g_CamBufs[m_camIndex]); 
	SetEvent(g_CamAcqs[m_camIndex]);


	//CWnd *pWnd1=CWnd::FindWindow(NULL,_T(" 螺丝检测"));//获取目标窗口
	//if(::IsWindowEnabled( pWnd1->GetSafeHwnd()))
	//{
	//	if(pWnd1!=NULL) 
	//		pWnd1->PostMessageA(WM_DATA_READY,m_camIndex,0);
	//}

	//CWnd *pWnd2=CWnd::FindWindow(NULL,_T("灯型编辑"));//获取目标窗口
	//if(::IsWindowEnabled( pWnd2->GetSafeHwnd()))
	//{
	//	if(pWnd2!=NULL)
	//		pWnd2->PostMessageA(WM_DATA_READY,m_camIndex,0);
	//}

	//CWnd *pWnd3=CWnd::FindWindow(NULL,_T("模板编辑"));//获取目标窗口
	//if(::IsWindowEnabled( pWnd3->GetSafeHwnd()))
	//{
	//	if(pWnd3!=NULL)
	//		pWnd3->PostMessageA(WM_DATA_READY,m_camIndex,0);
	//}


}

void camera_jai::OnBnClickedSwtriggerbutton()
{
	J_STATUS_TYPE status = J_ST_SUCCESS;

	// We have two possible ways of software triggering: JAI or GenICam SFNC
	// The GenICam SFNC software trigger uses a node called "TriggerSoftware" and the JAI
	// uses nodes called "SoftwareTrigger0" to "SoftwareTrigger3".
	// Therefor we have to determine which way to use here.
	// First we see if a node called "TriggerSoftware" exists.
	NODE_HANDLE hNode = NULL;
	status = J_Camera_GetNodeByName(m_hCam, (int8_t*)"TriggerSoftware", &hNode);

	// Does the "TriggerSoftware" node exist?
	if ((status == J_ST_SUCCESS) && (hNode != NULL))
	{
		// Here we assume that this is GenICam SFNC software trigger so we do the following:
		// TriggerSelector=FrameStart
		// Execute TriggerSoftware Command
		status = J_Camera_SetValueString(m_hCam, (int8_t*)"TriggerSelector", (int8_t*)"FrameStart");
		if(status != J_ST_SUCCESS) 
		{
			ShowErrorMsg(CString("Could not set TriggerSelector!"), status);
			return;
		}
		status = J_Camera_ExecuteCommand(m_hCam, (int8_t*)"TriggerSoftware");
		if(status != J_ST_SUCCESS) 
		{
			ShowErrorMsg(CString("Could not set TriggerSoftware!"), status);
			return;
		}
	}
	else
	{
		// Here we assume that this is JAI software trigger so we do the following:
		// SoftwareTrigger0=1
		// SoftwareTrigger0=0

		status = J_Camera_SetValueInt64(m_hCam, (int8_t*)"SoftwareTrigger0", 1);
		if(status != J_ST_SUCCESS) 
		{
			ShowErrorMsg(CString("Could not set SoftwareTrigger0!"), status);
			return;
		}

		status = J_Camera_SetValueInt64(m_hCam, (int8_t*)"SoftwareTrigger0", 0);
		if(status != J_ST_SUCCESS) 
		{
			ShowErrorMsg(CString("Could not set SoftwareTrigger0!"), status);
			return;
		}
	}
}

void camera_jai::ShowErrorMsg(CString message, J_STATUS_TYPE error)
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

bool camera_jai::changeAcquitionModel(int trigSetting)
{
	m_TrigSetting = trigSetting;
	stopCapture();
	settingCamera();
	startCapture();

	return true;
}