#pragma once
#include "graphics/SkinModel.h"
class SkinModelRender:public IGameObject
{
public:
	SkinModelRender();
	~SkinModelRender();

	
	void Init(const wchar_t*filePath);

	/// <summary>
	/// �V���h�E�L���X�^�[�̃t���O��ݒ�
	/// </summary>
	/// <param name="flag">�V���h�E�L���X�^�[�t���O</param>
	void SetShadowCasterFlag(bool flag)
	{
		m_skinModel.SetShadowCasterFlag(flag);
	}
	/// <summary>
	/// �V���h�E���V�[�o�[�̃t���O��ݒ�
	/// </summary>
	/// <param name="flag">�V���h�E���V�[�o�[�t���O</param>
	void SetShadowRecieverFlag(bool flag)
	{
		m_skinModel.SetShadowReciever(flag);
	}
	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	/// <param name="sca">�g�嗦</param>
	void SetScale(const CVector3& sca)
	{
		m_scale = sca;
	}
	/// <summary>
	/// �X�L�����f�����擾
	/// </summary>
	 SkinModel* GetSkinModel()
	{
		return &m_skinModel;
	}

	Skeleton* GetSkeleton()
	{
		return &m_skinModel.GetSkeleton();
	}
	void Update();
	void Render();
	SkinModel m_skinModel;
private:
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	EnFbxUpAxis					m_enFbxUpAxis = enFbxUpAxisZ;		// FBX�̏�����B
	

	//AnimationClip animationClip[enAnimationClip_num];

	Animation m_animation;
	CAnimationEvent m_canimation;
	AnimationEventListener m_listener;
};

