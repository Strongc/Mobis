#include "stdafx.h"
#include "PictureSave.h"


PictureSave::PictureSave(void)
{

	int warmspace =200;    //磁盘空间小于200M 将警告
	int errospace = 50;	   //磁盘空间小于50M 将出错
	m_ModelManage=NULL;
	UpdateParm();

	openConnection();
	//m_PicType=::GetPrivateProfileInt("数据保存设置","图像格式",0,".//setting.ini");
	//m_dateNum=::GetPrivateProfileInt("数据保存设置","保存天数",100,".//setting.ini");
	//::GetPrivateProfileString("数据保存设置","数据保存路径",".//data",m_dataPath.GetBuffer(MAX_PATH),MAX_PATH,".//setting.ini");
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
	m_PicType=::GetPrivateProfileInt("数据保存设置","图像格式",0,".//setting.ini");
	m_dateNum=::GetPrivateProfileInt("数据保存设置","保存天数",100,".//setting.ini");
	::GetPrivateProfileString("数据保存设置","数据保存路径",".//data",m_dataPath.GetBuffer(MAX_PATH),MAX_PATH,".//setting.ini");
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

//私有成员函数////////////////////////////////////////////////////////////////////////////////////////////

int PictureSave::savePic(cv::Mat saveimg,CString strDate,CString strTime ,int index)
{	
	int status = 1;

	if(saveimg.empty())				//检查图像有效
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


	//获取程序所在磁盘名   **必须保证程序和数据在同一磁盘
	TCHAR exeFullPath[MAX_PATH]; 
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(exeFullPath, drive, dir, NULL,NULL);

	//检测磁盘容量
	double FreeSpace = GetFreeSpace_MB(drive);
	if(FreeSpace<warmspace)
	{
		if(FreeSpace<errospace)		//erro错误磁盘容量不足  删除最开始的数据
		{
			status=-1;
			while(GetFreeSpace_MB(drive)<errospace)
			{ 
				CString date = getEarliestDate();
				deleteDbAndDir(date);
			}
		}
		else					//warm警告磁盘容量比较小了
		{
			status = -1000;  
		}

	}


	while(getPicDateNum()>m_dateNum)
	{ 
		CString date = getEarliestDate();
		deleteDbAndDir(date);
	}

	//  判断路径是否存在   
	if(!PathIsDirectory(dirName))   
	{   
		CreateDirectoryA(dirName,NULL);
	}   
	addPicToDbAndDir(img,fileName,dirName,path,"");

	return status;
}

void PictureSave::getDateAndTime(CString&date,CString&time)
{
	//获取时间
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
	// 初始化COM,创建ADO连接等操作
	//if(AfxOleGetMessageFilter()   !=   NULL)
	//	AfxOleInit();


	CoInitialize(NULL);
	m_pConnection.CreateInstance(__uuidof(Connection));

	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	// 因为它有时会经常出现一些想不到的错误。jingzhou xu
	try                 
	{	
		// 打开本地Access库Demo.mdb
		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Demo.mdb","","",adModeUnknown);
	}
	catch(_com_error& e)
	{
		AfxMessageBox("读取数据库,创建ADO连接失败!");///显示错误信息
		return FALSE;
	}
	return true;
}

bool PictureSave::closeConnection()
{
	// 关闭ADO连接状态
	if(m_pConnection->State)
		m_pConnection->Close();
	m_pConnection= NULL;
	CoUninitialize();
	return true;
}

bool PictureSave::openRecordset()
{
	// 使用ADO创建数据库记录集
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	// 因为它有时会经常出现一些想不到的错误。
	try
	{
		m_pRecordset->Open("SELECT * FROM  picture",                // 查询DemoTable表中所有字段
			m_pConnection.GetInterfacePtr(),						 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error& e)
	{
		AfxMessageBox("读取数据库,创建数据库记录集失败!");///显示错误信息
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
	//	AfxMessageBox(_T("读取最大的id异常"));
	//	return false;
	//}
	////从RecordSet中获取数据数目和当前数据库中最大的ID。
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
		AfxMessageBox(_T("数据库读取存取总数异常"));
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
		AfxMessageBox(_T("数据库读取存取总数异常"));
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
		AfxMessageBox("获取磁盘空间失败");///显示错误信息
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
		AfxMessageBox("获取磁盘空间失败");///显示错误信息
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
		AfxMessageBox(_T("数据库getEarliestDate异常"));
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
		AfxMessageBox(_T("数据库deleteDBdir异常"));
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
	//首先删除文件及子文件夹 
	CFileFind   ff; 
	BOOL bFound = ff.FindFile(strDir+ _T("\\*"),0); 
	while(bFound) 
	{ 
		bFound = ff.FindNextFile(); 
		if(ff.GetFileName()== _T(".")||ff.GetFileName()== _T("..")) 
			continue; 
		//去掉文件(夹)只读等属性 
		SetFileAttributes(ff.GetFilePath(),FILE_ATTRIBUTE_NORMAL); 
		if(ff.IsDirectory())  
		{   
			//递归删除子文件夹 
			deleteDirectory(ff.GetFilePath()); 
			RemoveDirectory(ff.GetFilePath()); 
		} 
		else   
		{ 
			DeleteFile(ff.GetFilePath());   //删除文件 
		} 
	} 
	ff.Close(); 
	//然后删除该文件夹 
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

	// 使用ADO创建数据库记录集
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	// 因为它有时会经常出现一些想不到的错误。
	try
	{
		m_pRecordset->Open("SELECT * FROM  picture",                // 查询DemoTable表中所有字段
			m_pConnection.GetInterfacePtr(),						 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error& e)
	{
		AfxMessageBox("读取数据库,添加记录失败!");///显示错误信息
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


	//获取imgs中最大的长和宽
	int maxWidth=0;
	int maxHeight=0;
	for (int i = 0; i < imgs.size(); i++)
	{
		if (maxWidth<imgs[i].cols)
			maxWidth = imgs[i].cols;
		if(maxHeight<imgs[i].rows)
			maxHeight = imgs[i].rows;
	}

	//计算得到多少行多少列
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