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
	/// シャドウキャスターのフラグを設定
	/// </summary>
	/// <param name="flag">シャドウキャスターフラグ</param>
	void SetShadowCasterFlag(bool flag)
	{
		m_isCasterFlag = flag;
		m_skinModel.SetShadowCasterFlag(flag);
	}
	/// <summary>
	/// シャドウレシーバーのフラグを設定
	/// </summary>
	/// <param name="flag">シャドウレシーバーフラグ</param>
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
	 /// <summary>
	 /// スケルトンを取得
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
	/// 自己発光カラーを設定
	/// </summary>
	/// <param name="color">カラー</param>
	void SetGlowColor(CVector3 color)
	{

		m_skinModel.SetGlowColor(color);
	}
	/// <summary>
	/// 鏡面反射光を設定。
	/// </summary>
	/// <param name="spec">スペキュラの絞り</param>
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
	EnFbxUpAxis					m_enFbxUpAxis = enFbxUpAxisZ;		// FBXの上方向。
	bool m_isRecieverFlag = false;
	bool m_isCasterFlag = false;
	
};

