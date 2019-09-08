#include "stdafx.h"
#include "Player.h"
#include"GameObjectManager.h"

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
}


Player::~Player()
{
	
}

void Player::Update()
{
	
	
	
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