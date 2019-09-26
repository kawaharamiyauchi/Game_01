#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include"GameObjectManager.h"
#include"HID/Pad.h"

Player::Player()
{
	m_charaCon.Init(
		20.0f,		//���a
		68.0f,		//����
		m_position	//�������W
	);	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	
}


Player::~Player()
{


}

void Player::Move()
{
	

	m_speed.x = g_pad[0].GetLStickXF()*20.0f;
	m_speed.z = g_pad[0].GetLStickYF()*20.0f;

	//CVector3 cameraForward =g_camera3D.

	if (g_pad[0].IsPress(enButtonB))
	{
		m_model.SetActiveFlag(false);
	}
	if (g_pad[0].IsPress(enButtonA))
	{
		m_model.SetActiveFlag(true);
	}
	m_position =m_charaCon.Execute(1.0f,m_speed);

}
void Player::Turn()
{
	if (fabsf(m_speed.x) < 0.001f
		&& fabsf(m_speed.z) < 0.001f) {
		
		return;
	}
	float angle = atan2(m_speed.x, m_speed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rotation.SetRotation(CVector3::AxisY(), angle);

	

}
void Player::Update()
{
	Move();
	Turn();
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position,m_rotation,m_scale);
}
void Player::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
	
}

