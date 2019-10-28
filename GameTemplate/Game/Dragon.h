#pragma once
#include "IGameObject.h"
#include"math/Matrix.h"

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
		walk,			///�p�j
		run,			///�ǐ�
		die,			///���S
		escape,			///����
	};
	/// <summary>
	/// �h���S���̈ʒu���擾
	/// </summary>
	///<returns>m_position �h���S���̈ʒu</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// �h���S���̏�Ԃ�ݒ�
	/// </summary>
	/// <param name="state">���݂̏��</param>
	void SetDragonState(DragonState state)
	{

		d_state = state;
	}
	/// <summary>
	/// ���݂̃h���S���̏�Ԃ��擾
	/// </summary>
	/// <returns>���݂̏��</returns>
	DragonState GetDragonState()
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
	/// <summary>
	/// �h���S���̍X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �h���S���̕`�揈��
	/// </summary>
	void Render();

private:
	enum {
		enAnimationClip_idle,
		enAnimationClip_num,

	};
	

	DragonState d_state;
	AnimationClip animationClip[enAnimationClip_num];
	
	Animation m_animation;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One();

	CVector3 diff = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	Skeleton m_skeleton;
	CMatrix m_bone[40] = {CMatrix::Identity() };
	AnimationPlayController m_aniCon;
	float a = 0.0f;
	
	const wchar_t * bonename[41];
	SkinModel m_model;		//�X�L�����f��
};

