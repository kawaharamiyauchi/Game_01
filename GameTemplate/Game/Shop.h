#pragma once
#include "IGameObject.h"
#include"GhostObject.h"
#include"UI.h"

class Shop:public IGameObject
{
public:
	Shop();
	~Shop();

	void Update();
	bool Start();

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
private:

	struct shopUI{


	};
	enum ShopModelType
	{
		BUY,
		SELL,
		TypeNum

	};
	enum SoundType
	{
		move,
		select
	};

	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One();
	CQuaternion m_rotation = CQuaternion::Identity();
	SkinModelRender * m_skinModelRender[TypeNum] = { nullptr };
	GhostObject m_ghostObject;
	CSoundSource m_soundSource;


};

