#pragma once
#include "graphics/SkinModel.h"
class SkinModelRender:public IGameObject
{
public:
	SkinModelRender();
	~SkinModelRender();

	
	void Init(const wchar_t*filePath);

	/// <summary>
	/// シャドウキャスターのフラグを設定
	/// </summary>
	/// <param name="flag">シャドウキャスターフラグ</param>
	void SetShadowCasterFlag(bool flag)
	{
		m_skinModel.SetShadowCasterFlag(flag);
	}
	/// <summary>
	/// シャドウレシーバーのフラグを設定
	/// </summary>
	/// <param name="flag">シャドウレシーバーフラグ</param>
	void SetShadowRecieverFlag(bool flag)
	{
		m_skinModel.SetShadowReciever(flag);
	}
	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 拡大率を設定
	/// </summary>
	/// <param name="sca">拡大率</param>
	void SetScale(const CVector3& sca)
	{
		m_scale = sca;
	}
	/// <summary>
	/// スキンモデルを取得
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
	EnFbxUpAxis					m_enFbxUpAxis = enFbxUpAxisZ;		// FBXの上方向。
	

	//AnimationClip animationClip[enAnimationClip_num];

	Animation m_animation;
	CAnimationEvent m_canimation;
	AnimationEventListener m_listener;
};

