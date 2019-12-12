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
	//�J������ݒ�B
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
//	//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
//	ID3D11RenderTargetView* oldRenderTargetView;
//	ID3D11DepthStencilView* oldDepthStencilView;
//	d3dDeviceContext->OMGetRenderTargets(
//		1,
//		&oldRenderTargetView,
//		&oldDepthStencilView
//	);
//	//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
//	unsigned int numViewport = 1;
//	D3D11_VIEWPORT oldViewports;
//	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);
//
//	//�V���h�E�}�b�v�Ƀ����_�����O
//	m_shadowMap.RenderToShadowMap();
//	//���ɖ߂��B
//	d3dDeviceContext->OMSetRenderTargets(
//		1,
//		&oldRenderTargetView,
//		oldDepthStencilView
//	);
//	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
//	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
//	oldRenderTargetView->Release();
//	oldDepthStencilView->Release();
//
//	///////////////////////////////////////////////
//	//��������ʏ탌���_�����O�B
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
