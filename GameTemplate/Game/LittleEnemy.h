#pragma once
#include"SkinModelRender.h"

class LittleEnemy:public IGameObject
{
public:
	LittleEnemy();
	~LittleEnemy();
	enum EnemyType
	{
		blue
	};
	struct littleEnemyInformation
	{
		EnemyType Type = blue;
		float HP = 0.0f;

		float attackPower = 10.0f;


	};
	
	void Update();
	void Render();


	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()const
	{
		return m_position;
	}
private:
	SkinModelRender *m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();

	littleEnemyInformation m_enemyInfo;
};

