#pragma once
#include "character/CharacterController.h"

class Player
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
	void Draw();


private:
	float move_x = 0.0f;
	float move_z = 0.0f;
	Pad m_pad;
	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_position =CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale =CVector3::One();
};

