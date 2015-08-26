#include "stdafx.h"
#include "PictureSave.h"


PictureSave::PictureSave(void)
{

	int warmspace =200;    //���̿ռ�С��200M ������
	int errospace = 50;	   //���̿ռ�С��50M ������
	m_ModelManage=NULL;
	UpdateParm();

	openConnection();
	//m_PicType=::GetPrivateProfileInt("���ݱ�������","ͼ���ʽ",0,".//setting.ini");
	//m_dateNum=::GetPrivateProfileInt("���ݱ�������","��������",100,".//setting.ini");
	//::GetPrivateProfileString("���ݱ�������","���ݱ���·��",".//data",m_dataPath.GetBuffer(MAX_PATH),MAX_PATH,".//setting.ini");
}

PictureSave::~PictureSave(void)
{
	closeConnection();
}



int PictureSave::savePic(cv::Mat img)
{
	int status = 1;
	CString strDate;
	CString strTime;
	getDateAndTime(strDate,strTime);
	status = savePic(img,strDate,strTime,0);

	return status;
}

int PictureSave::savePic(vector<cv::Mat> imgs)
{
	int status = 1;
	CString strDate;
	CString strTime;
	getDateAndTime(strDate,strTime);
	CString path = m_dataPath+strDate;

	for (int i = 0; i < imgs.size(); i++)
	{
		savePic(imgs[i],path,strTime,i);
	}
	return status;
}

int PictureSave::UpdateParm()
{
	m_PicType=::GetPrivateProfileInt("���ݱ�������","ͼ���ʽ",0,".//setting.ini");
	m_dateNum=::GetPrivateProfileInt("���ݱ�������","��������",100,".//setting.ini");
	::GetPrivateProfileString("���ݱ�������","���ݱ���·��",".//data",m_dataPath.GetBuffer(MAX_PATH),MAX_PATH,".//setting.ini");
	m_dataPath.ReleaseBuffer();
	return 1;
}

int PictureSave::UpdateModel(ModelManage  *p_ModelManage)
{
	if(p_ModelManage==NULL)
		return -1;
	m_ModelManage=p_ModelManage;
	return 1;

}

//˽�г�Ա����////////////////////////////////////////////////////////////////////////////////////////////

int PictureSave::savePic(cv::Mat saveimg,CString strDate,CString strTime ,int index)
{	
	int status = 1;

	if(saveimg.empty())				//���ͼ����Ч
	{	
		status = -1001;
		return status;
	}

	Mat img = saveimg;
	if(m_PicType==1&&m_ModelManage!=NULL)
	{
		translatePic(img,img);
	}

	CString strIndex;
	strIndex.Format("_%d_",index);

	CString dirName = strDate;
	CString fileName = strTime+strIndex+".jpg";
	CString path = strDate+"\\"+fileName;


	//��ȡ�������ڴ�����   **���뱣֤�����������ͬһ����
	TCHAR exeFullPath[MAX_PATH]; 
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);

	//����������
	double FreeSpace = GetFreeSpace_MB(drive);
	if(FreeSpace<warmspace)
	{
		if(FreeSpace<errospace)		//erro���������������  ɾ���ʼ������
		{
			status=-1;
			while(GetFreeSpace_MB(drive)<errospace)
			{ 
				CString date = getEarliestDate();
				deleteDbAndDir(date);
			}
		}
		else					//warm������������Ƚ�С��
		{
			status = -1000;  
		}

	}


	while(getPicDateNum()>m_dateNum)
	{ 
		CString date = getEarliestDate();
		deleteDbAndDir(date);
	}

	//  �ж�·���Ƿ����   
	if(!PathIsDirectory(dirName))   
	{   
		CreateDirectoryA(dirName,NULL);
	}   
	addPicToDbAndDir(img,fileName,dirName,path,"");

	return status;
}

void PictureSave::getDateAndTime(CString&date,CString&time)
{
	//��ȡʱ��
	SYSTEMTIME st;
	GetLocalTime(&st);

	CString strDate;
	CString strTime;
	strDate.Format("\\%4d-%2d-%2d",st.wYear,st.wMonth,st.wDay);
	strTime.Format("%2d_%2d_%2d_%3d",st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);

	date = strDate;
	time = strTime;
}


bool PictureSave::openDataBase()
{
	CoInitialize(NULL);
	if(!openConnection())
		return false;
	if(!openRecordset())
		return false;
	return true;

}

bool PictureSave::closeDataBase()
{
	if(!closeRecordset())
		return false;
	if(!closeConnection())
		return false;
	CoUninitialize();
	return true;
}

