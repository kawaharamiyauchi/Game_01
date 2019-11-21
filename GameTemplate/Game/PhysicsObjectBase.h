#pragma once
#include "physics/Physics.h"


/// <summary>
/// �{�b�N�X�R���C�_�[�N���X
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
/// �J�v�Z���R���C�_�[�N���X
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
		* @brief	�S�[�X�g�I�u�W�F�N�g������B
		*@detail
		* �����I�ȃ^�C�~���O�ŃI�u�W�F�N�g���폜�������ꍇ�ɌĂяo���Ă��������B
		*/
		virtual void Release() = 0;
	private:
		/*!
		* @brief	�ÓI�����I�u�W�F�N�g�쐬�����̋��ʏ����B
		*/
		virtual void CreateCommon(CVector3 pos, CQuaternion rot) = 0;
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		PhysicsObjectBase()
		{
		}
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		virtual ~PhysicsObjectBase()
		{

		}
		/*!
		 * @brief	�{�b�N�X�`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		 *@param[in]	pos			���W�B
		 *@param[in]	rot			��]�B
		 *@param[in]	size		�T�C�Y�B
		 */
		void CreateBox(CVector3 pos, CQuaternion rot, CVector3 size);
		/*!
		 * @brief	�J�v�Z���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		 *@param[in]	pos			���W�B
		 *@param[in]	rot			��]�B
		 *@param[in]	radius		�J�v�Z���̔��a�B
		 *@param[in]	height		�J�v�Z���̍����B
		 */
		void CreateCapsule(CVector3 pos, CQuaternion rot, float radius, float height);
		/*!
		* @brief	���̌`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		*@param[in]	pos			���W�B
		*@param[in]	rot			��]�B
		*@param[in]	radius		���̂̔��a�B
		*/
		void CreateSphere(CVector3 pos, CQuaternion rot, float radius);
		

protected:
		std::unique_ptr<ICollider> m_collider;	//!<�R���C�_�[�B

};

