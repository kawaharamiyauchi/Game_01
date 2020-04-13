#pragma once
#include "graphics/SkinModel.h"
#include"IGameObject.h"
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
		m_isCasterFlag = flag;
		m_skinModel.SetShadowCasterFlag(flag);
	}
	/// <summary>
	/// �V���h�E���V�[�o�[�̃t���O��ݒ�
	/// </summary>
	/// <param name="flag">�V���h�E���V�[�o�[�t���O</param>
	void SetShadowRecieverFlag(bool flag)
	{
		m_isRecieverFlag = flag;
		m_skinModel.SetShadowReciever(flag);
	}
	void SetShadowCasterUpdate();
	
	void SetActiveFlag(bool flag)
	{
		m_skinModel.SetActiveFlag(flag);
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
	 /// <summary>
	 /// �X�P���g�����擾
	 /// </summary>
	 /// <returns></returns>
	Skeleton* GetSkeleton()
	{
		return &m_skinModel.GetSkeleton();
	}
	CMatrix* GetWorldMatrix()
	{
		return &m_skinModel.GetWorldMatrix();
	}
	void Update();
	void Render();
	
	/// <summary>
	/// ���Ȕ����J���[��ݒ�
	/// </summary>
	/// <param name="color">�J���[</param>
	void SetGlowColor(CVector3 color)
	{

		m_skinModel.SetGlowColor(color);
	}
	/// <summary>
	/// ���ʔ��ˌ���ݒ�B
	/// </summary>
	/// <param name="spec">�X�y�L�����̍i��</param>
	void SetSpecPow(float spec)
	{
		m_skinModel.SetSpecPow(spec);
	}
private:
	SkinModel m_skinModel;
	EnRenderMode m_renderMode = enRenderMode_Normal;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	EnFbxUpAxis					m_enFbxUpAxis = enFbxUpAxisZ;		// FBX�̏�����B
	bool m_isRecieverFlag = false;
	bool m_isCasterFlag = false;
	
};

