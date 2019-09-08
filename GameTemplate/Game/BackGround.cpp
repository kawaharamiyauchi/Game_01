#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
	m_skinModel->Init(L"Assets/modelData/unityChan.cmo");
}


BackGround::~BackGround()
{
}

void BackGround::Update()
{
	m_skinModel->UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void BackGround::Render()
{
	m_skinModel->Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}