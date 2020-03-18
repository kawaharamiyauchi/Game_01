#pragma once
#include"SkinModelRender.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
class Player:public IGameObject
{
public:
	Player();
	~Player();

	void OnAnimationEvent(const wchar_t * clipName, const wchar_t * eventName);

	struct plinfo {
		float HP = 100.0f;
		float AttackPower = 50.0f;
		float Stamina = 100.0f;
		bool isEnd =false;
	};
	enum PlayerState {
		idle,
		walk,
		run,
		jump,
		damage,
		die,
		attack,
		useitem
		
	};
	
	PlayerState p_state =idle;
	plinfo GetPlayerInformation()const
	{
		return m_plinfo;
	}
	
	/// <summary>
	/// �v���C���[�̈ʒu���擾
	/// </summary>
	/// <returns>m_position �v���C���[�̈ʒu</returns>
	CVector3 GetPosition() const
	{	
			return m_position[Hunter];	
	}
	/// <summary>
	/// �v���C���[�̈ʒu�ݒ�
	/// </summary>
	/// <param name="pos">�ݒ肷��ʒu���W</param>
	void SetPosition(CVector3 pos)
	{
		m_position[Hunter] = pos;
	}
	/// <summary>
	/// �v���C���[�̉�]���擾
	/// </summary>
	/// <returns>m_rotation</returns>
	CQuaternion GetRotation()
	{
		return m_rotation[Hunter];
	}
	/// <summary>
	/// �v���C���[�̉�]��ݒ�
	/// </summary>
	/// <param name="rot">�ݒ肷���]</param>

	void SetRotation(CQuaternion rot)
	{
		m_rotation[Hunter] = rot;
	}

	void SetDamageFlag(bool flag)
	{
		m_damageFlag = flag;
	}
	void SetDamage(float damage)
	{
		m_plinfo.HP -= damage;
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
	void ResetMove()
	{
		m_speed = CVector3::Zero();
	}
	void SetActive(bool isActive)
	{
		m_skinModelRender[Hunter]->SetActiveFlag(isActive);
	}

	void SetCharaConPos(CVector3 pos)
	{
		m_charaCon.SetPosition(pos);
	}

	void SetPlInfo(plinfo info)
	{
		m_plinfo = info;
	}
	const SkinModel* GetskinModel()const
	{
		return m_skinModelRender[Hunter]->GetSkinModel();
		//return m_model;
	}
	const int Getattack()const
	{
		return m_attackTimer;
	}
	CharacterController& GetcharaCon()
	{
		return m_charaCon;
	}
	Bone *GetPlayerBone(int bonenum)const
	{
		return m_skeleton->GetBone(bonenum);
	}

private:
	enum Player_anim {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_attack,
		enAnimationClip_damage,
		enAnimationClip_die,
		enAnimationClip_drink,
		enAnimationClip_num
	};
	enum Modeltype {
		Hunter,
		RightHand,
		LeftHand,
		Weapon,
		ModelType_num
	};
	enum SoundType
	{
		GetHit,
		move,
		SoundTypeNum
	};
	float move_x = 0.0f;
	float move_z = 0.0f;
	Animation m_animation;
	AnimationClip m_animationClip[enAnimationClip_num];
	//SkinModel m_model[] = new Modeltype[4]{};	//�X�L�����f���B
	//SkinModel m_model[ModelType_num];
	SkinModelRender *m_skinModelRender[ModelType_num] = { nullptr };
	Skeleton* m_skeleton;
	CVector3 m_speed = CVector3::Zero();
	CVector3 m_position[ModelType_num] = {CVector3::Zero()}; //�ʒu
	CQuaternion m_rotation[ModelType_num] = { CQuaternion::Identity() };	//��]
	CVector3 m_scale =CVector3::One();					//�g�嗦
	CharacterController m_charaCon;
	plinfo m_plinfo;
	bool m_damageFlag =false;
	bool m_jumpflag = false;
	bool m_dashflag = true;
	int m_damageTimer = 0;
	int m_attackTimer = 0;
	float footStop = 1.0f;
	int runTimer = 0;
	CVector3 m_footStep = CVector3::Zero();
	bool stopflag = false;
	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Manager*				m_effekseerManager = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;
	CSoundSource m_sound[SoundTypeNum];
};

