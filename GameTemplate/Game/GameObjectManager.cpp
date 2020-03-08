#include "stdafx.h"
#include "GameObjectManager.h"
#include "Player.h"
#include"ShadowMap.h"

GameObjectManager::EffekseerTool g_effect;
//GameObjectManager�N���X�̃C���X�^���X�쐬

void GameObjectManager::Start()
{
	for (auto go:m_goList) {
		for (IGameObject* obj : m_goList) {
			obj->StartWrapper();
		}
	}
}

GameObjectManager::GameObjectManager()
{

	//Effekseer���������B
	InitEffekseer();

	m_soundEngine.Init();
	//�G�t�F�N�g���Đ�����B
	//m_playEffectHandle = m_effekseerManager->Play(m_sampleEffect, 0.0f, 0.0f, 0.0f);
	m_deleteObject.reserve(32);
	InitCamera();
	//���C���ƂȂ郌���_�����O�^�[�Q�b�g���쐬����B
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		//DXGI_FORMAT_R8G8B8A8_UNORM
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);

	//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G��
		//�t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g������������B
	m_copyMainRtToFrameBufferSprite.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);

}
GameObjectManager::~GameObjectManager()
{
	if (m_frameBufferRenderTargetView != nullptr) {
		m_frameBufferRenderTargetView->Release();
	}
	if (m_frameBufferDepthStencilView != nullptr) {
		m_frameBufferDepthStencilView->Release();
	}
}
void GameObjectManager::Update()
{

	if (SpeedCount == 101 - ExecuteSpeed) {
		//�o�^�ς݂̃Q�[���I�u�W�F�N�g��
		//Update�֐����ĂԁB
		for (auto go : m_goList)
		{
			go->Update();
		}
		SpeedCount = 0;
	}
	//Effekseer�J�����s���ݒ�B
	//�܂���Effeseer�̍s��^�̕ϐ��ɁA�J�����s��ƃv���W�F�N�V�����s����R�s�[�B
	Effekseer::Matrix44 efCameraMat;
	g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
	Effekseer::Matrix44 efProjMat;
	g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
	//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
	g_effect.m_effekseerRenderer->SetCameraMatrix(efCameraMat);
	g_effect.m_effekseerRenderer->SetProjectionMatrix(efProjMat);
	
	//Effekseer���X�V�B
	g_effect.m_effekseerManager->Update();

	m_soundEngine.Update();
	SpeedCount++;
	auto m_shadowMap = &ShadowMap::instance();
	//�V���h�E�}�b�v���X�V�B
	m_shadowMap->UpdateFromLightTarget(
		{ LightCameraPos.x+1000.0f ,
		  LightCameraPos.y +1000.0f,
		  LightCameraPos.z +1000.0f},
		{ LightCameraPos }
	);
	
	Fade::instance().Update();
	Draw();

	//�S�ẴQ�[���I�u�W�F�N�g��1�t���[�����̏������I����Ă���A�폜����B
	for (auto& it = m_goList.begin();it !=m_goList.end();)
	{
		//�����폜���N�G�X�g���󂯂Ă����Ȃ�
		if ((*it)->IsRequestDelete() ==true)
		{
			//m_deleteObject.push_back((*it));
			//�폜
			delete(*it);
			it = m_goList.erase(it);
		}
		//����ȊO�Ȃ�
		else {
			//����
			it++;
		}
	}

	for (auto& go : m_deleteObject)
	{
		delete (go);
	}
	
	m_deleteObject.clear();
	//�|�X�g�G�t�F�N�g�̍X�V�����B
	m_postEffect.Update();

	
}
void GameObjectManager::BackUp()
{
	//�t���[���o�b�t�@�̂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&m_frameBufferRenderTargetView,
		&m_frameBufferDepthStencilView
	);
	//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
	unsigned int numViewport = 1;
	d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);
}
void GameObjectManager::Draw()
{

	//�v�������_�����O
	PreRender();

	//�t�H���[�h�����_�����O�B
	ForwordRender();

	//�|�X�g�����_�����O
	PostRender();



}