bool PictureSave::openConnection()
{
	// ��ʼ��COM,����ADO���ӵȲ���
	//if(AfxOleGetMessageFilter()   !=   NULL)
	//	AfxOleInit();


	CoInitialize(NULL);
	m_pConnection.CreateInstance(__uuidof(Connection));

	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	// ��Ϊ����ʱ�ᾭ������һЩ�벻���Ĵ���jingzhou xu
	try                 
	{	
		// �򿪱���Access��Demo.mdb
		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Demo.mdb","","",adModeUnknown);
	}
	catch(_com_error& e)
	{
		AfxMessageBox("��ȡ���ݿ�,����ADO����ʧ��!");///��ʾ������Ϣ
		return FALSE;
	}
	return true;
}

bool PictureSave::closeConnection()
{
	// �ر�ADO����״̬
	if(m_pConnection->State)
		m_pConnection->Close();
	m_pConnection= NULL;
	CoUninitialize();
	return true;
}

bool PictureSave::openRecordset()
{
	// ʹ��ADO�������ݿ��¼��
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	// ��Ϊ����ʱ�ᾭ������һЩ�벻���Ĵ���
	try
	{
		m_pRecordset->Open("SELECT * FROM  picture",                // ��ѯDemoTable���������ֶ�
			m_pConnection.GetInterfacePtr(),						 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error& e)
	{
		AfxMessageBox("��ȡ���ݿ�,�������ݿ��¼��ʧ��!");///��ʾ������Ϣ
		return FALSE;
	}

	//CString strSQL;
	//strSQL.Format(_T("SELECT COUNT(*) AS NUM FROM picture"));
	//try
	//{
	//	m_pRecordset->Open(strSQL.AllocSysString(), m_pConnection.GetInterfacePtr(),
	//		adOpenDynamic, adLockUnspecified, adCmdText);
	//}
	//catch (_com_error e)
	//{
	//	AfxMessageBox(_T("��ȡ����id�쳣"));
	//	return false;
	//}
	////��RecordSet�л�ȡ������Ŀ�͵�ǰ���ݿ�������ID��
	//int num = m_pRecordset->GetCollect("NUM");
	return true;
}

bool PictureSave::closeRecordset()
{
	if(m_pRecordset->State)
		m_pRecordset->Close();
	m_pRecordset = NULL;
	return true;
}



int PictureSave::getPicNum()
{

	//openConnection();
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	CString strSQL;
	strSQL.Format(_T("SELECT COUNT(*) AS NUM FROM picture"));
	try
	{
		m_pRecordset->Open(strSQL.AllocSysString(), m_pConnection.GetInterfacePtr(),
			adOpenDynamic, adLockUnspecified, adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("���ݿ��ȡ��ȡ�����쳣"));
		return false;
	}

	int num = m_pRecordset->GetCollect("NUM");
	closeRecordset();
	//closeConnection();

	return num;
}

int PictureSave::getPicDateNum()
{
	//openConnection();
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	CString strSQL;
	strSQL.Format(_T("Select Count(*) AS num from( select * from (select distinct dir from picture) )  "));
	try
	{
		m_pRecordset->Open(strSQL.AllocSysString(), m_pConnection.GetInterfacePtr(),
			adOpenDynamic, adLockUnspecified, adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("���ݿ��ȡ��ȡ�����쳣"));
		return false;
	}

	int num = m_pRecordset->GetCollect("NUM");

	closeRecordset();
	//closeConnection();

	return num;
}

bool PictureSave::FreeSpaceMoreThan(double mixSpace)
{
	_ULARGE_INTEGER freespace,totalspace,userspace;

	if(!::GetDiskFreeSpaceExA("d:",&userspace,&totalspace,&freespace))
	{
		AfxMessageBox("��ȡ���̿ռ�ʧ��");///��ʾ������Ϣ
		return false;	
	}
	double freespace_MB = freespace.QuadPart/1024.0/1024.0;
	if (freespace_MB<mixSpace)
	{
		return false;
	}
	return true;
}

double PictureSave::GetFreeSpace_MB(CString dir)
{
	_ULARGE_INTEGER freespace,totalspace,userspace;

	if(!::GetDiskFreeSpaceExA(dir,&userspace,&totalspace,&freespace))
	{
		AfxMessageBox("��ȡ���̿ռ�ʧ��");///��ʾ������Ϣ
		return false;	
	}
	double freespace_MB = freespace.QuadPart/1024.0/1024.0;
	return freespace_MB;
}


CString PictureSave::getEarliestDate()
{

	//openConnection();
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	CString strSQL;
	strSQL.Format(_T("SELECT TOP 1 * from picture"));
	try
	{
		m_pRecordset->Open(strSQL.AllocSysString(), m_pConnection.GetInterfacePtr(),
			adOpenDynamic, adLockUnspecified, adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("���ݿ�getEarliestDate�쳣"));
		return false;
	}


	CString dir;
	_variant_t var = m_pRecordset->GetCollect("dir");
	if(var.vt != VT_NULL)
		dir = (LPCSTR)_bstr_t(var);
	closeRecordset();
	//closeConnection();

	return dir;
}

int PictureSave::deleteDbAndDir(CString strDir)
{
	deleteDBdir(strDir);
	deleteDirectory(strDir);

	return 1;
}

bool PictureSave::deleteDBdir(CString strDir)
{

	//openConnection();
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	CString strSQL;
	strSQL.Format(_T("DELETE  from picture where dir = '%s'"),strDir);
	try
	{
		m_pRecordset->Open(strSQL.AllocSysString(), m_pConnection.GetInterfacePtr(),
			adOpenDynamic, adLockUnspecified, adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("���ݿ�deleteDBdir�쳣"));
		return false;
	}
	closeRecordset();
	//closeConnection();

	return 1;
}

void PictureSave::deleteDirectory(CString strDir)
{
	if(strDir.IsEmpty())   
	{ 
		RemoveDirectory(strDir); 
		return; 
	} 
	//����ɾ���ļ������ļ��� 
	CFileFind   ff; 
	BOOL bFound = ff.FindFile(strDir+ _T("\\*"),0); 
	while(bFound) 
	{ 
		bFound = ff.FindNextFile(); 
		if(ff.GetFileName()== _T(".")||ff.GetFileName()== _T("..")) 
			continue; 
		//ȥ���ļ�(��)ֻ�������� 
		SetFileAttributes(ff.GetFilePath(),FILE_ATTRIBUTE_NORMAL); 
		if(ff.IsDirectory())  
		{   
			//�ݹ�ɾ�����ļ��� 
			deleteDirectory(ff.GetFilePath()); 
			RemoveDirectory(ff.GetFilePath()); 
		} 
		else   
		{ 
			DeleteFile(ff.GetFilePath());   //ɾ���ļ� 
		} 
	} 
	ff.Close(); 
	//Ȼ��ɾ�����ļ��� 
	RemoveDirectory(strDir); 
}



int PictureSave::addPicToDbAndDir(Mat img,CString name,CString dir,CString path,CString addin)
{
	addPicToDB(name,dir,path,addin);
	addPicToDir(img,path);
	return 1;
}

bool PictureSave::addPicToDB(CString name,CString dir,CString path,CString addin)
{

	//openConnection();

	// ʹ��ADO�������ݿ��¼��
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	// ��Ϊ����ʱ�ᾭ������һЩ�벻���Ĵ���
	try
	{
		m_pRecordset->Open("SELECT * FROM  picture",                // ��ѯDemoTable���������ֶ�
			m_pConnection.GetInterfacePtr(),						 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error& e)
	{
		AfxMessageBox("��ȡ���ݿ�,��Ӽ�¼ʧ��!");///��ʾ������Ϣ
		return FALSE;
	}

	m_pRecordset->AddNew();
	m_pRecordset->PutCollect("name",_variant_t(name));
	m_pRecordset->PutCollect("dir",_variant_t(dir));
	m_pRecordset->PutCollect("path",_variant_t(path));
	m_pRecordset->PutCollect("add",_variant_t(addin));
	m_pRecordset->Update();

	closeRecordset();
	//closeConnection();
	return true;
}

int PictureSave::addPicToDir(Mat img ,CString path)
{
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	compression_params.push_back(50);
	imwrite(path.GetBuffer(0),img,compression_params);
	return 1;
}


int PictureSave::translatePic(Mat &LargeImg,Mat &SmallImg )
{
	vector<Mat>imgs;

	int modelNum = m_ModelManage->m_Models.size();
	for (int i = 0; i < modelNum; i++)
	{
		Mat roi(LargeImg,m_ModelManage->m_Models[i].Search_rect);
		imgs.push_back(roi);
	}
	All2One(imgs,SmallImg);

	return 1;
}

void PictureSave::All2One(vector<Mat> imgs,Mat &outimg)
{
	assert(!imgs.empty());
	int width =1000;
	int gap_h =15;
	int gap_v =15; 


	//��ȡimgs�����ĳ��Ϳ�
	int maxWidth=0;
	int maxHeight=0;
	for (int i = 0; i < imgs.size(); i++)
	{
		if (maxWidth<imgs[i].cols)
			maxWidth = imgs[i].cols;
		if(maxHeight<imgs[i].rows)
			maxHeight = imgs[i].rows;
	}

	//����õ������ж�����
	int colsNum = width/maxWidth;
	int rowsNum = (imgs.size()+colsNum-1)/colsNum;

	outimg.create(rowsNum*(maxHeight+gap_h),colsNum*(maxWidth+gap_v),imgs[0].type());
	for (int i = 0; i < imgs.size(); i++)
	{
		int x = i/colsNum;
		int y = i%colsNum;

		Mat roi(outimg,Rect(Point(y*(maxWidth+gap_v),x*(maxHeight+gap_h)),Size(maxWidth+gap_v,maxHeight+gap_h)));

		Mat roi2(roi,Rect(0,gap_h,imgs[i].cols,imgs[i].rows));


		//imgs[i].copyTo(roi);
		imgs[i].convertTo(roi2, roi2.type(), 1, 0);
	}




}