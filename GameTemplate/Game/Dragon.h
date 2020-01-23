#pragma once
#include "IGameObject.h"
#include"math/Matrix.h"
#include "GhostObject.h"
#include "SkinModelRender.h"
#include"character/CharacterController.h"
class Dragon :public IGameObject
{
public:
	Dragon();
	~Dragon();
	
	/// <summary>
	/// ƒhƒ‰ƒSƒ“‚Ìó‘Ô‘JˆÚ
	/// </summary>
	enum DragonState
	{
		normal,			///’Êí
		walk,			///•às
		run,			///¾‘–
		die,			///€–S
		attack,			///UŒ‚
		hornattack,		///‹­UŒ‚
		tailattack,		///”ÍˆÍUŒ‚
		scream,			///™ôšK
		damage,			///”í’e
		escape,			///“¦‘–
	};
	struct DragonInfo
	{
		bool isFind =false;
		bool isDead = false;
		float HP = 300.0f;
		
	};
	/// <summary>
	/// ƒhƒ‰ƒSƒ“‚ÌˆÊ’u‚ğæ“¾
	/// </summary>
	///<returns>m_position ƒhƒ‰ƒSƒ“‚ÌˆÊ’u</returns>
	CVector3 GetPosition()const
	{
		return m_position;
	}
	CVector3 GetFront()const
	{
		return m_front;
	}

	
	/// <summary>
	/// ƒhƒ‰ƒSƒ“‚Ìó‘Ô‚ğİ’è
	/// </summary>
	/// <param name="state">Œ»İ‚Ìó‘Ô</param>
	void SetDragonState(DragonState state)
	{

		d_state = state;
	}
	void DamageEvent();
	
	/// <summary>
	/// Œ»İ‚Ìƒhƒ‰ƒSƒ“‚Ìó‘Ô‚ğæ“¾
	/// </summary>
	/// <returns>Œ»İ‚Ìó‘Ô</returns>
	DragonState GetDragonState()const
	{
		return d_state;
	}
	/// <summary>
	/// ƒhƒ‰ƒSƒ“‚ÌˆÊ’u‚ğİ’è
	/// </summary>
	/// <param name="pos">İ’è‚·‚éˆÊ’uÀ•W</param>
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
	/// <summary>
	/// ƒhƒ‰ƒSƒ“‚ÌXVˆ—
	/// </summary>
	void Update();
	/// <summary>
	/// ƒhƒ‰ƒSƒ“‚Ì•`‰æˆ—
	/// </summary>
	void Render();

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
		DownBody,
		Tail,
		CharaConTypeSize,
	};
	CharacterController m_charaCon[CharaConTypeSize];
	Dragon_anim d_anim;
	DragonInfo d_info;
	DragonState d_state;
	AnimationClip animationClip[enAnimationClip_num];
	
	Animation m_animation;
	//CAnimationEvent m_canimation;
	AnimationEventListener m_listener;
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
	
	Skeleton* m_skeleton;
	
	int m_timer = 0;
	int rand_damage = 0;
	bool m_damageflag = false;
	bool h_attackflag = false;
	const wchar_t * bonename[41];
	//SkinModel m_model;		//ƒXƒLƒ“ƒ‚ƒfƒ‹
	//SkinModel m_test;
	SkinModelRender * m_skinModelRender = nullptr;
	GhostObject m_ghost[EventSize];
};
