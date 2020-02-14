#include "stdafx.h"
#include "PhysicsObjectBase.h"
using namespace std;
void PhysicsObjectBase::CreateBox(CVector3 pos, CQuaternion rot, CVector3 size)
{
	Release();
	auto boxCollider = make_unique<CBoxCollider>();
	boxCollider->Create(size);
	m_collider = move(boxCollider);
	CreateCommon(pos, rot);
}
void PhysicsObjectBase::CreateCapsule(CVector3 pos, CQuaternion rot, float radius, float height)
{
	Release();
	auto capusuleCollider = make_unique<CCapsuleCollider>();
	capusuleCollider->Create(radius, height);
	m_collider = move(capusuleCollider);
	CreateCommon(pos, rot);
}

void PhysicsObjectBase::CreateSphere(CVector3 pos, CQuaternion rot, float radius)
{
	Release();
	auto sphereCollider = make_unique<CSphereCollider>();
	sphereCollider->Create(radius);
	m_collider = move(sphereCollider);
	CreateCommon(pos, rot);
}

//void PhysicsObjectBase::CreateMesh(CVector3 pos, CQuaternion rot, const CSkinModelData& skinModelData)
//{
//	Release();
//	auto meshCollider = make_unique<CMeshCollider>();
//	meshCollider->CreateFromSkinModel(skinModelData, nullptr);
//	m_collider = move(meshCollider);
//	CreateCommon(pos, rot);
//}
//void PhysicsObjectBase::CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, prefab::CSkinModelRender* skinModelRender)
//{
//	CreateMesh(pos, rot, scale, skinModelRender->GetSkinModel());
//}
//void PhysicsObjectBase::CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, const CSkinModel& skinModel)
//{
//	Release();
//	CMatrix mScale;
//	mScale.MakeScaling(scale);
//	auto meshCollider = make_unique<CMeshCollider>();
//	meshCollider->CreateFromSkinModel(skinModel, &mScale);
//	m_collider = move(meshCollider);
//	CreateCommon(
//		pos,
//		rot
//	);
//
//}