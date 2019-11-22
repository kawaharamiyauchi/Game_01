#pragma once
#include "IGameObject.h"
#include"math/Matrix.h"
#include "GhostObject.h"
#include"character/CharacterController.h"
class Dragon :public IGameObject
{
public:
	Dragon();
	~Dragon();
	
	/// <summary>
	/// ドラゴンの状態遷移
	/// </summary>
	enum DragonState
	{
		normal,			///通常
		walk,			///徘徊
		run,			///追跡
		die,			///死亡
		attack,			///攻撃
		escape,			///逃走
	};
	/// <summary>
	/// ドラゴンの位置を取得
	/// </summary>
	///<returns>m_position ドラゴンの位置</returns>
	CVector3 GetPosition()const
	{
		return m_position;
	}

	/// <summary>
	/// ドラゴンの状態を設定
	/// </summary>
	/// <param name="state">現在の状態</param>
	void SetDragonState(DragonState state)
	{

		d_state = state;
	}
	/// <summary>
	/// 現在のドラゴンの状態を取得
	/// </summary>
	/// <returns>現在の状態</returns>
	DragonState GetDragonState()const
	{
		return d_state;
	}
	/// <summary>
	/// ドラゴンの位置を設定
	/// </summary>
	/// <param name="pos">設定する位置座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	void AnimationPlay();

	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	
	void Move();
	/// <summary>
	/// ドラゴンの更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// ドラゴンの描画処理
	/// </summary>
	void Render();

private:
	enum Dragon_anim{
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_attack,
		enAnimationClip_run,
		enAnimationClip_scream,
		enAnimationClip_num,

	};
	
	Dragon_anim d_anim;
	DragonState d_state;
	AnimationClip animationClip[enAnimationClip_num];
	
	Animation m_animation;
	CAnimationEvent m_canimation;
	AnimationEventListener m_listener;

	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One();
	CQuaternion m_rotation = CQuaternion::Identity();

	CVector3 m_collisionPosition = CVector3::Zero();
	CVector3 m_collisionScale = CVector3::One();


	float angle = 0.0f;
	CVector3 diff = CVector3::Zero();
	
	Skeleton* m_skeleton;
	
	CharacterController m_charaCon[5];
	float a = 0.0;
	int m_timer = 0;
	const wchar_t * bonename[41];
	SkinModel m_model;		//スキンモデル
	//SkinModel m_test;
	GhostObject m_ghost;
};

