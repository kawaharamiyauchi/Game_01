#pragma once
#include "SkinModelRender.h"
class Character:public IGameObject
{
public:
	enum CharacterType {
		PLAYER,
		ENEMY,
		ANOTHER,
		TYPENUM
	};
	Character();
	~Character();
	void Update() {}
	void Render() {}
	CVector3 GetPosition()
	{
		return m_position;
	}
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
private:
	CharacterType m_charaType;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
};

