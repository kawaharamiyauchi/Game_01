#pragma once
#include "IGameObject.h"
#include <iostream>
#include "RenderTarget.h"
#include "Sprite.h"

using namespace std;
class GameObjectManager
{
public:
	static GameObjectManager& instance()
	{
		static GameObjectManager instance;
		return instance;
	}
private:

	GameObjectManager();
	~GameObjectManager();
public:
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
	/// レンダリングターゲットの切り替え。
	/// </summary>
	/// <param name="d3dDeviceContext">D3Dデバイスコンテキスト</param>
	/// <param name="renderTarget">レンダリングターゲット</param>
	/// <param name="viewport">ビューポート</param>
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
	/// <summary>
	/// カメラを初期化。
	/// </summary>
	void InitCamera();


private:
	CVector3 LightCameraPos = CVector3::Zero();
	Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。												
	//ゲームオブジェクトのリスト	
	std::vector<IGameObject*> m_goList;

	std::vector<IGameObject*> m_deleteObject;
	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
};

