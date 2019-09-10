#pragma once
#include "character/CharacterController.h"
#include"IGameObject.h"
class Player:public IGameObject
{
public:
	Player();
	~Player();

	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	void Update();
	void Render();


private:
	float move_x = 0.0f;
	float move_z = 0.0f;
	Pad m_pad;
	CMatrix m;
	SkinModel m_model;									//スキンモデル。
	CVector3 m_position =CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale =CVector3::One();
};

