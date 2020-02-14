#include "stdafx.h"
#include "LittleEnemy.h"
#include"GameObjectManager.h"

LittleEnemy::LittleEnemy()
{
	m_skinModelRender =GameObjectManager::instance().NewGO<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/ModelData/LittleDragon_Blue.cmo");


}


LittleEnemy::~LittleEnemy()
{
	GameObjectManager::instance().DeleteGO(m_skinModelRender);

}

void LittleEnemy::Update()
{

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
}

void LittleEnemy::Render()
{
}
