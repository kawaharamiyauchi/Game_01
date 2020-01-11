#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include"BackGround.h"
#include "GameCamera.h"
#include"GameObjectManager.h"
#include"Dragon.h"
#include"Title.h"
#include"level/Level.h"

Game::Game()
{
	auto m_manager = &GameObjectManager::instance();
	m_gamecamera = m_manager->NewGO<GameCamera>();
	m_player = m_manager->NewGO<Player>();
	m_dragon = m_manager->NewGO<Dragon>();

	m_background = m_manager->NewGO<BackGround>();
	m_UI = m_manager->NewGO<UI>();
	/*m_gamecamera = GameObjectManager::instance().NewGO<GameCamera>();
	m_player = GameObjectManager::instance().NewGO<Player>();	
	m_background = GameObjectManager::instance().NewGO<BackGround>();
	m_dragon = GameObjectManager::instance().NewGO<Dragon>();
	m_UI = GameObjectManager::instance().NewGO<UI>();*/
		
}

Game::~Game()
{
	
	GameObjectManager::instance().DeleteGO(m_background);
	GameObjectManager::instance().DeleteGO(m_gamecamera);
	GameObjectManager::instance().DeleteGO(m_dragon);
	GameObjectManager::instance().DeleteGO(m_UI);
	GameObjectManager::instance().DeleteGO(m_player);
	
}
void Game::Update()
{
	if (m_player != nullptr) {
		GameObjectManager::instance().SetLightCameraPos(m_player->GetPosition());
	}
if (g_pad[0].IsTrigger(enButtonSelect))
	{

		GameObjectManager::instance().DeleteGO(this);
	}
}
void Game::Render()
{

}
