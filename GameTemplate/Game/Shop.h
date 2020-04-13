#pragma once
#include "IGameObject.h"
#include "SkinModelRender.h"
class Shop:public IGameObject
{
public:
	Shop();
	~Shop();
private:
	SkinModelRender *m_skinModelRender[2] = { nullptr };

	struct shopUI{


	};
};

