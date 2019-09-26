#pragma once
#include "IGameObject.h"
#include"character/CharacterController.h"
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

	/*CVector3 GetScale(int i)
	{
		return m_scale;
	}

	void SetScale(int i,CVector3 sca)
	{
		m_scale = sca;
	}*/



	void Update();

	void Render();
	
private:

	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale[2] = { CVector3::One() };
	CQuaternion m_rotation = { CQuaternion::Identity() };
	CQuaternion add_2;
	SkinModel m_skinModel[2];
	CharacterController m_charaCon;
	
};

