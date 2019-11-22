#include "stdafx.h"
#include "GhostObject.h"


void GhostObject::Release()
{
	if (m_isRegistPhysicsWorld == true) {
	g_physics.RemoveCollisionObject(m_ghostObject);
		m_isRegistPhysicsWorld = false;
	}
	
}

void GhostObject::CreateCommon(CVector3 pos, CQuaternion rot)
{
	m_ghostObject.setCollisionShape(m_collider->GetBody());
	btTransform btTrans;
	btTrans.setOrigin({ pos.x, pos.y, pos.z });
	btTrans.setRotation({ rot.x, rot.y, rot.z, rot.w });
	m_ghostObject.setWorldTransform(btTrans);
	m_ghostObject.setCollisionFlags(m_ghostObject.getCollisionFlags()
		| btCollisionObject::CF_NO_CONTACT_RESPONSE);

	//ï®óùÉGÉìÉWÉìÇ…ìoò^ÅB
	g_physics.AddCollisionObject(m_ghostObject);
	m_isRegistPhysicsWorld = true;
}