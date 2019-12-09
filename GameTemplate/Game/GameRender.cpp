#include "stdafx.h"
#include "GameRender.h"


GameRender::GameRender()
{

	InitCamera();
	//Unity�����̃��f�����������B
	m_unityChanModelDraw.Init(L"Assets/modelData/unityChan.cmo");
	//�w�i���f���̏����������B
	m_bgModelDraw.Init(L"Assets/modelData/bg.cmo");
	//���C���ƂȂ郌���_�����O�^�[�Q�b�g���쐬����B
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R8G8B8A8_UNORM
	);

	//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G��
	//�t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g������������B
	m_copyMainRtToFrameBufferSprite.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
}


GameRender::~GameRender()
{
	if (m_frameBufferRenderTargetView != nullptr) {
		m_frameBufferRenderTargetView->Release();
	}
	if (m_frameBufferDepthStencilView != nullptr) {
		m_frameBufferDepthStencilView->Release();
	}
}

void GameRender::InitCamera()
{
	g_camera3D.SetPosition({ 0.0f, 1000.0f, 2200.0f });
	g_camera3D.SetTarget({ 0.0f, 200.0f, 0.0f });
	g_camera3D.Update();
	//g_camera2D.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	g_camera2D.SetWidth(FRAME_BUFFER_W);
	g_camera2D.SetHeight(FRAME_BUFFER_H);
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.Update();
}
void GameRender::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport)
{
	ChangeRenderTarget(
		d3dDeviceContext,
		renderTarget->GetRenderTargetView(),
		renderTarget->GetDepthStensilView(),
		viewport
	);
}

void GameRender::ChangeRenderTarget(ID3D11DeviceContext * d3dDeviceContext, ID3D11RenderTargetView * renderTarget, ID3D11DepthStencilView * depthStensil, D3D11_VIEWPORT * viewport)
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
void GameRender::Update()
{
	m_unityChanModelDraw.Update(m_unityChanPos);
}
void GameRender::PreRender()
{

}
void GameRender::ForwordRender()
{

	//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
	//���C�������_�����O�^�[�Q�b�g���N���A����B
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);

	m_bgModelDraw.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	m_unityChanModelDraw.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	
}
void GameRender::PostRender()
{
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
void GameRender::Render()
{
	//�`��J�n�B
	//g_graphicsEngine->BegineRender();
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

	//�v�������_�����O
	//PreRender();

	//�t�H���[�h�����_�����O�B
	ForwordRender();

	//�|�X�g�����_�����O
	PostRender();

	//�`��I���B
	//g_graphicsEngine->EndRender();

}