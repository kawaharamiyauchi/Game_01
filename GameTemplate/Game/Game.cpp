#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include"BackGround.h"
#include "GameCamera.h"
#include"GameObjectManager.h"
#include"Dragon.h"

Game::Game()
{
	
	
		m_player = g_goMgr.NewGO<Player>();
		m_dragon = g_goMgr.NewGO<Dragon>();		m_background = g_goMgr.NewGO<BackGround>();
		m_gamecamera = g_goMgr.NewGO<GameCamera>();
	
}

Game::~Game()
{
	g_goMgr.DeleteGO(m_player);
	g_goMgr.DeleteGO(m_background);
	g_goMgr.DeleteGO(m_gamecamera);
	g_goMgr.DeleteGO(m_dragon);
	
}
void Game::Update()
{
	
}
void Game::Render()
{
	
}
