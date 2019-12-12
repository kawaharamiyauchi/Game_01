#include "stdafx.h"
#include "GameObjectManager.h"
#include "Player.h"
//GameObjectManagerクラスのインスタンス作成


GameObjectManager::GameObjectManager()
{
	m_deleteObject.reserve(32);
	InitCamera();
	//メインとなるレンダリングターゲットを作成する。
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R8G8B8A8_UNORM
	);

	//メインレンダリングターゲットに描かれた絵を
		//フレームバッファにコピーするためのスプライトを初期化する。
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
	
	auto m_shadowMap = &ShadowMap::instance();
	//シャドウマップを更新。
	m_shadowMap->UpdateFromLightTarget(
		{ LightCameraPos.x+1000.0f ,
		  LightCameraPos.y +1000.0f,
		  LightCameraPos.z +1000.0f},
		{ LightCameraPos }
	);
	//登録済みのゲームオブジェクトの
	//Update関数を呼ぶ。
	for (auto go : m_goList)
	{
		go->Update();
	}
	Draw();

	//全てのゲームオブジェクトの1フレーム分の処理が終わってから、削除する。
	for (auto& it = m_goList.begin();it !=m_goList.end();)
	{
		//もし削除リクエストを受けていたなら
		if ((*it)->IsRequestDelete() ==true)
		{
			//m_deleteObject.push_back((*it));
			//削除
			delete(*it);
			it = m_goList.erase(it);
		}
		//それ以外なら
		else {
			//次へ
			it++;
		}
	}

	for (auto& go : m_deleteObject)
	{
		delete (go);
	}
	m_deleteObject.clear();

}
void GameObjectManager::BackUp()
{
	//フレームバッファののレンダリングターゲットをバックアップしておく。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&m_frameBufferRenderTargetView,
		&m_frameBufferDepthStencilView
	);
	//ビューポートもバックアップを取っておく。
	unsigned int numViewport = 1;
	d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);
}
void GameObjectManager::Draw()
{

	//プリレンダリング
	PreRender();

	//フォワードレンダリング。
	ForwordRender();

	//ポストレンダリング
	PostRender();



}

void GameObjectManager::PreRender()
{

	auto m_shadowMap = &ShadowMap::instance();
	m_shadowMap->RenderToShadowMap();
}

void GameObjectManager::ForwordRender()
{
	//レンダリングターゲットをメインに変更する。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
	//メインレンダリングターゲットをクリアする。
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);
	//Render関数を呼ぶ。
	for (auto go : m_goList)
	{
		go->Render();
	}
}

void GameObjectManager::PostRender()
{
	//レンダリングターゲットをフレームバッファに戻す。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(
		d3dDeviceContext,
		m_frameBufferRenderTargetView,
		m_frameBufferDepthStencilView,
		&m_frameBufferViewports
	);
	//ドロドロ
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
	//レンダリングターゲットの切り替え。
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
	if (viewport != nullptr) {
		//ビューポートが指定されていたら、ビューポートも変更する。
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
