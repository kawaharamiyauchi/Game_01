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
//	////�V���h�E�L���X�^�[��o�^�B
//	m_shadowMap.RegistShadowCaster(&m_unityChanModelDraw);
//	m_shadowMap.RegistShadowCaster(&m_bgModelDraw);
//	//�V���h�E�}�b�v���X�V�B

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
