#pragma once
#include "GameObjectManager.h"
#include "IGameObject.h"
#include "Sprite.h"
class SpriteRender :public IGameObject
{
public:
	SpriteRender()
	{
	}
	~SpriteRender();
	
	void Init(const wchar_t*FileName, float w, float h);
	void SetPosition(CVector3& pos)
	{
		m_position = pos;
	}

	void SetRotation(CQuaternion& rot)
	{
		m_rotation = rot;
	}

	void SetScale(CVector3& sca)
	{
		m_scale = sca;
	}

	void SetPivot(const CVector2& piv)
	{
		m_pivot = piv;
	}
	void SetAlpha(float alpha)
	{
		m_sprite.SetAlpha(alpha);
	}
	CVector3 GetPosition()const
	{
		return m_position;
	}
	CVector2 Get2DPosition()const
	{
		CVector2 pos = { m_position.x,m_position.y };
		return pos;
	}
	bool IsRender()const
	{
		return IsActive;
	}
	void Update();
	
	void Render();
	void PostRender()override;
	void SetIsActive(bool flag)
	{
		IsActive = flag;
	}
	Sprite m_sprite;
private:
	
	bool IsActive = true;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::CVector3::One();
	CVector2 m_pivot = {0.5f,0.5f};

};

