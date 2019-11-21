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
	/// ƒhƒ‰ƒSƒ“‚Ìó‘Ô‘JˆÚ
	/// </summary>
	enum DragonState
	{
		normal,			///’Êí
		walk,			///œpœj
		run,			///’ÇÕ
		die,			///€–S
		attack,			///UŒ‚
		escape,			///“¦‘–
	};
	/// <summary>
	/// ƒhƒ‰ƒSƒ“‚ÌˆÊ’u‚ğæ“¾
	/// </summary>
	///<returns>m_position ƒhƒ‰ƒSƒ“‚ÌˆÊ’u</returns>
	CVector3 GetPosition()const
	{
		return m_position;
	}

	/// <summary>
	/// ƒhƒ‰ƒSƒ“‚Ìó‘Ô‚ğİ’è
	/// </summary>
	/// <param name="state">Œ»İ‚Ìó‘Ô</param>
	void SetDragonState(DragonState state)
	{

		d_state = state;
	}
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

	void AnimationPlay();

	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	
	void Move();
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
	CVector3 m_collisionScale = { 3000.0f,1000.0f,3000.0f };

	CVector3 diff = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	Skeleton m_skeleton;
	CMatrix m_bone[40] = {CMatrix::Identity() };
	//AnimationPlayController m_aniCon;
	float a = 0.0;
	int m_timer = 0;
	const wchar_t * bonename[41];
	SkinModel m_model;		//ƒXƒLƒ“ƒ‚ƒfƒ‹
	
	GhostObject m_ghost;
};

