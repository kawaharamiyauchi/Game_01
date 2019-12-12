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
	//カメラを設定。
	//g_camera3D.SetPosition({ 0.0f, 1000.0f, 2200.0f });
	//g_camera3D.SetTarget({ 0.0f, 200.0f, 0.0f });
	//g_camera3D.Update();

	/*m_bgModelDraw.Init(L"Assets/modelData/Desert stage.cmo");
	m_unityChanModelDraw.Init(L"Assets/modelData/unityChan.cmo");

	m_bgModelDraw.SetShadowReciever(true);*/
	m_gamecamera = GameObjectManager::instance().NewGO<GameCamera>();
		m_player = GameObjectManager::instance().NewGO<Player>();
		
		m_background = GameObjectManager::instance().NewGO<BackGround>();
	  m_dragon = GameObjectManager::instance().NewGO<Dragon>();
		
		
		m_UI = GameObjectManager::instance().NewGO<UI>();
		
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
//	//g_graphicsEngine->BegineRender();
//
//	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
//	//現在のレンダリングターゲットをバックアップしておく。
//	ID3D11RenderTargetView* oldRenderTargetView;
//	ID3D11DepthStencilView* oldDepthStencilView;
//	d3dDeviceContext->OMGetRenderTargets(
//		1,
//		&oldRenderTargetView,
//		&oldDepthStencilView
//	);
//	//ビューポートもバックアップを取っておく。
//	unsigned int numViewport = 1;
//	D3D11_VIEWPORT oldViewports;
//	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);
//
//	//シャドウマップにレンダリング
//	m_shadowMap.RenderToShadowMap();
//	//元に戻す。
//	d3dDeviceContext->OMSetRenderTargets(
//		1,
//		&oldRenderTargetView,
//		oldDepthStencilView
//	);
//	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
//	//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
//	oldRenderTargetView->Release();
//	oldDepthStencilView->Release();
//
//	///////////////////////////////////////////////
//	//ここから通常レンダリング。
//	///////////////////////////////////////////////
//	m_bgModelDraw.Draw(
//		enRenderMode_Normal,
//		g_camera3D.GetViewMatrix(),
//		g_camera3D.GetProjectionMatrix()
//	);
//	m_unityChanModelDraw.Draw(
//		enRenderMode_Normal,
//		g_camera3D.GetViewMatrix(),
//		g_camera3D.GetProjectionMatrix()
//	);

	//g_graphicsEngine->EndRender();

}
