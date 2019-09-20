#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
	CQuaternion add;
	add.SetRotationDeg(CVector3::AxisX(), 90.0f);
	m_rotation.Add(add);
	m_skinModel.Init(L"Assets/modelData/Desert stage.cmo");
	m_scale = { 100.0f,10.0f,100.0f };
	
	//m_scale.y = 1.0f;
}


BackGround::~BackGround()
{
}

void BackGround::Update()
{
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void BackGround::Render()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}