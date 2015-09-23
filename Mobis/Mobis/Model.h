#ifndef MODEL_H
#define MODEL_H
#include <string>
#include<list>
#include"opencv.hpp"
using namespace std;
using namespace cv;

class Model
{
public:
	Model():m_Describe("defaut_Model_name"),m_cameraID(0),m_show_Search_rect(Rect(0,0,0,0)){};
	~Model(){};

	string getDescribe() const
	{
		return m_Describe;
	};
	int  getCameraID() const
	{
		return m_cameraID;
	};
	Rect getSearchrect() const
	{
		return m_show_Search_rect;
	}
	Mat  getDModel() const
	{
		return m_dModel;
	}
	Mat  getDModelMask() const
	{
		return m_dModel_Mask;
	}
	Rect getDModelRect() const
	{
		return m_dModel_rect;
	}
	Rect getDModelSearchRect() const
	{
		return m_dModel_SearchRect;
	}
	Mat  getDModel2() const
	{
		return m_dModel2;
	}
	Mat  getDModelMask2() const
	{
		return m_dModel_Mask2;
	}
	Rect getDModelRect2() const
	{
		return m_dModel_rect2;
	}
	Rect getDModelSearchRect2() const
	{
		return m_dModel_SearchRect2;
	}
	void setDescribe(string des)
	{
		m_Describe =des;
	};
	void setCameraID(int ID)
	{
		m_cameraID =ID;
	};
	void setSearchrect(Rect rect)
	{
		m_show_Search_rect = rect;
	}
	void setDModel(Mat model)
	{
		m_dModel = model;
	}
	void setDModelMask(Mat Mask)
	{
		m_dModel_Mask=Mask;
	}
	void setDModelRect(Rect rect)
	{
		m_dModel_rect= rect;
	}
	void setDModelSearchRect(Rect rect)
	{
		m_dModel_SearchRect = rect;
	}
	void setDModel2(Mat model)
	{
		m_dModel2 = model;
	}
	void setDModelMask2(Mat Mask)
	{
		m_dModel_Mask2=Mask;
	}
	void setDModelRect2(Rect rect)
	{
		m_dModel_rect2= rect;
	}
	void setDModelSearchRect2(Rect rect)
	{
		m_dModel_SearchRect2 = rect;
	}






	vector<Mat> getPModel_v()
	{
		return m_pModels;
	}
	vector<Rect> getPModelRects_v()
	{
		return m_pModels_Rects;
	}
	vector<Rect> getPModelSearchRects_v()
	{
		return m_pModels_SearchRects;
	}
	vector<Mat> getNModel_v()
	{
		return m_nModels;
	}
	vector<Rect> getNModelRects_v()
	{
		return m_nModels_Rects;
	}
	vector<Rect> getNModelSearchRects_v()
	{
		return m_nModels_SearchRects;
	}
	Mat  getPModel(int index)
	{
		assert(m_pModels.size()>index);
		vector<Mat>::iterator itor = m_pModels.begin()+index;
		return *itor;
	}
	Rect getPModelRects(int index)
	{
		assert(m_pModels_Rects.size()>index);
		vector<Rect>::iterator itor = m_pModels_Rects.begin()+index;
		return *itor;
	}
	Rect getPModelSearchRects(int index)
	{
		assert(m_pModels_SearchRects.size()>index);
		vector<Rect>::iterator itor = m_pModels_SearchRects.begin()+index;
		return *itor;
	}
	Mat  getNModel(int index)
	{
		assert(m_nModels.size()>index);
		vector<Mat>::iterator itor = m_nModels.begin()+index;
		return *itor;
	}
	Rect getNModelRects(int index)
	{
		assert(m_nModels_Rects.size()>index);
		vector<Rect>::iterator itor = m_nModels_Rects.begin()+index;
		return *itor;
	}
	Rect getNModelSearchRects(int index)
	{
		assert(m_nModels_SearchRects.size()>index);
		vector<Rect>::iterator itor = m_nModels_SearchRects.begin()+index;
		return *itor;
	}

