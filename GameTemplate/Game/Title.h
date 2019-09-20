#pragma once
#include"IGameObject.h"
class Title:public IGameObject
{
public:
	Title();
	~Title();
	void UpDate();
	void Render();
};

