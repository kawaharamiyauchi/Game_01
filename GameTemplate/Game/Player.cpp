#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include"GameObjectManager.h"
#include"HID/Pad.h"

Player::Player()
{
	m_charaCon.Init(
		10.0f,		//半径
		10.0f,		//高さ
		m_position	//初期座標
	);	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	
}


Player::~Player()
{


}

void Player::Move()
{
	

	float IStick_x = g_pad[0].GetLStickXF();
	float IStick_y = g_pad[0].GetLStickYF();

	CVector3 cameraForward = g_camera3D.GetFront();
	CVector3 cameraRight = g_camera3D.GetRight();

	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();

	m_speed.x = 0.0f;
	m_speed.z = 0.0f;
	m_speed.y -= 0.8f;

	m_speed += cameraForward * IStick_y*20.0f;
	m_speed += cameraRight * IStick_x*20.0f;



	if (g_pad[0].IsPress(enButtonY))
	{
		m_model.SetActiveFlag(false);
	}
	if (g_pad[0].IsPress(enButtonX))
	{
		m_model.SetActiveFlag(true);
	}
	if (g_pad[0].IsPress(enButtonB))
	{
		m_speed.y += 10.0f;
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
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	m_rotation.SetRotation(CVector3::AxisY(), angle);

	

}
void Player::Update()
{
	Move();
	Turn();
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

