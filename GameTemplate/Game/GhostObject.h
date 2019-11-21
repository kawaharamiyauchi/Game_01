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
	bool  m_isRegistPhysicsWorld =false; //物理ワールドに登録しているかどうかのフラグ
	btGhostObject m_ghostObject;		 //ゴースト
	
};

