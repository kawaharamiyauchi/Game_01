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
	animationClip[enAnimationClip_idle].Load(L"Assets/animData/DragonBoar_idle.tka",L"enAnimationIdle");
	animationClip[enAnimationClip_idle].SetLoopFlag(true);
	animationClip[enAnimationClip_walk].Load(L"Assets/animData/DragonBoar_walk.tka",L"enAnimationWalk");
	animationClip[enAnimationClip_walk].SetLoopFlag(true);
	animationClip[enAnimationClip_attack].Load(L"Assets/animData/DragonBoar_attack.tka",L"enAnimationAttack");
	animationClip[enAnimationClip_attack].SetLoopFlag(false);
	animationClip[enAnimationClip_run].Load(L"Assets/animData/DragonBoar_run.tka",L"enAnimationRun");
	animationClip[enAnimationClip_run].SetLoopFlag(true);
	animationClip[enAnimationClip_scream].Load(L"Assets/animData/DragonBoar_scream.tka",L"num");
	animationClip[enAnimationClip_scream].SetLoopFlag(false);
	m_animation.Init(m_model, animationClip, enAnimationClip_num);
	m_model.SetActiveFlag(false);
	m_skeleton = &m_model.GetSkeleton();
	m_animation.AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName,eventName);
		});

	//m_aniCon->Init(&m_skeleton);
	for (int i = 0; i < 40; i++)
	{
			bonename[i] = m_skeleton->GetBone(i)->GetName();	
			if (i == 39)
			{
				bonename[i] = L"end";
			}
	}
	//auto m_bone[0] = m_skeleton->GetBone(22);
	//m_charaCon->Init(15.0f,20.0f, m_bone->GetWorldMatrix().v[3]);

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
		m_animation.Update(0.06f);
		break;
	case walk:
		m_animation.Play(enAnimationClip_walk, 1.0f);
		m_animation.Update(0.06f);
		break;
	case run:
		m_animation.Play(enAnimationClip_run, 1.0f);
		m_animation.Update(0.06f);
		break;
	case attack:
		m_animation.Play(enAnimationClip_attack,1.0f);
		m_animation.Update(0.03f);
		break;
	default:
		return;
	}
	
}

void Dragon::OnAnimationEvent(const wchar_t * clipName, const wchar_t * eventName)
{
	auto m_game = Game::instance();
	
	
	m_collisionScale.Set(200.0f, 200.0f, 200.0f);
	auto bone = m_skeleton->GetBone(11);
	m_collisionPosition.x = bone->GetWorldMatrix().m[3][0];
	m_collisionPosition.y = bone->GetWorldMatrix().m[3][1];
	m_collisionPosition.z = bone->GetWorldMatrix().m[3][2];
	//m_collisionPosition = bone->GetWorldMatrix().v[3];
	CVector3 attackpoint;
	attackpoint.Set(m_collisionPosition);
	(void)clipName;
	m_ghost.CreateBox(attackpoint, m_rotation,m_collisionScale);
	g_physics.ContactTest(m_game->m_player->GetcharaCon(), [&](const btCollisionObject & contactObject)
		{
			if (m_ghost.IsSelf(contactObject))
			{
				MessageBox(NULL, "attack", "attack", MB_OK);

			}
		});


}
void Dragon::Move()
{
	auto m_game = Game::instance();
	diff.Set(m_game->m_player->GetPosition() - m_position);
	auto move = diff;
	move.Normalize();
	switch(d_state)

	{
	case normal:
		break;
	case walk:
		if (m_model.GetActiveFlag() == true)
		{
			if (diff.Length() > 10.0f)
			{
				m_position += move * 10.0f;
			}
			

			float angle = atan2(move.x, move.z);
			m_rotation.SetRotation(CVector3::AxisY(), angle);

		}

		break;
	case run:
		if (m_model.GetActiveFlag() == true)
		{
			if (diff.Length() > 20.0f)
			{
				m_position += move * 20.0f;
			}
			

			 angle = atan2(move.x, move.z);
			m_rotation.SetRotation(CVector3::AxisY(), angle);

		}
		break;
	case attack:
		break;
	}
}

void Dragon::Update()
{
	

	m_ghost.Release();
	
	m_timer ++ ;
	if (g_pad[0].IsTrigger(enButtonY))
	{
		if (GetDragonState() == normal)
		{
			SetDragonState(walk);
		}
		else if (GetDragonState() == walk)
		{
			SetDragonState(run);
		}
		else if (GetDragonState() == run)
		{
			SetDragonState(attack);
		}
		else if (m_animation.IsPlaying() == false)
		{
			SetDragonState(normal);
		}

	}

	a += 0.1f;
	
	
	if (g_pad[0].IsTrigger(enButtonA))
	{
		if (m_model.GetActiveFlag() == false) {
			m_model.SetActiveFlag(true);
		}
		else m_model.SetActiveFlag(false);
	}


	
	Move();
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
