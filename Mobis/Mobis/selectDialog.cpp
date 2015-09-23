#include "stdafx.h"
#include "Mobis.h"
#include "afxdialogex.h"
#include "selectDialog.h"
#include "types.h"
#include "AddModelDlg.h"
IMPLEMENT_DYNAMIC(selectDialog, CDialogEx)

selectDialog::selectDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(selectDialog::IDD, pParent)
	, m_isCameraLock(TRUE)
{
	m_pos=-1;

	int ctrNum=2;
	m_zoomPics.resize(ctrNum);
	workPool_imgs.resize(ctrNum);
}

selectDialog::~selectDialog()
{

}

void selectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC1, m_zoomPics[0]);
	DDX_Control(pDX, IDC_PIC2, m_zoomPics[1]);
	DDX_Control(pDX, IDC_COMBO1, m_list_xinghao);
	DDX_Text(pDX, IDC_EDIT_XH_NAME, m_curren_name);
	DDX_Text(pDX, IDC_EDIT2, m_current_num);
	DDV_MinMaxInt(pDX, m_current_num, 0, 20);
	DDX_Control(pDX, IDC_LIST1, m_listctr);
	DDX_Check(pDX, IDC_CHECK_Lock, m_isCameraLock);
}

BOOL selectDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_curren_name=_T("");
	m_current_num=0;

	//初始化PictureControl控件///////////////////////
	for (int i = 0; i < m_zoomPics.size(); i++)
	{
		m_zoomPics[i].ID = i;
		m_zoomPics[i].UpdateImage(workPool_imgs[i]);  
	}


	//初始化工作区ModelManage变量
	if(!xinghaos->empty())
	{
		if (m_pos>0&&m_pos<xinghaos->size())
		{
			current_xh = (*xinghaos)[m_pos];
		}
		else
		{
			m_pos=0;
			current_xh = (*xinghaos)[m_pos];
		}
	}
	else 
	{
		m_pos= -1;
		current_xh.setDescribe("new");
	}


	//初始化listctl控件
	m_listctr.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	LONG lStyle;
	lStyle = GetWindowLong(m_listctr.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK;	//清除显示方式位
	lStyle |= LVS_REPORT;		//设置style
	SetWindowLong(m_listctr.m_hWnd, GWL_STYLE, lStyle);//设置style
	m_listctr.DeleteAllItems();//清空
	m_listctr.InsertColumn(0,_T("位置"));//添加列
	m_listctr.InsertColumn(1,_T("相机ID"));//添加列
	m_listctr.InsertColumn(2,_T("正模数"));
	m_listctr.InsertColumn(3,_T("负模数"));
	m_listctr.InsertColumn(4,_T("检测区域"));
	m_listctr.SetColumnWidth(0, 50);//设置列宽
	m_listctr.SetColumnWidth(1, 50);
	m_listctr.SetColumnWidth(2, 50);
	m_listctr.SetColumnWidth(3, 50);
	m_listctr.SetColumnWidth(4, 120);
	m_listctr.SetRedraw(FALSE);//防止重绘


	myUpdata(false);

	OnClickedCheckLock();
	return TRUE;
}

