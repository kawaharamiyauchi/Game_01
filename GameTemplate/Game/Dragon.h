#pragma once
#include "IGameObject.h"
#include"math/Matrix.h";
class Dragon :public IGameObject
{
public:
	Dragon();
	~Dragon();

	/// <summary>
	/// ドラゴンの位置を取得
	/// </summary>
	///<returns>m_position ドラゴンの位置</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// ドラゴンの位置を設定
	/// </summary>
	/// <param name="pos">設定する位置座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ドラゴンの更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// ドラゴンの描画処理
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
	SkinModel m_model;		//スキンモデル
};

