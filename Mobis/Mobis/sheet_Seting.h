#pragma once
#include "afxdlgs.h"
#include"sheet_CameraSetPage.h"
#include"sheet_DatabaseSetPage.h"
#include"sheet_LightSetPage.h"
#include"MobisDlg.h"


class sheet_Seting :public CPropertySheet
{
public:
	sheet_Seting(void);
	sheet_Seting(CMobisDlg* pMaindata);
	~sheet_Seting(void);

	 BOOL OnInitDialog(); 
public:
	sheet_CameraSetPage   m_CameraSetPage;
	sheet_DatabaseSetPage m_DatabaseSetPage;
	sheet_LightSetPage    m_LightSetPage;

	
};

