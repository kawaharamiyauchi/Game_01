#include "stdafx.h"
#include "physics/Physics.h"
#include "Physics/RigidBody.h"


PhysicsWorld g_physics;

struct MyContactResultCallback : public btCollisionWorld::ContactResultCallback {
	using ContantTestCallback = function<void(const btCollisionObject& contactCollisionObject)>;
	ContantTestCallback  m_cb;
	btCollisionObject* m_me = nullptr;
	virtual	btScalar	addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) override
	{
		if (m_me == colObj0Wrap->getCollisionObject()) {
			m_cb(*colObj1Wrap->getCollisionObject());
		}
		return 0.0f;
	}
};
PhysicsWorld::~PhysicsWorld()
{
	Release();
}
void PhysicsWorld::Release()
{
	/*delete dynamicWorld;
	delete constraintSolver;
	delete overlappingPairCache;
	delete collisionDispatcher;
	delete collisionConfig;*/
	m_dynamicWorld.reset();
	m_constraintSolver.reset();
	m_constraintSolver.reset();
	m_overlappingPairCache.reset();
	m_collisionDispatcher.reset();
	m_collisionConfig.reset();
	/*dynamicWorld = nullptr;
	constraintSolver = nullptr;
	overlappingPairCache = nullptr;
	collisionDispatcher = nullptr;
	collisionConfig = nullptr;*/
}

void PhysicsWorld::Init()
{


	Release();

	m_dw.Prepare();
	////物理エンジンを初期化。
	/////collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	//collisionConfig = new btDefaultCollisionConfiguration();

	/////use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	//collisionDispatcher = new	btCollisionDispatcher(collisionConfig);

	/////btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	//overlappingPairCache = new btDbvtBroadphase();

	/////the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	//constraintSolver = new btSequentialImpulseConstraintSolver;

	//dynamicWorld = new btDiscreteDynamicsWorld(
	//	collisionDispatcher,
	//	overlappingPairCache,
	//	constraintSolver,
	//	collisionConfig
	//	);

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	m_collisionConfig = make_unique<btDefaultCollisionConfiguration>();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_collisionDispatcher = make_unique<btCollisionDispatcher>(m_collisionConfig.get());

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	m_overlappingPairCache = make_unique<btDbvtBroadphase>();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	m_constraintSolver = make_unique<btSequentialImpulseConstraintSolver>();
	m_dynamicWorld = make_unique<btDiscreteDynamicsWorld>(
		m_collisionDispatcher.get(),
		m_overlappingPairCache.get(),
		m_constraintSolver.get(),
		m_collisionConfig.get()
		);

	m_dynamicWorld->setGravity(btVector3(0, -10, 0));

	//ここにデバッグドロー設定スル。
	m_dynamicWorld.get()->setDebugDrawer(&m_dw);
}
void PhysicsWorld::Update()
{
	m_dynamicWorld->stepSimulation(1.0f/60.0f);
}
void PhysicsWorld::AddRigidBody(RigidBody& rb)
{
	m_dynamicWorld->addRigidBody(rb.GetBody());
}
void PhysicsWorld::RemoveRigidBody(RigidBody& rb)
{
	m_dynamicWorld->removeRigidBody(rb.GetBody());
}

void PhysicsWorld::ContactTest(btCollisionObject * colObj, std::function<void(const btCollisionObject&contactCollisionObject)> cb)
{
	MyContactResultCallback myContactResultCallback;
	myContactResultCallback.m_cb = cb;
	myContactResultCallback.m_me = colObj;
	m_dynamicWorld->contactTest(colObj, myContactResultCallback);
}
void PhysicsWorld::ContactTest(RigidBody & rb, std::function<void(const btCollisionObject&contactCollisionObject)> cb)
{
	ContactTest(rb.GetBody(), cb);
}
void PhysicsWorld::ContactTest(
	CharacterController& charaCon,
	std::function<void(const btCollisionObject& contactCollisionObject)> cb
)
{
	ContactTest(*charaCon.GetRigidBody(), cb);
}

void PhysicsWorld::DebugDraw()
{
	//デバッグドロー
	m_dw.Context();

	m_dynamicWorld.get()->debugDrawWorld();
}