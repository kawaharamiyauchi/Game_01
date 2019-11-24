#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
	
	CQuaternion add;
	
	add.SetRotationDeg(CVector3::AxisX(), 90.0f);

	m_scale[1].Set(0.5f, 0.5f, 0.2f);
	//m_rotation.Add(add);
	
	//m_skinModel[0].Init(L"Assets/modelData/testbox.cmo");
	m_skinModel[0].Init(L"Assets/modelData/Desert stage.cmo");
	m_skinModel[1].Init(L"Assets/modelData/MH_sky.cmo");
	
	m_physicsStaticObject.CreateMeshObject(m_skinModel[0], m_position, m_rotation,a);
	
}


BackGround::~BackGround()
{
	
}

void BackGround::Update()
{
	
	m_skinModel[0].UpdateWorldMatrix(m_position, m_rotation, m_scale[0]);
	m_skinModel[1].UpdateWorldMatrix(m_position, m_rotation, m_scale[1]);

	if (g_pad[0].IsPress(enButtonRB1))
	{
		m_skinModel[1].SetlightFlag(false);
	}
	if (g_pad[0].IsPress(enButtonLB1))
	{
		m_skinModel[1].SetlightFlag(true);
	}
}

void BackGround::Render()
{
	for (int i = 0; i < 2; i++) {
		m_skinModel[i].Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
	
}