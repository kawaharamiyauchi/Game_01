#pragma once
#include "character/CharacterController.h"
#include"IGameObject.h"
#include"character/CharacterController.h"

class Player:public IGameObject
{
public:
	Player();
	~Player();

	struct plinfo {
		float HP = 100.0f;
		float Stamina = 100.0f;

		

	};
	enum PlayerState {
		idle,
		run,
		damage,
		dye,
		attack
		
	};
	
	PlayerState p_state;
	plinfo GetPlayerInformation()
	{
		return m_plinfo;
	}
	
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

	void AnimationPlay();
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

	void StateChange();
	
	
private:
	enum Player_anim {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_damage,
		enAnimationClip_num
	};
	
	float move_x = 0.0f;
	float move_z = 0.0f;
	
	Animation m_animation;
	AnimationClip m_animationClip[enAnimationClip_num];
	SkinModel m_model;	//スキンモデル。
	Skeleton m_skleton;
	CVector3 m_speed = CVector3::Zero();
	CVector3 m_position =	{0.0f, 200.0f, -3000.0f};//位置
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale =CVector3::One();					//拡大率
	CharacterController m_charaCon;
	plinfo m_plinfo;
	bool isPlus = false;
};

