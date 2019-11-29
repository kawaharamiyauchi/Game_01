#include "stdafx.h"
#include "Title.h"
#include"Game.h"
#include "SpriteRender.h"

Title::Title()
{
	//m_sprite.Init(L"Assets/sprite/ago_free_03.dds", 1280.0f, 720.0f);
	m_position.Set(-640.0f, 0.0f, 0.0f);
	m_spriteRender = GameObjectManager::instance().NewGO<SpriteRender>();
	m_spriteRender->Init(L"Assets/sprite/MH_HP.dds", 1280.0f, 720.0f);
}


Title::~Title()
{
	GameObjectManager::instance().DeleteGO(m_spriteRender);
}

void Title::Update()
{
	
	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_spriteRender->SetPosition(m_position);
	m_spriteRender->SetPivot({	0.0f,0.5f });
	m_spriteRender->SetScale(m_scale);
	
	
	if (g_pad[0].IsPress(enButtonStart))
	{
		//m_spriteRender->SetIsActive(false);
		auto m_game = Game::instance();
		
		GameObjectManager::instance().DeleteGO(this);
		
		
	}

}
void Title::Render()
{
	
}