void selectDialog::myUpdata(bool direct)
{
	if(direct==false)
	{
		//更新型号列表框
		m_list_xinghao.ResetContent(); 
		for (int i = 0; i < xinghaos->size(); i++)
		{
			LPCTSTR str = (*xinghaos)[i].m_Describe.c_str(); 
			m_list_xinghao.AddString(str);
		}
		m_list_xinghao.SetCurSel(m_pos);


		//更新型号名称及螺钉数量编辑框
		m_curren_name = current_xh.m_Describe.c_str();
		m_current_num = current_xh.m_Models.size();
		UpdateData(false);
		//更新模型列表框
		m_listctr.DeleteAllItems();
		for (int i = 0; i < m_current_num; i++)
		{
			m_listctr.InsertItem(i,current_xh.m_Models[i].getDescribe().c_str());

			int CamId = current_xh.m_Models[i].getCameraID();
			int num1 = current_xh.m_Models[i].getPModel_v().size();
			int num2 = current_xh.m_Models[i].getNModel_v().size();
			cv::Rect rect = current_xh.m_Models[i].getDModelRect();
			CString str0;
			str0.Format("%d",CamId);
			CString str1;
			str1.Format("%d",num1);
			CString str2;
			str2.Format("%d",num2);
			CString str3;
			str3.Format("(%d,%d,%d,%d)",rect.x,rect.y,rect.width,rect.height);
			m_listctr.SetItemText(i,1,str0);
			m_listctr.SetItemText(i,2,str1);
			m_listctr.SetItemText(i,3,str2);
			m_listctr.SetItemText(i,4,str3);

		}

		m_listctr.SetRedraw(TRUE);	
	}
	else
	{
		current_xh.setDescribe(string(m_curren_name)); 
		UpdateData(true);
	}
}

BEGIN_MESSAGE_MAP(selectDialog, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &selectDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BT_ADD_POSITION, &selectDialog::OnBnClickedBtAddPosition)
	ON_BN_CLICKED(IDC_BT_DELETE_POSITION, &selectDialog::OnBnClickedBtDeletePosition)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &selectDialog::OnDblclkList1)
	ON_BN_CLICKED(IDC_SAVE, &selectDialog::OnBnClickedSave)
	ON_CBN_SELCHANGE(IDC_COMBO1, &selectDialog::OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_AddNew, &selectDialog::OnBnClickedAddnew)
	ON_BN_CLICKED(IDC_DeleteCurrent, &selectDialog::OnBnClickedDeletecurrent)
	ON_EN_CHANGE(IDC_EDIT_XH_NAME, &selectDialog::OnChangeEditXhName)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &selectDialog::OnClickList1)
	ON_MESSAGE(WM_DATA_READY,camera_buf_ready) 
	ON_BN_CLICKED(IDC_CHECK_Lock, &selectDialog::OnClickedCheckLock)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void selectDialog::OnPaint()
{
	//myUpdata(false);
	CDialogEx::OnPaint();
}

void selectDialog::OnBnClickedOk()
{
	int return_value_ID  = MessageBoxA("是否保存数据","保存对话框",MB_YESNOCANCEL);
	if(return_value_ID == IDYES)
	{
		OnBnClickedSave();
		CDialogEx::OnOK();
	}
	else if (return_value_ID == IDNO)
	{
		CDialogEx::OnOK();
	}
	else if (return_value_ID == IDCANCEL)
	{
		;
	}


}


//增加检测位置
void selectDialog::OnBnClickedBtAddPosition()
{
	Model model;
	int n = current_xh.m_Models.size();
	CString str1;
	str1.Format("%d",n+1);
	model.setDescribe(str1.GetBuffer(0));
	current_xh.addOneModel(model);
	myUpdata(false);
}

//删除某检测位置
void selectDialog::OnBnClickedBtDeletePosition()
{
	POSITION pos = m_listctr.GetFirstSelectedItemPosition();  
	if (pos == NULL)  
		TRACE0("No items were selected!\n");  
	else  
	{  
		int nItem = m_listctr.GetNextSelectedItem(pos);  
		current_xh.deleteOneModel(nItem);
	}
	myUpdata(false);
}

//编辑检测位置 的检测区域，及检测模板
void selectDialog::OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	if(pNMItemActivate->iItem == -1)
		return;

	//if(pNMItemActivate->iItem != -1)
	//{
	//	CString strtemp;
	//	strtemp.Format("单击的是第%d行第%d列",pNMItemActivate->iItem, pNMItemActivate->iSubItem);
	//	AfxMessageBox(strtemp);
	//}

	//POSITION pos = m_listctr.GetFirstSelectedItemPosition();
	//int tIndex = m_listctr.GetNextSelectedItem(pos);
	//if ( tIndex >= 0 )
	//{
	//	m_listctr.SetFocus();
	//	CEdit* pEdit = m_listctr.EditLabel( tIndex );
	//}

	//锁定相机，不跟新，否则会卡死
	m_isCameraLock= TRUE;
	UpdateData(FALSE);
	OnClickedCheckLock();


	addModel2 p_addModelDlg;
	p_addModelDlg.workPool_img = workPool_imgs[0];
	p_addModelDlg.workPool_img2 = workPool_imgs[1];
	int index = pNMItemActivate->iItem;
	p_addModelDlg.p_Model = &current_xh.m_Models[index];
	p_addModelDlg.DoModal();

	myUpdata(false);
}

