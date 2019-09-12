#pragma once
#include "IGameObject.h"
class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();

	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	CVector3 GetScale()
	{
		return m_scale;
	}

	void SetScale(CVector3 sca)
	{
		m_scale = sca;
	}



	void Update();

	void Render();
	
private:

	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One();
	CQuaternion m_rotation = CQuaternion::Identity();
	SkinModel m_skinModel;
	
};

