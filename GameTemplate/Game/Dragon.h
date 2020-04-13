#pragma once
#include "IGameObject.h"
#include"math/Matrix.h"
#include "GhostObject.h"
#include "SkinModelRender.h"
#include"character/CharacterController.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include"Player.h"
class Dragon :public IGameObject
{
public:
	Dragon();
	~Dragon();
	
	/// <summary>
	/// �h���S���̏�ԑJ��
	/// </summary>
	enum DragonState
	{
		normal,			///�ʏ�
		walk,			///���s
		run,			///����
		die,			///���S
		attack,			///�U��
		hornattack,		///���U��
		tailattack,		///�͈͍U��
		scream,			///���K
		damage,			///��e
		escape,			///����
	};
	struct DragonInfo
	{
		bool isFind =false;
		bool isDead = false;
		float HP = 500.0f;
		bool isEnd = false;
	};
	/// <summary>
	/// �h���S���̈ʒu���擾
	/// </summary>
	///<returns>m_position �h���S���̈ʒu</returns>
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
	/// �h���S���̏�Ԃ�ݒ�
	/// </summary>
	/// <param name="state">���݂̏��</param>
	void SetDragonState(DragonState state)
	{

		d_state = state;
	}
	void DamageEvent();
	
	/// <summary>
	/// ���݂̃h���S���̏�Ԃ��擾
	/// </summary>
	/// <returns>���݂̏��</returns>
	DragonState GetDragonState()const
	{
		return d_state;
	}
	/// <summary>
	/// �h���S���̈ʒu��ݒ�
	/// </summary>
	/// <param name="pos">�ݒ肷��ʒu���W</param>
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
	/// �h���S���̍X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �h���S���̕`�揈��
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
	bool m_damageflag = false;
	bool h_attackflag = false;
	const wchar_t * bonename[41];
	//SkinModel m_model;		//�X�L�����f��
	//SkinModel m_test;
	SkinModelRender * m_skinModelRender = nullptr;
	GhostObject m_ghost[EventSize];

	CSoundSource m_sound[SoundTypeNum];
};
