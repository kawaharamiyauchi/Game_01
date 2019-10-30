#include "stdafx.h"
#include "Dragon.h"
#include "Game.h"
#include "Player.h"
Dragon::Dragon()
{	
	d_state = normal;
	m_position.Set(0.0f, 50.0f, 100.0f);
	m_scale *= 2.5f;
	m_model.Init(L"Assets/modelData/DragonBoar.cmo");
	animationClip[enAnimationClip_idle].Load(L"Assets/animData/DragonBoar_idle.tka");
	animationClip[enAnimationClip_idle].SetLoopFlag(true);
	animationClip[enAnimationClip_walk].Load(L"Assets/animData/DragonBoar_walk.tka");
	animationClip[enAnimationClip_walk].SetLoopFlag(true);
	animationClip[enAnimationClip_attack].Load(L"Assets/animData/DragonBoar_attack.tka");
	animationClip[enAnimationClip_attack].SetLoopFlag(false);
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
	

}


Dragon::~Dragon()
{
}

void Dragon::AnimationPlay()
{
	switch (d_state)
	{
	case normal:
		m_animation.Play(enAnimationClip_idle, 1.0f);
		break;
	case walk:
		m_animation.Play(enAnimationClip_walk, 1.0f);
		break;
	case attack:
		m_animation.Play(enAnimationClip_attack,1.0f);
		break;
	default:
		return;
	}
	m_animation.Update(0.03f);
}

void Dragon::Update()
{
	m_timer ++ ;
	if (g_pad[0].IsTrigger(enButtonY))
	{
		if (GetDragonState() == normal)
		{
			SetDragonState(walk);
		}
		else if (GetDragonState() == walk)
		{
			SetDragonState(attack);
		}
		else if (m_animation.IsPlaying() == false)
		{
			SetDragonState(normal);
		}
	}
	a += 0.1f;
	
	/*m_bone[1].MakeRotationY(a);
	m_skeleton.GetBone(1)->SetWorldMatrix(m_bone[1]);*/
	//auto m_search = m_aniCon.GetKeyFrame();
	if (g_pad[0].IsTrigger(enButtonA))
	{
		if (m_model.GetActiveFlag() == false) {
			m_model.SetActiveFlag(true);
		}
		else m_model.SetActiveFlag(false);
	}

	auto m_game = Game::instance();
	if (m_timer > 30.0f) {
		diff.Set(m_game->m_player->GetPosition() - m_position);
		m_timer = 0;
	}

	auto move = diff;
	move.Normalize();
	if (m_model.GetActiveFlag() == true)
	{
		if (diff.Length() > 20.0f)
		{
			m_position += move * 20.0f;
		}
		m_aniCon.GetAnimClip();

		float angle = atan2(move.x, move.z);
		m_rotation.SetRotation(CVector3::AxisY(), angle);
		
	}
	AnimationPlay();
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Dragon::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
