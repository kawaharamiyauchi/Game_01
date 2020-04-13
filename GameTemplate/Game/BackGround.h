#pragma once
#include "IGameObject.h"
#include"character/CharacterController.h"
#include"physics/PhysicsStaticObject.h"
#include "SkinModelRender.h"


class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();
	
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	void SetStageType(int type)
	{
		m_stageType = type;
	}
	void LoadStage(int stagetype);
	
	/*CVector3 GetScale(int i)
	{
		return m_scale;
	}

	void SetScale(int i,CVector3 sca)
	{
		m_scale = sca;
	}*/

	SkinModel* GetskinModel()
	{
		return m_skinModelRender[MH_Ground]->GetSkinModel();
		//return m_skinModel;
	}

	void Update();

	void Render();
	
private:
	enum ModelType {
		MH_Ground,
		MH_Sky,
		MH_Limit,
		ModelTypenum
	};
	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale[ModelTypenum] = { CVector3::One() };
	CVector3 staticscale = { 1000.0f,20.0f,1000.0f };
	CQuaternion m_rotation = { CQuaternion::Identity() };
	CQuaternion add_2 ={ CQuaternion::Identity() };
	//SkinModel m_skinModel[2];
	SkinModelRender *m_skinModelRender[ModelTypenum] = { nullptr };
	PhysicsStaticObject m_physicsStaticObject;
	PhysicsStaticObject *m_limit;
	//PhysicsStaticObject m_limit;
	wchar_t*m_loadname =L".cmo";
	bool isLoad = false;
	int m_stageType =0;
};

