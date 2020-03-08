#pragma once


#include "stdafx.h"
#include "IGameObject.h"
#include <iostream>
#include "RenderTarget.h"
#include "Sprite.h"
#include "Fade.h"
#include "PostEffect.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
using namespace std;
class GameObjectManager
{
public:

	struct EffekseerTool
	{
		//Effekseerマネージャ管理。
		Effekseer::Manager*				m_effekseerManager = nullptr;
		EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;

		Effekseer::Effect* m_sampleEffect = nullptr;
		Effekseer::Handle m_playEffectHandle = -1;
	};
	static GameObjectManager& instance()
	{
		static GameObjectManager instance;
		return instance;
	}

	/// <summary>
	/// メインレンダリングターゲットを取得。
	/// </summary>
	/// 
	RenderTarget* GetMainRenderTarget()
	{
		return &m_mainRenderTarget;
	}
private:

	

	GameObjectManager();
	~GameObjectManager();
public:

	void Start();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	void BackUp();
	
	/// <summary>
	/// ゲームオブジェクトを追加
	/// </summary>
	/// <param name ="name">作成するゲームオブジェクト</param>
	template<class T>
	T*NewGO()
	{
		T*newObj = new T;
		m_goList.push_back(newObj);
		
		return newObj;
	}

	/// /// <summary>
	/// ゲームオブジェクトをリストから削除。
	/// </summary>
	///<param name ="go">削除するゲームオブジェクト</param>
	void DeleteGO(IGameObject* go)
	{
		for (auto it = m_goList.begin(); it != m_goList.end(); it++)
		{
			if ((*it) == go) {

				go->RequestDelete();
				go->OnDestroy();
			}
		}
	}
	void SetLightCameraPos(CVector3 pos)
	{
		LightCameraPos = pos;
		

	}
private:
	void Draw();
	/// <summary>
	/// プリレンダリング。
	/// </summary>
	void PreRender();
	/// <summary>
	/// フォワードレンダリング(通常の描画だと考えてOK)
	/// </summary>
	void ForwordRender();
	/// <summary>
	/// ポストレンダリング
	/// </summary>
	void PostRender();
	/// <summary>
	/// カメラを初期化。
	/// </summary>
	void InitCamera();
public:
	/// <summary>
	/// レンダリングターゲットの切り替え。
	/// </summary>
	/// <param name="d3dDeviceContext">D3Dデバイスコンテキスト</param>
	/// <param name="renderTarget">レンダリングターゲット</param>
	/// <param name="viewport">ビューポート</param>
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
public:
	void CountPlus()
	{
		GameCount++;
	}
	int GetGameCount()const
	{
		return GameCount;
	}
	void SetExecuteSpeed(int speed)
	{
		ExecuteSpeed = speed;
	}
	/// <summary>
	/// Effekseerの初期化。
	/// </summary>
	void InitEffekseer();
private:
	int GameCount = 0;
	int ExecuteSpeed = 100;
	int SpeedCount = 0;
	CVector3 LightCameraPos = CVector3::Zero();
	Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。												
	PostEffect m_postEffect;
	CVector4 m_ligPower = { 2.0f,2.0f,2.0f,1.0f };
	//ゲームオブジェクトのリスト	
	std::vector<IGameObject*> m_goList;

	std::vector<IGameObject*> m_deleteObject;
	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。

	CSoundEngine m_soundEngine;

	

	


};

extern GameObjectManager::EffekseerTool g_effect;