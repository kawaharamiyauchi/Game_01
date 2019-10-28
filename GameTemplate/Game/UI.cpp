#include "stdafx.h"
#include "UI.h"
#include"Game.h"
#include"Player.h"

UI::UI()
{
	for (int i = 0; i < 3; i++) {
		m_spriteRender[i] = g_goMgr.NewGO<SpriteRender>();
	}
	
	m_spritePos[0].Set(-550.0f, 340.0f, 0.0f);
	m_spriteSca[0].Set(110.0f,1.5f,1.0f );
	m_spritePos[1].Set(-600.0f, 100.0f, 0.0f);
	m_spriteSca[1].Set( 50.0f,1.0f,1.0f );
	m_spriteRender[0]->Init(L"Assets/sprite/MH_HP.dds",10.0f,10.0f);
	//m_spriteRender[0]->Init(L"Assets/sprite/ago_free_03.dds", 1280.0f, 720.0f);

	m_spriteRender[0]->SetPivot({ 0.0f,0.5f });
	m_spriteRender[1]->Init(L"MH_stamina.dds", 1.0f, 1.0f);
	m_spriteRender[1]->SetPivot({ 0.0f,0.5f });
	m_spriteRender[2]->Init(L"MH_Red.dds", 100.0f, 100.0f);


}


UI::~UI()
{
}
void UI::Update()
{
	auto m_game = Game::instance();
	m_game->m_player->GetPosition();
	m_spriteSca[1] *= 1.1f;

	for (int i = 0; i < 3; i++)
	{
		m_spriteRender[i]->SetPosition(m_spritePos[i]);
		m_spriteRender[i]->SetScale(m_spriteSca[i]);
	}
}

void UI::Render()
{
	
}