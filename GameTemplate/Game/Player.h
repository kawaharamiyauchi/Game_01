#pragma once
#include "character/CharacterController.h"
#include"IGameObject.h"
#include"character/CharacterController.h"
class Player:public IGameObject
{
public:
	Player();
	~Player();

	/// <summary>
	/// プレイヤーの位置を取得
	/// </summary>
	/// <returns>m_position プレイヤーの位置</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// プレイヤーの位置設定
	/// </summary>
	/// <param name="pos">設定する位置座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// プレイヤーの回転を取得
	/// </summary>
	/// <returns>m_rotation</returns>
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	/// <summary>
	/// プレイヤーの回転を設定
	/// </summary>
	/// <param name="rot">設定する回転</param>

	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// プレイヤーの更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// プレイヤーの描画処理
	/// </summary>
	void Render();

	/// <summary>
	/// プレイヤーの移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// プレイヤーの回転処理
	/// </summary>
	void Turn();
private:
	float move_x = 0.0f;
	float move_z = 0.0f;
	
	
	SkinModel m_model;	//スキンモデル。
	CVector3 m_speed = CVector3::One();
	CVector3 m_position =CVector3::Zero();				//位置
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale =CVector3::One();					//拡大率
	CharacterController m_charaCon;

};

