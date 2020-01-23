#include "stdafx.h"
#include "Title.h"
#include"Game.h"
#include "SpriteRender.h"

Title::Title()
{
	StartFlag = true;
	ExitFlag = false;
	//m_sprite.Init(L"Assets/sprite/ago_free_03.dds", 1280.0f, 720.0f);
	for (int i = 0; i < Typenum; i++)
	{
		m_position[i].Set(-400.0f, 0.0f, 0.0f);

	}
	for (int i = 0; i < Typenum; i++)
	{
		m_spriteRender[i] = GameObjectManager::instance().NewGO<SpriteRender>();
	}
	m_spriteRender[Menu]->Init(L"Assets/sprite/MH_menu.dds", 400.0f, 100.0f);
	m_spriteRender[GameStart_Grey]->Init(L"Assets/sprite/MH_GameStart_Grey.dds", 400.0f, 100.0f);
	m_spriteRender[GameStart_Yellow]->Init(L"Assets/sprite/MH_GameStart_Yellow.dds", 400.0f, 100.0f);
	m_spriteRender[Exit_Grey]->Init(L"Assets/sprite/MH_Exit_Grey.dds", 600.0f, 100.0f);
	m_spriteRender[Exit_Yellow]->Init(L"Assets/sprite/MH_Exit_Yellow.dds", 600.0f, 100.0f);
	m_spriteRender[Triangle]->Init(L"Assets/sprite/Triangle.dds", 200.0f, 200.0f);
	m_spriteRender[GameStart_Grey]->SetIsActive(false);
	m_spriteRender[GameStart_Yellow]->SetIsActive(true);
	m_position[Menu].y += 200.0f;
	m_position[Exit_Grey].y -= 200.0f;
	m_position[Exit_Yellow].y -= 200.0f;
	m_position[Triangle].x -= 200.0f;
	/*m_spriteRender[1] = GameObjectManager::instance().NewGO<SpriteRender>();
	m_spriteRender[1]->SetAlpha(0.5f);
	m_spriteRender[1]->Init(L"Assets/sprite/MH_Red.dds", 1280.0f, 720.0f);*/
}


Title::~Title()
{
	for (int i = 0; i < Typenum; i++)
	{
		GameObjectManager::instance().DeleteGO(m_spriteRender[i]);
	}
}

void Title::Update()
{
	if (g_pad[0].IsTrigger(enButtonDown) && !ExitFlag)
	{
		StartFlag = false;
		ExitFlag = true;

		m_position[Triangle].y -= 200.0f;

	}
	else if (g_pad[0].IsTrigger(enButtonUp) && !StartFlag)
	{
		StartFlag = true;
		
		ExitFlag = false;
		
		m_position[Triangle].y += 200.0f;

	}
	//m_spriteRender->SetAlpha(0.5f);
	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_spriteRender[GameStart_Yellow]->SetIsActive(StartFlag);
	m_spriteRender[GameStart_Grey]->SetIsActive(!StartFlag);
	m_spriteRender[Exit_Grey]->SetIsActive(!ExitFlag);
	m_spriteRender[Exit_Yellow]->SetIsActive(ExitFlag);
	for (int i = 0; i < Typenum; i++)
	{
		m_spriteRender[i]->SetPosition(m_position[i]);
		m_spriteRender[i]->SetPivot({ 0.0f,0.5f });
		m_spriteRender[i]->SetScale(m_scale);
	}
	
	
	
	
	if (g_pad[0].IsPress(enButtonA))
	{
		if (StartFlag)
		{
			auto m_game = Game::instance();
			GameObjectManager::instance().CountPlus();
			if (GameObjectManager::instance().GetGameCount() > 1) {
				m_game->LoadGame(0);
			}
			GameObjectManager::instance().DeleteGO(this);
		}
		else if (ExitFlag)
		{
			exit(0);
		}


	}
}
void Title::Render()
{
	
}