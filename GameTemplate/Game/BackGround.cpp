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
	m_stageType = stagetype;
	switch (stagetype)
	{
	case(0):
		m_loadname = L"Assets/modelData/MH_0-0.cmo";
		break;
	case(1):
		
		m_loadname = L"Assets/modelData/MH_Stage1-2.cmo";
		break;
	case(2):
		m_loadname = L"Assets/modelData/MH_Stage1-3.cmo";
		break;
	case(3):
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

	m_scale[MH_Sky].Set(2.0f,2.0f,1.0f);
	m_skinModelRender[MH_Ground]->Init(m_loadname);

	m_skinModelRender[MH_Sky]->Init(L"Assets/modelData/MH_sky.cmo");
	m_skinModelRender[MH_Ground]->SetShadowCasterFlag(true);
	m_skinModelRender[MH_Ground]->SetShadowRecieverFlag(true);
	m_skinModelRender[MH_Limit]->Init(L"Assets/modelData/Limit.cmo");
	m_skinModelRender[MH_Limit]->SetActiveFlag(true);
	//m_skinModelRender[QuestBoard]->Init(L"Assets/modelData/QuestBoard.cmo");
	//m_skinModelRender[QuestBoard]->SetActiveFlag(false);
	m_scale[MH_Limit].Set(100.0f, 100.0f, 100.0f);
	//m_scale[QuestBoard].Set(CVector3::One());
	m_physicsStaticObject.CreateMeshObject(*m_skinModelRender[MH_Ground]->GetSkinModel(), m_position, m_rotation, staticscale);
	if (m_stageType == 3) {
		PhysicsStaticObject m_limit;
		m_limit.CreateMeshObject(*m_skinModelRender[MH_Limit]->GetSkinModel(), m_position, m_rotation, staticscale);
	}
	/*if (m_stageType == 0)
	{
		m_skinModelRender[QuestBoard]->SetActiveFlag(true);
		PhysicsStaticObject m_board;
		m_board.CreateMeshObject(*m_skinModelRender[MH_Limit]->GetSkinModel(), m_position, m_rotation, CVector3::One());
	}*/
	//m_limit.CreateMeshObject(*m_skinModelRender[MH_Limit]->GetSkinModel(), m_position, CQuaternion::Identity(), CVector3::Zero());



	//m_skinModelRender[0]->SetActiveFlag(false);
	//m_skinModelRender[1]->SetActiveFlag(false);

}

void BackGround::Update()
{
	
	
	for (int i = 0; i < ModelType::ModelTypenum; i++)
	{
		m_skinModelRender[i]->SetPosition(m_position);
		m_skinModelRender[i]->SetRotation(m_rotation);
		m_skinModelRender[i]->SetScale(m_scale[i]);
	}
	if (m_stageType != 3)
	{
		m_skinModelRender[MH_Limit]->SetScale(CVector3::Zero());
	}
	
}

void BackGround::Render()
{
		
}