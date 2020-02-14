#pragma once
#include"math/Vector.h"


class ICollider;

//���̏��B
struct RigidBodyInfo {

	RigidBodyInfo() :
		collider(NULL),
		mass(0.0f)
	{
		pos = CVector3::Zero();
		rot = CQuaternion::Identity();
		localInteria = CVector3::Zero();
	}
	CVector3 pos /*= CVector3::Zero()*/;			//���W�B
	CQuaternion rot /*= CQuaternion::Identity()*/;	//��]�B
	CVector3 sca;
	CVector3 localInteria;
	ICollider* collider/* = nullptr*/;				//�R���C�_�[�B
	float mass /*= 0.0f*/;						//���ʁB
	
};
//���̃N���X�B
class RigidBody
{
	btRigidBody*			rigidBody = nullptr;		//���́B
	btDefaultMotionState*	myMotionState = nullptr;	//���[�V�����X�e�[�g�B
public:

	~RigidBody();
	void Release();
	void Create(RigidBodyInfo& rbInfo);
	btRigidBody* GetBody()
	{
		return rigidBody;
	}
};

