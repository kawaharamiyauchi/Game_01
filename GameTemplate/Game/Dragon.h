#pragma once
#include "IGameObject.h"
#include"math/Matrix.h"
#include "GhostObject.h"
#include "SkinModelRender.h"
#include"character/CharacterController.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include"Player.h"
class Item;
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
		walk,			///歩行
		run,			///疾走
		die,			///死亡
		attack,			///攻撃
		hornattack,		///強攻撃
		tailattack,		///範囲攻撃
		scream,			///咆哮
		damage,			///被弾
		escape,			///逃走
	};
	struct DragonInfo
	{
		bool isFind =false;
		bool isDead = false;
		float HP = 1500.0f;
		bool isEnd = false;
	};
	/// <summary>
	/// ドラゴンの位置を取得
	/// </summary>
	///<returns>m_position ドラゴンの位置</returns>
	CVector3 GetPosition()const
	{
		return m_position;
	}
	CVector3 GetFront()const
	{
		return m_front;
	}
	bool GetHitFlag()const
	{
		return m_damageflag;
	}
	DragonInfo GetDragonInfo()const
	{
		return d_info;
	}
	/// <summary>
	/// ドラゴンの状態を設定
	/// </summary>
	/// <param name="state">現在の状態</param>
	void SetDragonState(DragonState state)
	{

		d_state = state;
	}
	void DamageEvent();
	
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
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	void AnimationPlay();
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	
	void SetState();
	void Move();
	void CharaConMove();
	bool Start();
	/// <summary>
	/// ドラゴンの更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// ドラゴンの描画処理
	/// </summary>
	void Render();
	void ColliderInit(int type, float radius, float height, CVector3& position);

private:
	enum Dragon_anim{
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_attack,
		enAnimationClip_hornAttack,
		enAnimationClip_tailAttack,
		enAnimationClip_getHit,
		enAnimationClip_run,
		enAnimationClip_scream,
		enAnimationClip_die,
		enAnimationClip_num,

	};
	enum anim_event {
		D_attack00,
		P_attack00,
		EventSize,
	};
	enum CharaConType
	{
		Head,
		UpBody,
		Body,
		Tail,
		CharaConTypeSize,
	};
	enum SoundType
	{
		screamvoice,
		gethit,
		SoundTypeNum
	};
	CharacterController m_charaCon[CharaConTypeSize];
	CapsuleCollider m_collider[3] ;
	RigidBody m_rigidBody;
	Dragon_anim d_anim;
	DragonInfo d_info;
	DragonState d_state;
	AnimationClip animationClip[enAnimationClip_num];
	
	Animation m_animation;
	//CAnimationEvent m_canimation;
	//AnimationEventListener m_listener;
	Bone *m_bone[CharaConTypeSize];
	CVector3 m_position = CVector3::Zero();
	CVector3 m_charaConPos[CharaConTypeSize] ={CVector3::Zero()};
	CVector3 m_scale = CVector3::One();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 moveSpeed =CVector3::Zero();
	CVector3 m_collisionPosition = CVector3::Zero();
	CVector3 m_collisionScale = CVector3::One();
	CVector3 m_front = CVector3::Zero();

	float angle = 0.0f;
	CVector3 diff = CVector3::Zero();
	CVector3 move = CVector3::Zero();
	Skeleton* m_skeleton;
	
	int m_timer = 0;
	int rand_damage = 0;
	int escapetimer = 0;
	int walktimer = 0;
	bool m_damageflag = false;
	bool h_attackflag = false;
	const wchar_t * bonename[41];
	//SkinModel m_model;		//スキンモデル
	//SkinModel m_test;
	SkinModelRender * m_skinModelRender = nullptr;
	GhostObject m_ghost[EventSize];
	Item *m_Item = nullptr;
	CSoundSource m_sound[SoundTypeNum];
};
