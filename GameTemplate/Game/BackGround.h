#pragma once
#include "IGameObject.h"
#include"character/CharacterController.h"
#include"physics/PhysicsStaticObject.h"

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

	SkinModel* GetskinModel()
	{
		return &m_skinModel[0];
	}

	void Update();

	void Render();
	
private:

	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale[2] = { CVector3::One() };
	CVector3 a = { 1000.0f,20.0f,1000.0f };
	CQuaternion m_rotation = { CQuaternion::Identity() };
	CQuaternion add_2;
	SkinModel m_skinModel[2];
	CharacterController m_charaCon;
	PhysicsStaticObject m_physicsStaticObject;
	
};