void selectDialog::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	if(pNMItemActivate->iItem == -1)
		return;


	m_zoomPics[0].models.clear();
	m_zoomPics[1].models.clear();
	POSITION pos = m_listctr.GetFirstSelectedItemPosition();;
	int nIndex;
	while(pos)
	{
		nIndex = m_listctr.GetNextSelectedItem(pos);
		m_zoomPics[0].AddRelatedModel(current_xh.m_Models[nIndex]);
		m_zoomPics[1].AddRelatedModel(current_xh.m_Models[nIndex]);
	}

	m_zoomPics[0].Invalidate();
	m_zoomPics[1].Invalidate();
}

void selectDialog::OnBnClickedSave()
{

	if(m_pos>=0 &&m_pos<(*xinghaos).size())
		(*xinghaos)[m_pos] = current_xh;
	else if(m_pos==-1)
		xinghaos->push_back(current_xh);

	ModelManage Current;
	current_xh = Current;
	m_pos=-1;
	myUpdata(false);
}


void selectDialog::OnSelchangeCombo1()
{
	int pos = m_list_xinghao.GetCurSel();
	m_pos = pos;
	if(m_pos>=0 &&m_pos<(*xinghaos).size())
		current_xh = (*xinghaos)[m_pos];
	myUpdata(false);
}


void selectDialog::OnBnClickedAddnew()
{
	ModelManage Current;
	current_xh = Current;
	m_pos=-1;
	myUpdata(false);
}


void selectDialog::OnBnClickedDeletecurrent()
{
	if(m_pos>=0 &&m_pos<(*xinghaos).size())
	{
		vector<ModelManage>::iterator it=(*xinghaos).begin()+m_pos;
		(*xinghaos).erase(it);
	}
	ModelManage Current;
	current_xh = Current;
	m_pos=-1;
	myUpdata(false);
}


void selectDialog::OnChangeEditXhName()
{

	UpdateData(true);
	current_xh.setDescribe(m_curren_name.GetBuffer(0));

}


LRESULT selectDialog::camera_buf_ready(WPARAM wParam, LPARAM lParam)
{

	if(wParam==0)
	{
		Mat rgb_img;
		if(workPool_imgs[0].channels()==1)
			cvtColor(workPool_imgs[0],rgb_img,CV_GRAY2RGB);
		m_zoomPics[0].UpdateImage(rgb_img);

	}
	else if(wParam==1)
	{
		Mat rgb_img;
		if(workPool_imgs[1].channels()==1)
			cvtColor(workPool_imgs[1],rgb_img,CV_GRAY2RGB);
		m_zoomPics[1].UpdateImage(rgb_img);
	}
	return true;
}


void selectDialog::OnClickedCheckLock()
{
	UpdateData();
	if(m_isCameraLock)//相机锁定，图像不跟新
	{
		KillTimer(1);        //关闭定时器1。
	}
	else 
	{
		SetTimer(1,100,NULL);//启动定时器1,定时时间是1秒
	}
}

void selectDialog::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent) 
	{      
	case 1:    
		{  

			for (int i = 0; i < workPool_imgs.size(); i++)
			{
				Mat rgb_img;
				if(workPool_imgs[i].channels()==1)
					cvtColor(workPool_imgs[i],rgb_img,CV_GRAY2RGB);
				m_zoomPics[i].UpdateImage(rgb_img);

			}
			break; 
		}
	default:      
		break;      
	}      

	CDialogEx::OnTimer(nIDEvent);
}
