#include "stdafx.h"
#include "Player.h"
#include"GameObjectManager.h"
#include"HID/Pad.h"
Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	
}


Player::~Player()
{


}

void Player::Move()
{

	move_x = g_pad[0].GetLStickXF()*2.0f;
	move_z = g_pad[0].GetLStickYF()*2.0f;

	if (g_pad[0].IsPress(enButtonB))
	{
		m_model.SetActiveFlag(false);
	}
	if (g_pad[0].IsPress(enButtonA))
	{
		m_model.SetActiveFlag(true);
	}
	m_position.x += move_x;
	m_position.z += move_z;

}

void Player::Update()
{
	Move();
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position,m_rotation,m_scale);
}
void Player::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
	
}

