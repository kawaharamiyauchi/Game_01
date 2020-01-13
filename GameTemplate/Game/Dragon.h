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
	/// �h���S���̏�ԑJ��
	/// </summary>
	enum DragonState
	{
		normal,			///�ʏ�
		walk,			///���s
		run,			///����
		die,			///���S
		attack,			///�U��
		escape,			///����
	};
	struct DragonInfo
	{
		bool isFind =false;
		bool isDead = false;
		float HP = 1000.0f;
		
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

	void AnimationPlay();

	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	
	void SetState();
	void Move();
	void CharaConMove();
	/// <summary>
	/// �h���S���̍X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �h���S���̕`�揈��
	/// </summary>
	void Render();

private:
	enum Dragon_anim{
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_attack,
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
	
	float a = 0.0;
	int m_timer = 0;
	const wchar_t * bonename[41];
	SkinModel m_model;		//�X�L�����f��
	//SkinModel m_test;
	SkinModelRender * m_skinModelRender = nullptr;
	GhostObject m_ghost[EventSize];
};
