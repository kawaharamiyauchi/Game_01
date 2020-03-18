#include "stdafx.h"
#include "LittleEnemy.h"
#include"GameObjectManager.h"
#include"Game.h"
#define pai 3.14159265

LittleEnemy::LittleEnemy()
{
	g_effect.m_sampleEffect = Effekseer::Effect::Create(g_effect.m_effekseerManager, (const EFK_CHAR*)L"Assets/effect/tm_damage.efk");
	m_skinModelRender =GameObjectManager::instance().NewGO<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/ModelData/LittleDragon_Blue.cmo");
	animationClip[enAnimationClip_idle].Load(L"Assets/animData/LBD_idle.tka", L"");
	animationClip[enAnimationClip_move].Load(L"Assets/animData/LBD_move.tka", L"");
	animationClip[enAnimationClip_damage].Load(L"Assets/animData/LBD_damage.tka", L"");
	animationClip[enAnimationClip_attack].Load(L"Assets/animData/LBD_attack.tka", L"");
	animationClip[enAnimationClip_die].Load(L"Assets/animData/LBD_die.tka", L"");

	animationClip[enAnimationClip_damage].SetLoopFlag(false);
	animationClip[enAnimationClip_die].SetLoopFlag(false);
	animationClip[enAnimationClip_attack].SetLoopFlag(false);
	animationClip[enAnimationClip_idle].SetLoopFlag(true);
	animationClip[enAnimationClip_move].SetLoopFlag(true);
	m_animation.Init(*m_skinModelRender->GetSkinModel(), animationClip, enAnimationClip_num);

	m_charaCon.Init(
		50.0f,
		100.0f,
		m_position
	);
	m_skeleton = m_skinModelRender->GetSkeleton();

	m_animation.AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);

		});
	for (int i = 0; i < 31; i++)
	{
		bonename[i] = m_skeleton->GetBone(i)->GetName();
		if (i == 30)
		{
			bonename[i] = L"end";
		}
	}
	m_sound[0].Init(L"Assets/sound/punch-middle2.wav");
	m_sound[1].Init(L"Assets/sound/sword-slash5.wav");
}


LittleEnemy::~LittleEnemy()
{
	GameObjectManager::instance().DeleteGO(m_skinModelRender);
}

void LittleEnemy::Update()
{
	auto m_game = Game::instance();
	if (!m_game->GetPauseFlag()) {
		if (m_game->m_player != nullptr) {
			ChangeState();
			Move();
			AnimationPlay();
			DamageEvent();
		}
		if (&m_ghost[P_attack00] != nullptr)
		{
			m_ghost[P_attack00].Release();
		}
		if (d_state == die)
		{
			m_charaCon.RemoveRigidBoby();
		}
		m_skinModelRender->SetPosition(m_position);
		m_skinModelRender->SetRotation(m_rotation);
		m_skinModelRender->SetScale(m_scale);
	}
}

void LittleEnemy::Render()
{
}

void LittleEnemy::Move()
{
	auto  m_game = Game::instance();
	if (!attackflag||d_state!=attack) {
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		if (m_game->m_player != nullptr) {
			diff.Set(m_game->m_player->GetPosition() - m_position);
		}
	}
	
	float angle = 0.0f;

	

	
	auto move = diff;
	
	move.Normalize();
	
	switch (d_state)
	{
	case normal:
		break;
	case run:
		moveSpeed = move * 10.0f;
		angle = atan2(move.x, move.z);
		break;
	case damage:
		moveSpeed = move*-10.0f;
		angle = atan2(move.x, move.z);
		break;
	case attack:
		moveSpeed = move*10.0f;
		angle = atan2(move.x, move.z);
		break;
	case die:
		/*angle = atan2(move.x, move.z);
		move *= 0.0f;*/
		break;
	}
	if (!m_charaCon.IsOnGround())
	{
		moveSpeed.y = -20.0f;
	}
	if (fabsf(moveSpeed.x*moveSpeed.z) > 0.01f) {
		m_rotation.SetRotation(CVector3::AxisY(), angle);
	}
	m_position =m_charaCon.Execute(1.0f,moveSpeed);
}

void LittleEnemy::AnimationPlay()
{
	switch (d_state)
	{
	case normal:
		m_animation.Play(enAnimationClip_idle,1.0f);
		m_animation.Update(0.05f);
		break;

	case run:
		m_animation.Play(enAnimationClip_move,1.0f);
		m_animation.Update(0.05f);
		break;
	case damage:
		m_animation.Play(enAnimationClip_damage, 0.0f);
		m_animation.Update(0.05f);
		break;
	case die:
		m_animation.Play(enAnimationClip_die, 0.0f);
		m_animation.Update(0.05f);
		break;
	case attack:
		m_animation.Play(enAnimationClip_attack, 0.0f);
		m_animation.Update(0.05f);
		break;

	default:
		return;
	}
}

