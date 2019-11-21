#pragma once
#include "PhysicsObjectBase.h"
class GhostObject:public PhysicsObjectBase
{
public:
	
	~GhostObject()
	{
		Release();
	}

	void Release();

	bool IsSelf(const btCollisionObject& ghost)const
	{
		return &ghost == &m_ghostObject;
	}
private:
	void CreateCommon(CVector3 pos, CQuaternion rot)override;

private:
	bool  m_isRegistPhysicsWorld =false; //�������[���h�ɓo�^���Ă��邩�ǂ����̃t���O
	btGhostObject m_ghostObject;		 //�S�[�X�g
	
};

