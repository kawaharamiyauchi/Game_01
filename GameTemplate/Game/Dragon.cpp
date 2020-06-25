#include "stdafx.h"
#include "Dragon.h"
#include "Game.h"
#include "Player.h"
#include"QuestManager.h"
#include "BackGround.h"

#define pai 3.14159265f
const CVector3 ATTACK_SCALE = { 100.0f, 200.0f, 300.0f };

Dragon::Dragon()
{	

	//サンプルのエフェクトをロードする。
	g_effect.m_sampleEffect[GameObjectManager::EffectType::damage] = Effekseer::Effect::Create(g_effect.m_effekseerManager, (const EFK_CHAR*)L"Assets/effect/tm_damage.efk");
	d_state = normal;
	//m_position.Set(0.0f,0.0f, 1000.0f);
	m_scale *= 2.5f;
	
	m_skinModelRender = GameObjectManager::instance().NewGO<SkinModelRender>();
	
	m_skinModelRender->Init(L"Assets/modelData/DragonBoar.cmo");
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowRecieverFlag(false);
	//m_skinModelRender->SetActiveFlag(false);
	//m_model.Init(L"Assets/modelData/DragonBoar.cmo");
	animationClip[enAnimationClip_idle].Load(L"Assets/animData/DragonBoar_idle.tka",L"enAnimationIdle");
	animationClip[enAnimationClip_idle].SetLoopFlag(true);
	animationClip[enAnimationClip_walk].Load(L"Assets/animData/DragonBoar_walk.tka",L"enAnimationWalk");
	animationClip[enAnimationClip_walk].SetLoopFlag(true);
	animationClip[enAnimationClip_attack].Load(L"Assets/animData/DragonBoar_attack.tka",L"enAnimationAttack");
	animationClip[enAnimationClip_attack].SetLoopFlag(false);
	animationClip[enAnimationClip_hornAttack].Load(L"Assets/animData/DragonBoar_HornAttack.tka", L"enAnimationHornAttack");
	animationClip[enAnimationClip_hornAttack].SetLoopFlag(false);
	animationClip[enAnimationClip_tailAttack].Load(L"Assets/animData/DragonBoar_TailAttack.tka", L"enAnimationTailAttack");
	animationClip[enAnimationClip_tailAttack].SetLoopFlag(false);
	animationClip[enAnimationClip_getHit].Load(L"Assets/animData/DragonBoar_GetHit.tka", L"enAnimationDamage");
	animationClip[enAnimationClip_getHit].SetLoopFlag(false);
	animationClip[enAnimationClip_run].Load(L"Assets/animData/DragonBoar_run.tka",L"enAnimationRun");
	animationClip[enAnimationClip_run].SetLoopFlag(true);
	animationClip[enAnimationClip_scream].Load(L"Assets/animData/DragonBoar_scream.tka",L"num");
	animationClip[enAnimationClip_scream].SetLoopFlag(false);
	animationClip[enAnimationClip_die].Load(L"Assets/animData/DragonBoar_Die.tka", L"num");
	animationClip[enAnimationClip_die].SetLoopFlag(false);
	m_animation.Init(*m_skinModelRender->GetSkinModel(), animationClip, enAnimationClip_num);
	//m_animation.Init(m_model, animationClip, enAnimationClip_num);
	m_skeleton = m_skinModelRender->GetSkeleton();
	//m_skeleton = &m_model.GetSkeleton();
	m_animation.AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
			OnAnimationEvent(clipName, eventName);
		
	});
	
		m_charaCon[Head].Init(
			90.0f,
			80.0f,
			m_charaConPos[Head]
		);
	/*ColliderInit(
		Head,
		90.0f,
		80.0f,
		m_charaConPos[Head]
	);*/
		m_charaCon[UpBody].Init(
			90.0f,
			100.0f,
			m_charaConPos[UpBody]
		);
		m_charaCon[Body].Init(
			90.0f,
			80.0f,
			m_charaConPos[Body]
		);
		m_charaCon[Tail].Init(
			40.0f,
			50.0f,
			m_charaConPos[Tail]
		);
	//m_charaCon.RemoveRigidBoby();
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
	m_sound[screamvoice].Init(L"Assets/sound/DragonScream.wav");
	m_sound[gethit].Init(L"Assets/sound/sword-slash5.wav");
}