	void setPModel(int index,Mat pModel)
	{
		assert(m_pModels.size()>index);
		vector<Mat>::iterator itor = m_pModels.begin()+index;
		*itor = pModel;
	}
	void setPModelRects(int index,Rect PModelRect )
	{
		assert(m_pModels_Rects.size()>index);
		vector<Rect>::iterator itor = m_pModels_Rects.begin()+index;
		 *itor =PModelRect ;
	}
	void setPModelSearchRects(int index,Rect PModelSearchRect )
	{
		assert(m_pModels_SearchRects.size()>index);
		vector<Rect>::iterator itor = m_pModels_SearchRects.begin()+index;
		*itor =PModelSearchRect;
	}
	void setNModel(int index,Mat NModel)
	{
		assert(m_nModels.size()>index);
		vector<Mat>::iterator itor = m_nModels.begin()+index;
		*itor = NModel;
	}
	void setNModelRects(int index,Rect NModelRect)
	{
		assert(m_nModels_Rects.size()>index);
		vector<Rect>::iterator itor = m_nModels_Rects.begin()+index;
		*itor = NModelRect;
	}
	void setNModelSearchRects(int index,Rect NModelSearchRect)
	{
		assert(m_nModels_SearchRects.size()>index);
		vector<Rect>::iterator itor = m_nModels_SearchRects.begin()+index;
		*itor = NModelSearchRect;
	}


	void addPModel(Mat img)
	{
		m_pModels.push_back(img);
	}
	void addPModelRects(Rect rect)
	{
		m_pModels_Rects.push_back(rect);
	}
	void addPModelSearchRects(Rect rect)
	{
		m_pModels_SearchRects.push_back(rect);
	}
	void addNModel(Mat img)
	{
		m_nModels.push_back(img);
	}
	void addNModelRects(Rect rect)
	{
		m_nModels_Rects.push_back(rect);
	}
	void addNModelSearchRects(Rect rect)
	{
		m_nModels_SearchRects.push_back(rect);
	}

	void minusPModel(int index)
	{
		assert(m_pModels.size()>index);
		vector<Mat>::iterator itor = m_pModels.begin()+index;
		m_pModels.erase(itor);
	}
	void minusPModelRects(int index)
	{
		assert(m_pModels_Rects.size()>index);
		vector<Rect>::iterator itor = m_pModels_Rects.begin()+index;
		m_pModels_Rects.erase(itor);
	}
	void minusPModelSearchRects(int index)
	{
		assert(m_pModels_SearchRects.size()>index);
		vector<Rect>::iterator itor = m_pModels_SearchRects.begin()+index;
		m_pModels_SearchRects.erase(itor);
	}
	void minusNModel(int index)
	{
		assert(m_nModels.size()>index);
		vector<Mat>::iterator itor = m_nModels.begin()+index;
		m_nModels.erase(itor);
	}
	void minusNModelRects(int index)
	{
		assert(m_nModels_Rects.size()>index);
		vector<Rect>::iterator itor = m_nModels_Rects.begin()+index;
		m_nModels_Rects.erase(itor);
	}
	void minusNModelSearchRects(int index)
	{
		assert(m_nModels_SearchRects.size()>index);
		vector<Rect>::iterator itor = m_nModels_SearchRects.begin()+index;
		m_nModels_SearchRects.erase(itor);
	}

