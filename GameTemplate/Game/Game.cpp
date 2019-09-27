#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include"BackGround.h"
#include "GameCamera.h"
#include"GameObjectManager.h"

Game::Game()
{
	
	
		m_player = g_goMgr.NewGO<Player>();
		m_background = g_goMgr.NewGO<BackGround>();
		m_gamecamera = g_goMgr.NewGO<GameCamera>();
	
}

Game::~Game()
{
	g_goMgr.DeleteGO(m_player);
	g_goMgr.DeleteGO(m_background);
	g_goMgr.DeleteGO(m_gamecamera);

	
}
void Game::Update()
{
	
}
void Game::Render()
{
	
}
