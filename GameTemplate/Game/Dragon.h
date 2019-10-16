#pragma once
#include "IGameObject.h"
#include"math/Matrix.h";
class Dragon :public IGameObject
{
public:
	Dragon();
	~Dragon();

	/// <summary>
	/// �h���S���̈ʒu���擾
	/// </summary>
	///<returns>m_position �h���S���̈ʒu</returns>
	CVector3 GetPosition()
	{
		return m_position;
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
	AnimationClip animationClip[enAnimationClip_num];
	Animation m_animation;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One();
	CQuaternion m_rotation = CQuaternion::Identity();
	Skeleton m_skeleton;
	CMatrix m_bone[40] = {CMatrix::Identity() };
	float a = 0.0f;
	
	const wchar_t * bonename[41];
	SkinModel m_model;		//�X�L�����f��
};

