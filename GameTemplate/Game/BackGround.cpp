#include "stdafx.h"
#include "BackGround.h"
#include"GameObjectManager.h"

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
}



void BackGround::LoadStage(int stagetype)
{
	switch (stagetype)
	{
	case(0):
		m_loadname = L"Assets/modelData/MH_0-0.cmo";

		break;
	case(1):
		m_loadname = L"Assets/modelData/MH_Stage1-4.cmo";
		
		break;
	default:
		break;
	}
	CQuaternion add;
	for (int i = 0; i < ModelType::ModelTypenum; i++)
	{
		m_skinModelRender[i] = GameObjectManager::instance().NewGO<SkinModelRender>();
	}
	/*m_skinModelRender[MH_Ground] = GameObjectManager::instance().NewGO<SkinModelRender>();
	m_skinModelRender[MH_Sky] = GameObjectManager::instance().NewGO<SkinModelRender>();
	m_skinModelRender[MH_Limit] = GameObjectManager::instance().NewGO<SkinModelRender>();*/
	add.SetRotationDeg(CVector3::AxisX(), 90.0f);

	m_scale[MH_Sky].Set(1.0f,1.0f,0.4f);
	m_skinModelRender[MH_Ground]->Init(m_loadname);

	m_skinModelRender[MH_Sky]->Init(L"Assets/modelData/MH_sky.cmo");
	//m_skinModelRender[MH_Limit]->Init(L"Assets/modelData/Limit.cmo");
	m_skinModelRender[MH_Ground]->SetShadowCasterFlag(true);
	m_skinModelRender[MH_Ground]->SetShadowRecieverFlag(true);
	//m_scale[MH_Limit].Set(1.0f, 1.0f, 1.0f);
	m_physicsStaticObject.CreateMeshObject(*m_skinModelRender[MH_Ground]->GetSkinModel(), m_position, m_rotation, staticscale);
	//m_limit.CreateMeshObject(*m_skinModelRender[MH_Limit]->GetSkinModel(), m_position, CQuaternion::Identity(), CVector3::Zero());

}

void BackGround::Update()
{
	
	
	for (int i = 0; i < ModelType::ModelTypenum; i++)
	{
		m_skinModelRender[i]->SetPosition(m_position);
		m_skinModelRender[i]->SetRotation(m_rotation);
		m_skinModelRender[i]->SetScale(m_scale[i]);
	}
	
	
}

void BackGround::Render()
{
		
}