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
	/// プレイヤーの位置を取得
	/// </summary>
	/// <returns>m_position プレイヤーの位置</returns>
	CVector3 GetPosition() const
	{	
			return m_position[Hunter];	
	}
	/// <summary>
	/// プレイヤーの位置設定
	/// </summary>
	/// <param name="pos">設定する位置座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position[Hunter] = pos;
	}
	/// <summary>
	/// プレイヤーの回転を取得
	/// </summary>
	/// <returns>m_rotation</returns>
	CQuaternion GetRotation()
	{
		return m_rotation[Hunter];
	}
	/// <summary>
	/// プレイヤーの回転を設定
	/// </summary>
	/// <param name="rot">設定する回転</param>

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
	//SkinModel m_model[] = new Modeltype[4]{};	//スキンモデル。
	//SkinModel m_model[ModelType_num];
	SkinModelRender *m_skinModelRender[ModelType_num] = { nullptr };
	Skeleton* m_skeleton;
	CVector3 m_speed = CVector3::Zero();
	CVector3 m_position[ModelType_num] = {CVector3::Zero()}; //位置
	CQuaternion m_rotation[ModelType_num] = { CQuaternion::Identity() };	//回転
	CVector3 m_scale =CVector3::One();					//拡大率
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

