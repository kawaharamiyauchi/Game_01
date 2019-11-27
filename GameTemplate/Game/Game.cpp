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
	m_gamecamera = g_goMgr.NewGO<GameCamera>();
		m_player = g_goMgr.NewGO<Player>();
		
		m_background = g_goMgr.NewGO<BackGround>();
	  m_dragon = g_goMgr.NewGO<Dragon>();
		
		
		m_UI = g_goMgr.NewGO<UI>();
	
}

Game::~Game()
{
	
	g_goMgr.DeleteGO(m_background);
	g_goMgr.DeleteGO(m_gamecamera);
	g_goMgr.DeleteGO(m_dragon);
	g_goMgr.DeleteGO(m_UI);
	g_goMgr.DeleteGO(m_player);
	
}
void Game::Update()
{
	
//	m_unityChanPos.x += g_pad[0].GetLStickXF() * -50.0f;
//	m_unityChanPos.z += g_pad[0].GetLStickYF() * -50.0f;
//
//	m_unityChanModelDraw.Update(m_unityChanPos);
//
//	////シャドウキャスターを登録。
//	m_shadowMap.RegistShadowCaster(&m_unityChanModelDraw);
//	m_shadowMap.RegistShadowCaster(&m_bgModelDraw);
//	//シャドウマップを更新。

	/*m_shadowMap.UpdateFromLightTarget(
		{ 1000.0f, 1000.0f, 1000.0f },
		{ 0.0f, 0.0f, 0.0f }
	);*/
//
//	
	if (g_pad[0].IsTrigger(enButtonSelect))
	{

		g_goMgr.DeleteGO(this);
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
