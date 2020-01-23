#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
	
	
}


BackGround::~BackGround()
{
	for (int i = 0; i < ModelTypenum; i++) {
		if (m_skinModelRender[i] != nullptr) {
			GameObjectManager::instance().DeleteGO(m_skinModelRender[i]);
		}
	}

	//m_physicsStaticObject.~PhysicsStaticObject();
}

bool BackGround::Start()
{

	/*switch (m_stageType)
	{
	case(0):
		m_loadname = L"Assets/modelData/MH_0-0.cmo";
		break;
	case(1):
		m_loadname = L"Assets/modelData/Desert stage.cmo";
		break;
	default:
		break;
	}
	
	CQuaternion add;
	m_skinModelRender[MH_Ground] = GameObjectManager::instance().NewGO<SkinModelRender>();
	m_skinModelRender[MH_Sky] = GameObjectManager::instance().NewGO<SkinModelRender>();
	add.SetRotationDeg(CVector3::AxisX(), 90.0f);

	m_scale[1].Set(0.5f, 0.5f, 0.2f);
	m_skinModelRender[MH_Ground]->Init(m_loadname);
	

	m_skinModelRender[MH_Sky]->Init(L"Assets/modelData/MH_sky.cmo");
	m_skinModelRender[MH_Ground]->SetShadowCasterFlag(true);
	m_skinModelRender[MH_Ground]->SetShadowRecieverFlag(true);
	m_physicsStaticObject.CreateMeshObject(
	*m_skinModelRender[MH_Ground]->GetSkinModel(),
	m_position, m_rotation,
	a);*/
	return true;
}

void BackGround::LoadStage(int stagetype)
{
	switch (stagetype)
	{
	case(0):
		m_loadname = L"Assets/modelData/MH_0-0.cmo";
		break;
	case(1):
		m_loadname = L"Assets/modelData/Desert stage.cmo";
		break;
	default:
		break;
	}
	CQuaternion add;
	m_skinModelRender[MH_Ground] = GameObjectManager::instance().NewGO<SkinModelRender>();
	m_skinModelRender[MH_Sky] = GameObjectManager::instance().NewGO<SkinModelRender>();
	add.SetRotationDeg(CVector3::AxisX(), 90.0f);

	m_scale[1].Set(0.5f, 0.5f, 0.2f);
	m_skinModelRender[MH_Ground]->Init(m_loadname);

	m_skinModelRender[MH_Sky]->Init(L"Assets/modelData/MH_sky.cmo");
	m_skinModelRender[MH_Ground]->SetShadowCasterFlag(true);
	m_skinModelRender[MH_Ground]->SetShadowRecieverFlag(true);
	m_physicsStaticObject.CreateMeshObject(*m_skinModelRender[MH_Ground]->GetSkinModel(), m_position, m_rotation, a);
}

void BackGround::Update()
{
	
	for (int i = MH_Ground; i < ModelType::ModelTypenum; i++)
	{
		m_skinModelRender[i]->SetPosition(m_position);
		m_skinModelRender[i]->SetRotation(m_rotation);
		m_skinModelRender[i]->SetScale(m_scale[i]);
	}
	/*if (g_pad[0].IsPress(enButtonRB1))
	{
		m_skinModel[1].SetlightFlag(false);
	}
	if (g_pad[0].IsPress(enButtonLB1))
	{
		m_skinModel[1].SetlightFlag(true);
	}*/
}

void BackGround::Render()
{
	/*for (int i = 0; i < 2; i++) {
		m_skinModel[i].Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}*/
	
}