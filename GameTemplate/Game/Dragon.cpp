#include "stdafx.h"
#include "Dragon.h"
#include "Game.h"
#include "Player.h"
Dragon::Dragon()
{	

	m_position.Set(0.0f, 50.0f, 100.0f);
	m_scale *= 1.0f;
	m_model.Init(L"Assets/modelData/DragonBoar.cmo");
	animationClip[enAnimationClip_idle].Load(L"Assets/animData/DragonBoar_idle.tka");
	animationClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animation.Init(m_model, animationClip, enAnimationClip_num);
	m_model.SetActiveFlag(false);
	//m_skeleton.Load(L"Assets/modelData/DragonBoar.tks");
	
	/*for (int i = 0; i < 40; i++)
	{
			bonename[i] = m_skeleton.GetBone(i)->GetName();	
			if (i == 39)
			{
				bonename[i] = L"end";
			}
	}*/
	
	m_animation.Play(enAnimationClip_idle, 1.0f);



}


Dragon::~Dragon()
{
}

void Dragon::Update()
{

	a += 0.1f;
	m_animation.Update(0.03f);
	/*m_bone[1].MakeRotationY(a);
	m_skeleton.GetBone(1)->SetWorldMatrix(m_bone[1]);*/
	auto m_search = m_aniCon.GetAnimClip();
	if (g_pad[0].IsTrigger(enButtonA))
	{
		if (m_model.GetActiveFlag() == false) {
			m_model.SetActiveFlag(true);
		}
		else m_model.SetActiveFlag(false);
	}
	auto m_game = Game::instance();
	diff.Set(m_game->m_player->GetPosition() - m_position);
	
	auto move = diff;
	move.Normalize();
	if (m_model.GetActiveFlag() == true)
	{
		if (diff.Length() > 20.0f)
		{
			m_position += move * 20.0f;
		}
		m_aniCon.GetAnimClip();

		float angle = atan2(diff.x, diff.z);
		//atanが返してくる角度はラジアン単位なので
		//SetRotationDegではなくSetRotationを使用する。
		m_rotation.SetRotation(CVector3::AxisY(), angle);
		
	}
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Dragon::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
