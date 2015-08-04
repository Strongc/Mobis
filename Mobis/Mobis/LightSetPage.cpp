// LightSetPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mobis.h"
#include "LightSetPage.h"
#include "afxdialogex.h"


// LightSetPage dialog

IMPLEMENT_DYNAMIC(LightSetPage, CPropertyPage)

LightSetPage::LightSetPage()
	: CPropertyPage(LightSetPage::IDD)
{

}

LightSetPage::~LightSetPage()
{
}

void LightSetPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LightSetPage, CDialogEx)
END_MESSAGE_MAP()


// LightSetPage message handlers
