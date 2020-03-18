#pragma once
#include"IGameObject.h"
#include "Game.h"
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	enum CameraState {
		normal,
		GameClear,
		GameOver
	};
	/// <summary>
	/// カメラの位置情報を取得
	/// </summary>
	/// <returns　m_position>カメラの位置</returns>
	CVector3 GetPosition()
	{
		return m_toCameraPos;
	}

	/// <summary>
	/// カメラの位置を設定
	/// </summary>
	/// <param name="pos">カメラの位置</param>
	void SetPosition(CVector3 pos)
	{
		m_toCameraPos = pos;
	}
	/// <summary>
	/// 注視点の座標設定
	/// </summary>
	/// <param name="t">設定する注視点位置座標</param>
	void SetTarget(CVector3 t)
	{
		m_target = t;
	}

	void Reset();
	
	void ChangeCameraState();
	void Update();		//更新処理
	void Render();		//描画処理
private:
	CVector3 m_toCameraPos = CVector3::Zero();		//位置
	CVector3 m_target = CVector3::Zero();		//注視点の座標
	CVector3 m_position;
	int m_timer = 0;
	CameraState m_CS = normal;
};

