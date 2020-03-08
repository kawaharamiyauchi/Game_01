#pragma once
#include"SkinModelRender.h"
#include "Player.h"
#include "GhostObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
class LittleEnemy:public IGameObject
{
public:
	LittleEnemy();
	~LittleEnemy();

	enum EnemyState
	{
		normal,			///í èÌ
		walk,			///ï‡çs
		run,			///éæëñ
		die,			///éÄñS
		attack,			///çUåÇ
		hornattack,		///ã≠çUåÇ
		tailattack,		///îÕàÕçUåÇ
		scream,			///ôÙöK
		damage,			///îÌíe
		escape,			///ì¶ëñ
	};
	enum EnemyType
	{
		blue
	};
	struct littleEnemyInformation
	{
		EnemyType Type = blue;
		float HP = 200.0f;

		float attackPower = 10.0f;


	};

	void SetEnemyState(EnemyState state)
	{

		d_state = state;
	}
	void SetCharaConPos(CVector3 pos)
	{
		m_charaCon.SetPosition(pos);
	}
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	void Update();
	void Render();
	void Move();
	void AnimationPlay();
	void DamageEvent();
	void ChangeState();
	void OnAnimationEvent(const wchar_t * clipName, const wchar_t * eventName);
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()const
	{
		return m_position;
	}
private:
	enum enemy_anim {
		enAnimationClip_idle,
		enAnimationClip_move,
		enAnimationClip_damage,
		enAnimationClip_attack,
		enAnimationClip_die,
		enAnimationClip_num
	};
	enum anim_event {
		D_attack00,
		P_attack00,
		EventSize,
	};
	SkinModelRender *m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();

	CVector3 moveSpeed = CVector3::Zero();
	CVector3 diff = CVector3::Zero();

	Animation m_animation;
	AnimationClip animationClip[enAnimationClip_num];
	EnemyState d_state =normal;
	GhostObject m_ghost[EventSize];
	CharacterController m_charaCon;
	littleEnemyInformation m_enemyInfo;

	Skeleton* m_skeleton;
	const wchar_t * bonename[41];
	bool attackflag = false;
	bool m_damageflag = false;

	CSoundSource m_sound[2];
};

