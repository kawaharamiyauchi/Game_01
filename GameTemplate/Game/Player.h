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
	/// �v���C���[�̈ʒu���擾
	/// </summary>
	/// <returns>m_position �v���C���[�̈ʒu</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// �v���C���[�̈ʒu�ݒ�
	/// </summary>
	/// <param name="pos">�ݒ肷��ʒu���W</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// �v���C���[�̉�]���擾
	/// </summary>
	/// <returns>m_rotation</returns>
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	/// <summary>
	/// �v���C���[�̉�]��ݒ�
	/// </summary>
	/// <param name="rot">�ݒ肷���]</param>

	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}

	void AnimationPlay();
	/// <summary>
	/// �v���C���[�̍X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �v���C���[�̕`�揈��
	/// </summary>
	void Render();

	/// <summary>
	/// �v���C���[�̈ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// �v���C���[�̉�]����
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
	SkinModel m_model;	//�X�L�����f���B
	Skeleton m_skleton;
	CVector3 m_speed = CVector3::Zero();
	CVector3 m_position =	{0.0f, 200.0f, -3000.0f};//�ʒu
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale =CVector3::One();					//�g�嗦
	CharacterController m_charaCon;
	plinfo m_plinfo;
	bool isPlus = false;
};

