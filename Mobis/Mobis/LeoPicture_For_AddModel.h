//---------------------------------------------------------------------
#pragma once
#include"LeoPicture.h"
#include"opencv.hpp"
#include"LeoRectTracker.h"
#include"vector"
#include"Model.h"
#include"types.h"
//---------------------------------------------------------------------


class LeoPicture_For_AddModel : public LeoPicture
{
public:
	LeoPicture_For_AddModel();
	~LeoPicture_For_AddModel();

public:
	void Draw(CDC *pDC);
	void AddRelatedModel(Model mod);


	std::vector<Model>  models;
};

