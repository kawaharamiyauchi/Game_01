#include "stdafx.h"
#include "Player.h"
#include"GameObjectManager.h"
Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	
}


Player::~Player()
{
	Player*n = g_goMgr.NewGO<Player>();
}

void Player::Update()
{
	move_x = m_pad.GetLStickXF()*100.0f;
	move_z = m_pad.GetLStickYF()*100.0f;

	if (m_pad.IsPressAnyKey())
	{
		move_x = 1.0f;

	}
	m_position.x += move_x;
	m_position.z += move_z;
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