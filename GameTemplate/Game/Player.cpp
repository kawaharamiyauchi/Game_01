#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
}


Player::~Player()
{
}

void Player::Update()
{
	
	move_x = m_pad.GetLStickXF() ;
	move_z = m_pad.GetLStickYF();
	m_position.x += move_x;
	m_position.z += move_z;
	
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position,m_rotation,m_scale);

	

}
void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}