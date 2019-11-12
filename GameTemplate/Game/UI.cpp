#include "stdafx.h"
#include "UI.h"
#include"Game.h"
#include"Player.h"

UI::UI()
{
	for (int i = 0; i < 3; i++) {
		m_spriteRender[i] = g_goMgr.NewGO<SpriteRender>();
		m_spriteSca[i].Set(100.0f, 2.0f, 1.0f);
		m_spriteRender[i]->SetPivot({ 0.0f,0.5f });
	}
	m_spritePos[0].Set(-550.0f, 340.0f, 0.0f);
	m_spritePos[1].Set(-550.0f, 300.0f, 0.0f);
	m_spritePos[2].Set(-550.0f, 340.0f, 0.0f);
	m_spriteRender[0]->Init(L"Assets/sprite/MH_HP.dds",10.0f,10.0f);
		
	m_spriteRender[1]->Init(L"Assets/sprite/MH_stamina.dds", 10.0f, 10.0f);
	
	m_spriteRender[2]->Init(L"Assets/sprite/MH_Red.dds", 10.0f, 10.0f);

	m_spriteRender[2]->SetIsActive(false);

}


UI::~UI()
{
}
void UI::Update()
{
	auto m_game = Game::instance();
	float hp = m_game->m_player->GetPlayerInformation().HP;
	float stamina = m_game->m_player->GetPlayerInformation().Stamina;
	if (hp < 30.0f)
	{
		m_spriteRender[0]->SetIsActive(false);
		m_spriteRender[2]->SetIsActive(true);
	}
	if (hp >= 30.0f) {
		m_spriteRender[0]->SetIsActive(true);
		m_spriteRender[2]->SetIsActive(false);
	}

	m_spriteSca[0].x = hp;
	m_spriteSca[1].x = stamina;
	m_spriteSca[2].x = hp;
	for (int i = 0; i < 3; i++)
	{
		m_spriteRender[i]->SetPosition(m_spritePos[i]);
		m_spriteRender[i]->SetScale(m_spriteSca[i]);
	}
}
