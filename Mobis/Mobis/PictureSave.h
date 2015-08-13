#pragma once
#include"opencv.hpp"
#include<vector>
#include"Model.h"
using namespace cv;
using namespace std;




class PictureSave
{
public:
	PictureSave(void);
	~PictureSave(void);

	int UpdateParm();
	int UpdateModel(ModelManage  *p_ModelManage);
	int savePic(vector<cv::Mat> imgs);
	int savePic(cv::Mat img);
	
private:
	int savePic(cv::Mat img,CString strDate,CString strTime,int index);
	void getDateAndTime(CString&date,CString&time);


	bool openDataBase();
	bool closeDataBase();
	bool openConnection();
	bool closeConnection();
	bool openRecordset();
	bool closeRecordset();

	//添加数据
	int addPicToDbAndDir(Mat img,CString name,CString dir,CString path,CString addin);
	bool addPicToDB(CString name,CString dir,CString path,CString addin);
	int addPicToDir(Mat img ,CString path);

	//查询
	int getPicNum();					  //获取数据库保存图像总数
	int getPicDateNum();				  //获取数据库保存图像天数
	double GetFreeSpace_MB(CString dir);  //获取某磁盘可用空间
	bool FreeSpaceMoreThan(double mixSpace);//检查剩余空间大于mixSpace 单位MB

	//删除数据
	CString getEarliestDate();
	int deleteDbAndDir(CString strDir);
	bool deleteDBdir(CString strDir);
	void deleteDirectory(CString strDir);

	//全局大图转局部小图  缩小存储容量
	int translatePic(Mat &LargeImg,Mat &SmallImg );
	void All2One(vector<Mat> imgs,Mat &outimg);


	_ConnectionPtr	m_pConnection;
	_RecordsetPtr	m_pRecordset;

	ModelManage  *m_ModelManage;
	int m_PicType;
	int m_dateNum;
public:
	CString m_dataPath;
	int warmspace ;  //磁盘空间小于200M 将警告
	int errospace ;	//磁盘空间小于50M 将出错
};