void GameObjectManager::PreRender()
{

	auto m_shadowMap = &ShadowMap::instance();
	m_shadowMap->RenderToShadowMap();
}

void GameObjectManager::ForwordRender()
{
	//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
	//���C�������_�����O�^�[�Q�b�g���N���A����B
	float clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);
	//Render�֐����ĂԁB
	for (auto go : m_goList)
	{
		go->Render();
	}
	//�G�t�F�N�g�͕s�����I�u�W�F�N�g��`�悵����ŕ`�悷��B
	g_effect.m_effekseerRenderer->BeginRendering();
	g_effect.m_effekseerManager->SetScale(g_effect.m_playEffectHandle,20.0f,20.0f,20.0f);
	g_effect.m_effekseerManager->Draw();
	g_effect.m_effekseerRenderer->EndRendering();
}

void GameObjectManager::PostRender()
{
	for (auto go : m_goList)
	{
		go->PostRender();
	}
	Fade::instance().PostRender();
	//�|�X�g�G�t�F�N�g�̕`�揈���B
	m_postEffect.Draw();
	
	//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂��B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(
		d3dDeviceContext,
		m_frameBufferRenderTargetView,
		m_frameBufferDepthStencilView,
		&m_frameBufferViewports
	);
	//�h���h��
	m_copyMainRtToFrameBufferSprite.Draw();

	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();

}

void GameObjectManager::ChangeRenderTarget(ID3D11DeviceContext * d3dDeviceContext, RenderTarget * renderTarget, D3D11_VIEWPORT * viewport)
{
	
	ChangeRenderTarget(
		d3dDeviceContext,
		renderTarget->GetRenderTargetView(),
		renderTarget->GetDepthStensilView(),
		viewport
	);
}

void GameObjectManager::ChangeRenderTarget(ID3D11DeviceContext * d3dDeviceContext, ID3D11RenderTargetView * renderTarget, ID3D11DepthStencilView * depthStensil, D3D11_VIEWPORT * viewport)
{
	ID3D11RenderTargetView* rtTbl[] = {
		renderTarget
	};
	//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
	if (viewport != nullptr) {
		//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
		d3dDeviceContext->RSSetViewports(1, viewport);
		
	}
}

void GameObjectManager::InitCamera()
{
	g_camera3D.SetPosition({ 0.0f, 1000.0f, 2200.0f });
	g_camera3D.SetTarget({ 0.0f, 200.0f, 0.0f });
	g_camera3D.Update();
	g_camera2D.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	g_camera2D.SetWidth(FRAME_BUFFER_W);
	g_camera2D.SetHeight(FRAME_BUFFER_H);
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.Update();
}
void GameObjectManager::InitEffekseer()
{
	//�����_���[���������B
	g_effect.m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3D�f�o�C�X�B
		g_graphicsEngine->GetD3DDeviceContext(),	//D3D�f�o�C�X�R���e�L�X�g�B
		20000										//�|���̍ő吔�B
	);
	//�G�t�F�N�g�}�l�[�W�����������B
	g_effect.m_effekseerManager = Effekseer::Manager::Create(10000);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	g_effect.m_effekseerManager->SetSpriteRenderer(g_effect.m_effekseerRenderer->CreateSpriteRenderer());
	g_effect.m_effekseerManager->SetRibbonRenderer(g_effect.m_effekseerRenderer->CreateRibbonRenderer());
	g_effect.m_effekseerManager->SetRingRenderer(g_effect.m_effekseerRenderer->CreateRingRenderer());
	g_effect.m_effekseerManager->SetTrackRenderer(g_effect.m_effekseerRenderer->CreateTrackRenderer());
	g_effect.m_effekseerManager->SetModelRenderer(g_effect.m_effekseerRenderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	g_effect.m_effekseerManager->SetTextureLoader(g_effect.m_effekseerRenderer->CreateTextureLoader());
	g_effect.m_effekseerManager->SetModelLoader(g_effect.m_effekseerRenderer->CreateModelLoader());



}