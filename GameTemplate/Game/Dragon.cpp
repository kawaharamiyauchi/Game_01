#include "stdafx.h"
#include "Dragon.h"
#include "Game.h"

Dragon::Dragon()
{
	
	animationClip[enAnimationClip_idle].Load(L"Assets/animData/DragonBoar_idle.tka");
	animationClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animation.Init(m_model, animationClip, enAnimationClip_num);
	
	m_position.Set(0.0f, 50.0f, 100.0f);
	m_scale *= 5.0f;
	m_model.Init(L"Assets/modelData/DragonBoar.cmo");
	
	m_skeleton.Load(L"Assets/modelData/DragonBoar.tks");
	
	for (int i = 0; i < 40; i++)
	{
			bonename[i] = m_skeleton.GetBone(i)->GetName();	
	}
	
	m_animation.Play(enAnimationClip_idle, 1.0f);
}


Dragon::~Dragon()
{
}

void Dragon::Update()
{
	m_animation.Update(1.0f);
	
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Dragon::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
