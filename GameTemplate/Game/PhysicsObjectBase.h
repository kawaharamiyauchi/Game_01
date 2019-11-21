#pragma once
#include "physics/Physics.h"


/// <summary>
/// ボックスコライダークラス
/// </summary>
class CBoxCollider :public ICollider
{
public:
	CBoxCollider() :shape(NULL)
	{	
	}
	~CBoxCollider()
	{
		delete shape;
	}
	void Create(const CVector3&size)
	{
		shape = new btBoxShape(btVector3(size.x*0.5f, size.y*0.5f, size.z*0.5f));
		/*shape =new btBoxShape()*/
	}
	btCollisionShape*GetBody()const override
	{
		return shape;
	}
private:
	btBoxShape*		shape;
};
/// <summary>
/// カプセルコライダークラス
/// </summary>
class CCapsuleCollider :public ICollider
{
public:
	void Create(float radius, float height)
	{
		m_shape = std::make_unique<btCapsuleShape>(radius,height);
		m_radius = radius;
		m_height = height;
	}

	btCollisionShape*GetBody()const override
	{
		return m_shape.get();
	}

	float GetRadius()const
	{
		return m_radius;
	}
	float GetHeight()const
	{
		return m_height;
	}
private:
	std::unique_ptr<btCapsuleShape>	m_shape;
	float m_radius = 0.0f;
	float m_height = 0.0f;
};

class CSphereCollider:public ICollider
{
public:
	CSphereCollider():shape(NULL)
	{

	}
	~CSphereCollider()
	{
		delete shape;
	}
	void Create(const float radius)
	{
		shape = new btSphereShape(radius);
	}
	btCollisionShape*GetBody()const override
	{
		return shape;
	}
private:
	btSphereShape*		shape;
};
class PhysicsObjectBase
{
public:
		/*!
		* @brief	ゴーストオブジェクトを解放。
		*@detail
		* 明示的なタイミングでオブジェクトを削除したい場合に呼び出してください。
		*/
		virtual void Release() = 0;
	private:
		/*!
		* @brief	静的物理オブジェクト作成処理の共通処理。
		*/
		virtual void CreateCommon(CVector3 pos, CQuaternion rot) = 0;
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		PhysicsObjectBase()
		{
		}
		/*!
		 *@brief	デストラクタ。
		 */
		virtual ~PhysicsObjectBase()
		{

		}
		/*!
		 * @brief	ボックス形状のゴーストオブジェクトを作成。
		 *@param[in]	pos			座標。
		 *@param[in]	rot			回転。
		 *@param[in]	size		サイズ。
		 */
		void CreateBox(CVector3 pos, CQuaternion rot, CVector3 size);
		/*!
		 * @brief	カプセル形状のゴーストオブジェクトを作成。
		 *@param[in]	pos			座標。
		 *@param[in]	rot			回転。
		 *@param[in]	radius		カプセルの半径。
		 *@param[in]	height		カプセルの高さ。
		 */
		void CreateCapsule(CVector3 pos, CQuaternion rot, float radius, float height);
		/*!
		* @brief	球体形状のゴーストオブジェクトを作成。
		*@param[in]	pos			座標。
		*@param[in]	rot			回転。
		*@param[in]	radius		球体の半径。
		*/
		void CreateSphere(CVector3 pos, CQuaternion rot, float radius);
		

protected:
		std::unique_ptr<ICollider> m_collider;	//!<コライダー。

};