void LittleEnemy::DamageEvent()
{
	
	if (d_state != die) {
		auto m_game = Game::instance();
		if (m_game->m_player != nullptr)
		{

			if (m_game->m_player->Getattack() > 0 && m_game->m_player->Getattack() < 15)
			{

				auto plbone = m_game->m_player->GetPlayerBone(23);
				auto plpower = m_game->m_player->GetPlayerInformation().AttackPower;
				CVector3 forward;
				forward.x = plbone->GetWorldMatrix().m[2][0];
				forward.y = plbone->GetWorldMatrix().m[2][1];
				forward.z = plbone->GetWorldMatrix().m[2][2];
				forward *= 60.0f;
				CVector3 bonePos;
				CQuaternion boneQua;
				bonePos.Set(
					plbone->GetWorldMatrix().m[3][0] + forward.x,
					plbone->GetWorldMatrix().m[3][1] + forward.y,
					plbone->GetWorldMatrix().m[3][2] + forward.z
				);
				boneQua.SetRotation(plbone->GetWorldMatrix());
				if (d_state != damage) {

					m_ghost[P_attack00].CreateBox(bonePos, boneQua, { 30.0f,5.0f, 150.0f });
				}
					g_physics.ContactTest(m_charaCon, [&](const btCollisionObject & contactObject)
						{
							if (m_ghost[P_attack00].IsSelf(contactObject))
							{
								//再生中のエフェクトを止める。
								g_effect.m_effekseerManager->StopEffect(g_effect.m_playEffectHandle);
								//再生。
								g_effect.m_playEffectHandle = g_effect.m_effekseerManager->Play(
									g_effect.m_sampleEffect,
									bonePos.x,
									bonePos.y,
									bonePos.z
								);
								m_sound[1].Play(false);
									m_enemyInfo.HP -= plpower;
									if (d_state != tailattack) {
										m_damageflag = true;
										m_ghost[P_attack00].Release();

									}
								

							}
						});
				
			}

		}

	}

}

void LittleEnemy::ChangeState()
{

	float angle;

	auto m_game = Game::instance();
	CVector3 headPos;

	CMatrix m_dragonWorld = m_skeleton->GetBone(22)->GetWorldMatrix();
	headPos.x = m_dragonWorld.m[2][0];
	headPos.y = m_dragonWorld.m[2][1];
	headPos.z = m_dragonWorld.m[2][2];
	auto forward = headPos;
	forward.y = 0.0f;
	auto pldiff =m_position- m_game->m_player->GetPosition();

	auto nor_diff = pldiff;
	nor_diff.Normalize();
	angle = acos(nor_diff.Dot(forward));
	auto eyerange = angle / (pai / 180.0f);
	if (d_state != die)
	{
		if (m_enemyInfo.HP < 0.01f)
		{
			SetEnemyState(die);
		}
	}
	if (m_damageflag)
	{
		SetEnemyState(damage);
		m_damageflag = false;
	}
	switch (d_state)
	{
	case normal:
		if (pldiff.Length() < 1200.0f&&fabsf(eyerange) < 60.0f)
		{
			SetEnemyState(run);
		}
		break;
	case damage:
		if (!m_animation.IsPlaying())
		{
			SetEnemyState(run);
		}
		break;
	case run:
		if (pldiff.Length() < 150.0f)
		{
			attackflag = true;
			SetEnemyState(attack);

		}
	case attack:
		if (!m_animation.IsPlaying())
		{
			SetEnemyState(run);
			attackflag = false;
		}
	default:
		break;
	}
}

void LittleEnemy::OnAnimationEvent(const wchar_t * clipName, const wchar_t * eventName)
{
	auto m_game = Game::instance();
	if (d_state == attack)
	{
		auto bone = m_skeleton->GetBone(22);
		CVector3 ghostPos;
		ghostPos.x = bone->GetWorldMatrix().m[3][0];
		ghostPos.y = bone->GetWorldMatrix().m[3][1];
		ghostPos.z = bone->GetWorldMatrix().m[3][2];

		(void)clipName;
		m_ghost[D_attack00].CreateSphere(ghostPos,CQuaternion::Identity(), 30.0f);
		g_physics.ContactTest(m_game->m_player->GetcharaCon(), [&](const btCollisionObject & contactObject)
			{
				if (m_ghost[D_attack00].IsSelf(contactObject))
				{
					//MessageBox(NULL, "attack", "attack", MB_OK);
					m_game->m_player->SetDamage(m_enemyInfo.attackPower);
					m_sound[0].Play(false);
				}
			});
	
	}
}