	void writeModel (FileStorage& fs) const
	{
		//FileStorage fs(filename, FileStorage::WRITE);
		fs<<"{";
		fs<<"describe"<<getDescribe();
		fs<<"cameraID"<<getCameraID();
		fs<<"SearchRect"<<getSearchrect();

		fs<<"directModel"<<getDModel();
		fs<<"directModel_Mask"<<getDModelMask();
		fs<<"directModel_Rect"<<getDModelRect();
		fs<<"directModel_SearchRect"<<getDModelSearchRect();

		fs<<"directModel2"<<getDModel2();
		fs<<"directModel_Mask2"<<getDModelMask2();
		fs<<"directModel_Rect2"<<getDModelRect2();
		fs<<"directModel_SearchRect2"<<getDModelSearchRect2();



		int positive_num= m_pModels.size();
		int Nagetive_num= m_nModels.size();
		fs<<"positive_num"<<positive_num;
		fs<<"Nagetive_num"<<Nagetive_num;

		assert(m_pModels.size()==m_pModels_SearchRects.size());
		for(int i=0;i<positive_num;i++)
		{
			char name[30];
			sprintf(name,"positive_Image_%02d",i);	
			fs<<name<<m_pModels[i];

			sprintf(name,"positive_Rect_%02d",i);	
			fs<<name<<m_pModels_Rects[i];

			sprintf(name,"positive_SearchRect_%02d",i);	
			fs<<name<<m_pModels_SearchRects[i];
		}

		assert(m_nModels.size()==m_nModels_SearchRects.size());
		for(int i=0;i<Nagetive_num;i++)
		{
			char name[30];
			sprintf(name,"Nagetive_Image_%02d",i);	
			fs<<name<<m_nModels[i];

			sprintf(name,"Nagetive_Rect_%02d",i);	
			fs<<name<<m_nModels_Rects[i];

			sprintf(name,"Nagetive_SearchRect_%02d",i);	
			fs<<name<<m_nModels_SearchRects[i];
		}
		fs<<"}";
	}
	void readModel(const FileNode& node)
	{
		//FileStorage fs;
		//fs.open(filename, FileStorage::READ);
		string describe = (string)node["describe"];
		this->setDescribe(describe);   

		this->m_cameraID = (int) node["cameraID"];

		Rect SearchRect;
		node["SearchRect"]>>SearchRect;
		this->setSearchrect(SearchRect);



		Mat directModel;
		node["directModel"]>>directModel;
		this->setDModel(directModel);

		Mat directModel_Mask;
		node["directModel_Mask"]>>directModel_Mask;
		this->setDModelMask(directModel_Mask);

		Rect directModel_Rect;
		node["directModel_Rect"]>>directModel_Rect;
		this->setDModelRect(directModel_Rect);

		Rect directModel_SearchRect;
		node["directModel_SearchRect"]>>directModel_SearchRect;
		this->setDModelSearchRect(directModel_SearchRect);


		Mat directModel2;
		node["directModel2"]>>directModel2;
		this->setDModel2(directModel2);

		Mat directModel_Mask2;
		node["directModel_Mask2"]>>directModel_Mask2;
		this->setDModelMask2(directModel_Mask2);

		Rect directModel_Rect2;
		node["directModel_Rect2"]>>directModel_Rect2;
		this->setDModelRect2(directModel_Rect2);

		Rect directModel_SearchRect2;
		node["directModel_SearchRect2"]>>directModel_SearchRect2;
		this->setDModelSearchRect2(directModel_SearchRect2);




		int positive_num = (int) node["positive_num"];
		int Nagetive_num = (int) node["Nagetive_num"];

		for (int i = 0; i < positive_num; i++)
		{
			char name[30];
			sprintf(name,"positive_Image_%02d",i);
			Mat p ;
			node[name]>>p;
			this->addPModel(p);

			sprintf(name,"positive_Rect_%02d",i);
			Rect rect2 ;
			node[name]>>rect2;
			this->addPModelRects(rect2);


			sprintf(name,"positive_SearchRect_%02d",i);
			Rect rect ;
			node[name]>>rect;
			this->addPModelSearchRects(rect);
		}

		for (int i = 0; i < Nagetive_num; i++)
		{
			char name[30];
			sprintf(name,"Nagetive_Image_%02d",i);
			Mat p ;
			node[name]>>p;
			this->addNModel(p);

			sprintf(name,"Nagetive_Rect_%02d",i);
			Rect rect2 ;
			node[name]>>rect2;
			this->addNModelRects(rect2);

			sprintf(name,"Nagetive_SearchRect_%02d",i);
			Rect rect ;
			node[name]>>rect;
			this->addNModelSearchRects(rect);
		}
	}

private:
	string m_Describe;
	int m_cameraID;
	Rect m_show_Search_rect;

