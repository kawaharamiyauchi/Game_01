#pragma once
#include "graphics/SkinModel.h"
class SkinModelRender:public IGameObject
{
public:
	SkinModelRender();
	~SkinModelRender();

	
	void Init(const wchar_t*filePath,EnFbxUpAxis fbxUpaxis);

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
	const SkinModel& GetSkinModel() const
	{
		return m_skinModel;
	}
	void Update();
	void Render();
private:
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	EnFbxUpAxis					m_enFbxUpAxis = enFbxUpAxisZ;		// FBX�̏�����B
	SkinModel m_skinModel;
};