Dragon::~Dragon()
{
	GameObjectManager::instance().DeleteGO(m_skinModelRender);
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
	case damage:
		m_animation.Play(enAnimationClip_getHit, 1.0f);
		m_animation.Update(0.06f);
		break;
	case die:
		m_animation.Play(enAnimationClip_die, 1.0f);
		m_animation.Update(0.015f);
		break;
	case escape:
		m_animation.Play(enAnimationClip_run, 1.0f);
		m_animation.Update(0.06f);
		break;
	case hornattack:
		if (h_attackflag)
		{
			m_animation.Play(enAnimationClip_hornAttack, 1.0f);
			m_animation.Update(0.06f);
			break;
		}
		else m_animation.Play(enAnimationClip_run, 1.0f);
			 m_animation.Update(0.06f);
			 break;
	case tailattack:
		m_animation.Play(enAnimationClip_tailAttack, 1.0f);
		m_animation.Update(0.08f);
		break;
	case scream:
		m_animation.Play(enAnimationClip_scream, 1.0f);
		m_animation.Update(0.03f);
		break;
	default:
		return;
	}
	
}

void Dragon::OnAnimationEvent(const wchar_t * clipName, const wchar_t * eventName)
{
	auto m_game = Game::instance();
	
	if (d_state ==attack)
	{
		m_collisionScale.Set(ATTACK_SCALE);
		auto bone = m_skeleton->GetBone(11);
		m_collisionPosition.x = bone->GetWorldMatrix().m[3][0];
		m_collisionPosition.y = bone->GetWorldMatrix().m[3][1];
		m_collisionPosition.z = bone->GetWorldMatrix().m[3][2];
		//m_collisionPosition = bone->GetWorldMatrix().v[3];
		CVector3 attackpoint;
		attackpoint.Set(m_collisionPosition);
		
		(void)clipName;
		m_ghost[D_attack00].CreateBox(attackpoint, m_rotation, m_collisionScale);
		
		g_physics.ContactTest(m_game->m_player->GetcharaCon(), [&](const btCollisionObject & contactObject)
			{
				if (m_ghost[D_attack00].IsSelf(contactObject))
				{
					m_game->m_player->SetDamageFlag(true);
				}
		});

	}
	else if (d_state == hornattack)
	{
		m_collisionScale.Set(400.0f, 400.0f, 500.0f);
		auto bone = m_skeleton->GetBone(3);
		m_collisionPosition.x = bone->GetWorldMatrix().m[3][0];
		m_collisionPosition.y = bone->GetWorldMatrix().m[3][1];
		m_collisionPosition.z = bone->GetWorldMatrix().m[3][2];
		//m_collisionPosition = bone->GetWorldMatrix().v[3];
		CVector3 attackpoint;
		attackpoint.Set(m_collisionPosition);

		(void)clipName;
		m_ghost[D_attack00].CreateBox(attackpoint, m_rotation, m_collisionScale);

		g_physics.ContactTest(m_game->m_player->GetcharaCon(), [&](const btCollisionObject & contactObject)
			{
				if (m_ghost[D_attack00].IsSelf(contactObject))
				{
					//MessageBox(NULL, "attack", "attack", MB_OK);
					m_game->m_player->SetDamageFlag(true);
					m_game->m_player->SetDamage(20.0f);
				}
			});
		}
	else if (d_state == tailattack)
	{
		m_collisionScale.Set(500.0f, 50.0f, 650.0f);
		auto bone = m_skeleton->GetBone(25);
		m_collisionPosition.x = bone->GetWorldMatrix().m[3][0];
		m_collisionPosition.y = bone->GetWorldMatrix().m[3][1];
		m_collisionPosition.z = bone->GetWorldMatrix().m[3][2];
		//m_collisionPosition = bone->GetWorldMatrix().v[3];
		CVector3 attackpoint;
		attackpoint.Set(m_position);
		(void)clipName;
		m_ghost[D_attack00].CreateBox(attackpoint, m_rotation, m_collisionScale);
		
		g_physics.ContactTest(m_game->m_player->GetcharaCon(), [&](const btCollisionObject & contactObject)
			{
				if (m_ghost[D_attack00].IsSelf(contactObject))
				{
					
					m_game->m_player->SetDamageFlag(true);
					m_game->m_player->SetDamage(20.0f);
				}
			});
		
	}
	else if (d_state == scream)
	{
		m_collisionScale.Set(1000.0f, 800.0f, 1000.0f);
		auto bone = m_skeleton->GetBone(3);
		m_collisionPosition.x = bone->GetWorldMatrix().m[3][0];
		m_collisionPosition.y = bone->GetWorldMatrix().m[3][1] + 100.0f;
		m_collisionPosition.z = bone->GetWorldMatrix().m[3][2];
		//m_collisionPosition = bone->GetWorldMatrix().v[3];
		CVector3 attackpoint;
		attackpoint.Set(m_collisionPosition);

		(void)clipName;
		m_ghost[D_attack00].CreateBox(attackpoint, m_rotation, m_collisionScale);
		
		m_sound[screamvoice].SetVolume(5.0f);
		m_sound[screamvoice].Play(false);
		g_physics.ContactTest(m_game->m_player->GetcharaCon(), [&](const btCollisionObject & contactObject)
			{
				if (m_ghost[D_attack00].IsSelf(contactObject))
				{
					//MessageBox(NULL, "attack", "attack", MB_OK);
					m_game->m_player->SetDamageFlag(true);
					m_game->m_player->SetDamage(10.0f);
				}
			});
	}
}
void Dragon::Move()
{
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	float angle = 0.0f;
	auto m_game = Game::instance();
	auto agoPos = m_collisionPosition;
	auto MoveLimitDiff = m_game->m_background->GetPosition() - m_position;
	
		if (m_game->m_player != nullptr) {
			diff.Set(m_game->m_player->GetPosition() - m_position);
		}
		//diff.Set(m_game->m_player->GetPosition() - agoPos);
		move = diff;
		move.y = 0.0f;
		move.Normalize();
		switch (d_state)

		{
		case normal:
			break;
		case walk:
			if (diff.Length() > 10.0f)
			{
				
				moveSpeed = move * 10.0f;
			}


			angle = atan2(move.x, move.z);
			m_rotation.SetRotation(CVector3::AxisY(), angle);
			break;
		case run:


			if (diff.Length() > 20.0f)
			{
				moveSpeed = move * 40.0f;
			
			}

			angle = atan2(move.x, move.z);
			m_rotation.SetRotation(CVector3::AxisY(), angle);

			break;
		case attack:
			break;
		case damage:

			
			break;
		case escape:
			
			moveSpeed = move * -30.0f;
			angle = atan2(-move.x, -move.z);
			m_rotation.SetRotation(CVector3::AxisY(), angle);
			break;
		case hornattack:

			if (!h_attackflag)
			{
				moveSpeed = move * 30.0f;
			}
			else move.Normalize();

			angle = atan2(move.x, move.z);
			m_rotation.SetRotation(CVector3::AxisY(), angle);
			break;
		case tailattack:

			move.Normalize();
			moveSpeed += m_front*20.0f;
			/*if (diff.Length() > 400.0f) {
			
				moveSpeed = move * 20.0f;
			}*/
			
			/*angle = atan2(move.x, move.z);
			m_rotation.SetRotation(CVector3::AxisY(), angle);*/
			break;
		case scream:
			move.Normalize();
			angle = atan2(move.x, move.z);
			m_rotation.SetRotation(CVector3::AxisY(), angle);
			break;

		}
		
	
}