	Mat   m_dModel;
	Mat   m_dModel_Mask;
	Rect  m_dModel_rect;
	Rect  m_dModel_SearchRect;

	Mat   m_dModel2;
	Mat   m_dModel_Mask2;
	Rect  m_dModel_rect2;
	Rect  m_dModel_SearchRect2;


	vector<Mat>   m_pModels;
	vector<Rect>  m_pModels_Rects;
	vector<Rect>  m_pModels_SearchRects;

	vector<Mat>   m_nModels;
	vector<Rect>  m_nModels_Rects;
	vector<Rect>  m_nModels_SearchRects;
};
//These write and read functions must be defined for the serialization in FileStorage to work
static void write(FileStorage& fs, const std::string&,  const Model& x)
{
	x.writeModel(fs);
}
static void read(const FileNode& node, Model& x, const Model& default_value = Model())
{
	if(node.empty())
		x = default_value;
	else
		x.readModel(node);
}



class ModelManage
{
public:
	ModelManage():m_Describe("defaut_ModelManage_name"){};
	~ModelManage(){};
public:
	void Init(std::string str,int number)
	{
		m_Describe = str;
		m_Models.resize(number);
		for(int i=0;i<number;i++)
		{
			char name[50];
			sprintf(name,"position %d",i);
			m_Models[i].setDescribe(name);
		}
	}
	string getDescribe()
	{
		return m_Describe;
	};
	void setDescribe(string des)
	{
		m_Describe =des;
	};

	Model getModel(int index)
	{
		assert(m_Models.size()>index);
		vector<Model>::iterator itor = m_Models.begin()+index;
		return *itor;
	}
	void addOneModel(Model m)
	{
		m_Models.push_back(m);
	}
	void deleteOneModel(int index)
	{
		assert(m_Models.size()>index);
		vector<Model>::iterator itor = m_Models.begin()+index;
		m_Models.erase(itor);
	}
	void insertOneModel(Model m,int index)
	{
		assert(m_Models.size()>index);
		vector<Model>::iterator itor = m_Models.begin()+index;
		m_Models.insert(itor,m);
	}



	void writeModelManage (FileStorage& fs) const
	{
		fs<<"{";
		fs<<"str_Describe"<<m_Describe;
		int num = m_Models.size();
		fs<<"position_num"<<num;
		for(int i=0;i<num;i++)
		{
			char name[30];
			sprintf(name,"Model_%02d",i);
			fs<<name<<m_Models[i];
		}
		fs<<"Mat_Describe"<<img;
		fs<<"}";
	}
	void readModelManage(const FileNode& node)
	{
		string describe = (string)node["str_Describe"];
		this->setDescribe(describe);   
		int position_num = (int) node["position_num"];
		for (int i = 0; i < position_num; i++)
		{
			char name[30];
			sprintf(name,"Model_%02d",i);
			Model p ;
			node[name]>>p;
			this->addOneModel(p);
		}
		Mat image ;
		node["Mat_Describe"]>>image;
		this->img = image;
	}
public:
	std::string m_Describe;
	cv::Mat img;
	std::vector<Model> m_Models;

};
static void write(FileStorage& fs, const std::string&,  const ModelManage& x)
{
	x.writeModelManage(fs);
}
static void read(const FileNode& node, ModelManage& x, const ModelManage& default_value = ModelManage())
{
	if(node.empty())
		x = default_value;
	else
		x.readModelManage(node);
}

#endif