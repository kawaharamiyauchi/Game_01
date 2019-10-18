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
	~SpriteRender()
	{
		//m_sprite.~Sprite();
	}
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

	void Update() override final;
	
	void Render();
	Sprite m_sprite;
private:
	

	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::CVector3::One();
	CVector2 m_pivot = {0.5f,0.5f};

};