void Dragon::CharaConMove()
{
	m_bone[Head] = m_skeleton->GetBone(11);
	m_bone[UpBody] = m_skeleton->GetBone(2);
	m_bone[Body] = m_skeleton->GetBone(0);
	m_bone[Tail] = m_skeleton->GetBone(30);
	moveSpeed.y -= 7.0f;
	for (int i = 0; i < CharaConTypeSize; i++) {

			m_charaConPos[i].Set(
				m_bone[i]->GetWorldMatrix().m[3][0],
				m_position.y,
				m_bone[i]->GetWorldMatrix().m[3][2]

			);
			m_charaCon[i].SetPosition(m_charaConPos[i]);
			m_charaCon[i].Execute(1.0f, moveSpeed);

			
	}
	

	

	//m_position =m_charaCon[UpBody].Execute(1.0f, CVector3::Zero());
	auto diff = m_charaConPos[Head]-m_position;
	m_position = m_charaCon[Head].GetPosition() -diff;
	//m_position = m_charaCon[UpBody].GetPosition();
}

bool Dragon::Start()
{
	//m_skinModelRender->SetGlowColor({0.01f,-0.01f,-0.01f});
	return true;
}

void Dragon::SetState()
{

	CVector3 bonePos;
	float angle;
	auto m_game = Game::instance();
	CVector3 forward;
	CVector3 diff_2;  //顎のボーンとプレイヤーの座標との距離
	CVector3 diff_3;  //m_positionとプレイヤーの座標との距離
	CMatrix m_dragonWorld = m_skeleton->GetBone(12)->GetWorldMatrix();
	forward.x = m_dragonWorld.m[2][0];
	forward.y = m_dragonWorld.m[2][1];
	forward.z = m_dragonWorld.m[2][2];

	bonePos.Set(
		m_dragonWorld.m[3][0],
		m_dragonWorld.m[3][1],
		m_dragonWorld.m[3][2]

	);
	diff_2= m_game->m_player->GetPosition() - bonePos;
	diff_3 = m_game->m_player->GetPosition() - m_position;
	
	auto nor_diff = diff_2;
	nor_diff.y = 0.0f;
	nor_diff.Normalize();
	angle = acos(nor_diff.Dot(forward));
	auto eyerange = angle / (pai / 180.0f);
	
	
	
	auto a = fabsf(eyerange);
	
	if (m_damageflag == true)
	{
		SetDragonState(damage);
		m_damageflag = false;
	}
	
	if (d_state == die)
	{
		
		if (!m_animation.IsPlaying())
		{
			d_info.isEnd = true;
			
		}
	}
	if (d_state != die) {
		if (d_info.HP < 0.01f)
		{
			SetDragonState(die);
			
		}
		auto a = rand() % 3;
		
			switch (d_state)
			{
			case Dragon::normal:

				/*if (diff_2.Length() < 150.0f)
				{
					SetDragonState(attack);
				}*/
				if (diff_2.Length() < 2000.0f&&fabsf(eyerange) < 90.0f || d_info.isFind == true)
				{
					//MessageBox(NULL, "ミツケタ…", "発見", MB_OK);
					OutputDebugStringA("ミツケタ…\n");
					SetDragonState(walk);

				}
				break;
			case Dragon::walk:

				walktimer++;
				if (walktimer > 100.0f)
				{
					SetDragonState(scream);
					walktimer = 0;
				}

				if (diff_3.Length() < 100.0f)
				{
					SetDragonState(escape);
				}
				if (diff_2.Length() < 150.0f)
				{
					SetDragonState(attack);
				}
				else if (diff_2.Length() < 2000.0f&&diff_2.Length() > 600.0f)
				{
					SetDragonState(run);
				}

				break;
			case Dragon::run:

				if (diff_2.Length() < 600.0f)
				{
					SetDragonState(walk);
				}
				else if (diff_2.Length() >= 2000.0f)
				{
					SetDragonState(normal);
				}
				break;
			case Dragon::die:
				
				break;
			case Dragon::attack:
				if (!m_animation.IsPlaying())
				{
					if (a == 0) {
						SetDragonState(escape);
					}
					if (a == 1)
					{
						SetDragonState(tailattack);
					}
					if (a == 2)
					{
						SetDragonState(scream);
					}
				}
				break;
			case Dragon::damage:
				if (!m_animation.IsPlaying())
				{
					
					if (a == 0) {
					
						SetDragonState(escape);
					}
					else if (a == 1)
					{
					
						SetDragonState(tailattack);
					}
					else if (a == 2)
					{
						SetDragonState(scream);
					}
				}
				break;
			case Dragon::escape:

				escapetimer++;
				if (diff_3.Length() > 1500.0f||escapetimer >50)
				{
					SetDragonState(hornattack);
					h_attackflag = false;
					escapetimer = 0;
				}
				break;
			case Dragon::hornattack:
				if (diff_2.Length() < 150.0f)
				{
					if (diff_3.Length() < 50)
					{
						SetDragonState(escape);
					}
					h_attackflag = true;
				}
				
				if (!m_animation.IsPlaying())
				{
					SetDragonState(walk);
					
				}
				break;
			case tailattack:
				if (!m_animation.IsPlaying())
				{
					
					if (a == 0) {
						SetDragonState(walk);
					}
					if (a == 1)
					{
						SetDragonState(hornattack);
					}
					if (a == 2)
					{
						SetDragonState(scream);
					}
					
					
				}
				break;
			case scream:
				if (!m_animation.IsPlaying())
				{
					if (diff_2.Length() > 1500.0f)
					{
						SetDragonState(hornattack);
					}
					else SetDragonState(walk);

				}
				break;
			default:
				break;
			}
		
	}
	m_front = bonePos - m_position;
	m_front.y = 0.0f;
	m_front.Normalize();


}
void Dragon::DamageEvent()
{
	
	rand_damage = rand() % 3;
	if (d_state != die) {
		auto m_game = Game::instance();
		if (m_game->m_player != nullptr)
		{
			
				if (m_game->m_player->GetAttackFlag())
				{

					auto plbone = m_game->m_player->GetPlayerBone(23);
					auto plpower = m_game->m_player->GetPlayerInformation().AttackPower;



					/*if (plpower >= d_info.HP)
					{

						if (m_game->m_quest->GetQuestInfo().m_questType == QuestManager::Bossbattle)
						{
							m_game->m_quest->AddQuestPoint();
							
						}
					}*/
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
					for (int i = 0; i < CharaConTypeSize; i++) {
						g_physics.ContactTest(m_charaCon[i], [&](const btCollisionObject & contactObject)
							{
								if (m_ghost[P_attack00].IsSelf(contactObject))
								{
									//再生中のエフェクトを止める。
									g_effect.m_effekseerManager->StopEffect(g_effect.m_playEffectHandle);
									//再生。
									g_effect.m_playEffectHandle = g_effect.m_effekseerManager->Play(
										g_effect.m_sampleEffect[GameObjectManager::EffectType::damage],
										bonePos.x,
										bonePos.y,
										bonePos.z
									);
									m_sound[gethit].Play(false);

									if (rand_damage == 0) {
										d_info.HP -= plpower;
										if (d_state != tailattack) {
											m_damageflag = true;
											m_ghost[P_attack00].Release();

										}
									}
									
								}
						});
					}
				}
			
		}
		
	}
	

}
void Dragon::Update()
{
	auto ispouse = Game::instance()->GetPauseFlag();
	auto m_game = Game::instance();
	if (!ispouse) {
		//ゴーストオブジェクトを１フレーム削除
		if (&m_ghost[D_attack00] != nullptr)
		{
			m_ghost[D_attack00].Release();
		}

		if (&m_ghost[P_attack00] != nullptr)
		{
			m_ghost[P_attack00].Release();
		}
		if (d_info.isEnd)
		{
			
			if (m_Item == nullptr&&d_state == die && !m_animation.IsPlaying()) {
				if (m_game->m_quest->GetQuestInfo().m_questType == QuestManager::Bossbattle)
				{
					m_game->m_quest->AddQuestPoint();
					m_game->m_quest->SetTargetDieFlag(true);
				}
				m_Item = GameObjectManager::instance().NewGO<Item>();
				m_Item->RandTypeItemCreate(
					m_position,
					m_rotation,
					200.0f,
					Item::BD_Die,
					2
				);
			}
		}
		Move();
		CharaConMove();

		SetState();
		AnimationPlay();
		DamageEvent();

		m_skinModelRender->SetPosition(m_position);
		m_skinModelRender->SetRotation(m_rotation);
		m_skinModelRender->SetScale(m_scale);
	}
}

void Dragon::Render()
{
	
}

void Dragon::ColliderInit(int type,float radius,float height,CVector3& position)
{
	m_collider[type].Create(radius, height);
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider[type];
	m_rigidBody.Create(rbInfo);
	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	//剛体の位置を更新。
	trans.setOrigin(btVector3(position.x, position.y + height * 0.5f + radius, position.z));
	//@todo 未対応。trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	g_physics.AddRigidBody(m_rigidBody);

}


