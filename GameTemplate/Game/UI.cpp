#include "stdafx.h"
#include "UI.h"
#include"Game.h"
#include"Player.h"
#include"Dragon.h"

UI::UI()
{
	for (int i = 0; i < UITypeNum; i++) {
		m_spriteRender[i] = GameObjectManager::instance().NewGO<SpriteRender>();
		m_spriteSca[i].Set(100.0f, 2.0f, 1.0f);
		m_spritePos[i].Set(CVector3::One());
		m_spriteRender[i]->SetPivot({ 0.0f,0.5f });
	}

	m_spritePos[HP].Set(-550.0f, 340.0f, 0.0f);
	m_spritePos[Stamina].Set(-550.0f, 300.0f, 0.0f);
	m_spritePos[Red].Set(-550.0f, 340.0f, 0.0f);
	

	m_spriteRender[HP]->Init(L"Assets/sprite/MH_HP.dds",10.0f,10.0f);
	
	m_spriteRender[Stamina]->Init(L"Assets/sprite/MH_stamina.dds", 10.0f, 10.0f);
	m_spriteRender[Clear]->Init(L"Assets/sprite/MH_QUESTCLEAR .dds", 20.0f, 300.0f);
	m_spriteRender[Clear]->SetIsActive(false);
	m_spriteRender[Clear]->SetPivot({ 0.5f,0.5f });
	m_spriteRender[Clear]->SetScale(CVector3::One());

	m_spriteRender[GameOver]->Init(L"Assets/sprite/MH_QUESTFAILED.dds", 20.0f, 300.0f);
	m_spriteRender[GameOver]->SetIsActive(false);
	m_spriteRender[GameOver]->SetPivot({ 0.5f,0.5f });
	m_spriteRender[GameOver]->SetScale(CVector3::One());

	m_spriteRender[Red]->Init(L"Assets/sprite/MH_Red.dds", 10.0f, 10.0f);
	m_spriteRender[Red]->SetIsActive(false);

	m_spriteRender[actionLine]->Init(L"Assets/sprite/001_line.dds", 10.0f, 10.0f);
	m_spriteRender[actionLine]->SetPivot({ 0.5f, 0.5f });
	m_spriteSca[actionLine].Set(1.0,1.0f,1.0f);
	m_spriteRender[actionLine]->SetAlpha(0.1f);
	m_spriteRender[actionLine]->SetIsActive(false);

	m_spriteRender[kaihukuyaku]->Init(L"Assets/sprite/HealingBottle02.dds", 80.0f, 80.0f);
	m_spriteRender[kaihukuyaku]->SetPivot({ 0.5f,0.5f });
	m_spriteRender[kaihukuyaku]->SetIsActive(true);
	m_spriteSca[kaihukuyaku].Set(2.0f,2.0f,0.1f);
	m_spritePos[kaihukuyaku].Set(400.0f, -200.0f, 1.0f);

	m_spriteRender[QuestPaper]->Init(L"Assets/sprite/QuestPaper.dds", 40.0f, 60.0f);
	m_spriteRender[QuestPaper]->SetPivot({ 0.5f,0.5f });
	m_spriteSca[QuestPaper].Set(10.0f, 10.0f, 1.0f);
	m_spriteRender[QuestPaper]->SetIsActive(false);
	
	AttackEvent = false;

}


UI::~UI()
{
	for (int i = 0; i < UITypeNum; i++) {
		GameObjectManager::instance().DeleteGO(m_spriteRender[i]);
	}
}
void UI::Update()
{
	
	auto m_game = Game::instance();
	if (m_game->m_dragon != nullptr&&m_game->GetStageNum()==3) {
		if (m_game->m_dragon->GetHitFlag())
		{
			AttackEvent = true;
		}
		if (AttackEvent) {
			m_spriteRender[actionLine]->SetIsActive(true);
			m_spriteSca[actionLine] *= 1.6f;
		}
	}
	if (m_spriteSca[actionLine].x >1280.0f)
	{
		m_spriteSca[actionLine].Set(CVector3::One());
		m_spriteRender[actionLine]->SetIsActive(false);
		AttackEvent = false;
	}
	
	if (m_game->m_player != nullptr) {
		hp = m_game->m_player->GetPlayerInformation().HP;
		float stamina = m_game->m_player->GetPlayerInformation().Stamina;
		if (hp < 30.0f)
		{
			m_spriteRender[HP]->SetIsActive(false);
			m_spriteRender[Red]->SetIsActive(true);
		}
		if (hp >= 30.0f) {
			m_spriteRender[HP]->SetIsActive(true);
			m_spriteRender[Red]->SetIsActive(false);
		}

		m_spriteSca[HP].x = hp;
		m_spriteSca[Stamina].x = stamina;
		m_spriteSca[Red].x = hp;
	}
	for (int i = 0; i < UITypeNum; i++)
	{
		m_spriteRender[i]->SetPosition(m_spritePos[i]);
		m_spriteRender[i]->SetScale(m_spriteSca[i]);
	}

	
}
void UI::ClearDraw()
{
	if (m_alpha < 1.0f) {
		m_alpha += 0.02f;
	}
	m_spriteRender[Clear]->SetIsActive(true);
	m_spriteRender[Clear]->SetAlpha(m_alpha);
}

void UI::GameOverDraw()
{
	if (m_alpha < 1.0f) {
		m_alpha += 0.02f;
	}
	m_spriteRender[GameOver]->SetIsActive(true);
	m_spriteRender[GameOver]->SetAlpha(m_alpha);
}

Item::Item()
{
	InitItem(&m_Item[kaihukuyaku], User_Item, 2, 10);
}

bool Item::UseItem(ItemType type)
{
	if (m_Item[type].num > 0)
	{
		m_Item[type].num--;
		return true;
	}
	else return false;
}
void Item::Update()
{

}
void Item::Render()
{

}