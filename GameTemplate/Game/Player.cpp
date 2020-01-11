#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Dragon.h"
#include"GameObjectManager.h"
#include"HID/Pad.h"

Player::Player()
{
	m_position[Hunter].Set(0.0f, 200.0f, -300.0f);
	for (int i = 0; i < Modeltype::ModelType_num; i++) {
		m_skinModelRender[i] =GameObjectManager::instance().NewGO<SkinModelRender>();
	}
	m_charaCon.Init(

		80.0f,		//半径
		80.0f,		//高さ
		m_position[Hunter]	//初期座標
	);	
	//cmoファイルの読み込み。
	//m_skinModelRender[Hunter]->Init(L"Assets/modelData/hunter_weapon.cmo");
	m_skinModelRender[Hunter]->Init(L"Assets/modelData/hunter03.cmo");

	m_skinModelRender[RightHand]->Init(L"Assets/modelData/testbox_small.cmo");
	m_skinModelRender[LeftHand]->Init(L"Assets/modelData/testbox_small.cmo");
	m_skinModelRender[Weapon]->Init(L"Assets/modelData/testbox_small.cmo");

	m_skinModelRender[Hunter]->SetShadowCasterFlag(true);
	m_skinModelRender[Hunter]->SetShadowRecieverFlag(false);
	m_skinModelRender[RightHand]->SetShadowCasterFlag(true);
	m_skinModelRender[LeftHand]->SetShadowCasterFlag(true);
	m_skinModelRender[Weapon]->SetShadowCasterFlag(true);
	//m_skinModelRender[Hunter]
	/*m_model[Hunter].Init(L"Assets/modelData/hunter_weapon.cmo");
	m_model[RightHand].Init(L"Assets/modelData/testbox_small.cmo");
	m_model[LeftHand].Init(L"Assets/modelData/testbox_small.cmo");
	m_model[Weapon].Init(L"Assets/modelData/testbox_small.cmo");*/

	//m_model[Hunter].SetlightFlag(false);
	m_animationClip[enAnimationClip_run].Load(L"Assets/animData/hunter03_run.tka",L"enAnimation(h)Run");
	m_animationClip[enAnimationClip_run].SetLoopFlag(true);
	m_animationClip[enAnimationClip_jump].Load(L"Assets/animData/hunter03_jump.tka", L"enAnimation(h)Jump");
	m_animationClip[enAnimationClip_jump].SetLoopFlag(false);
	m_animationClip[enAnimationClip_walk].Load(L"Assets/animData/hunter03_walk.tka", L"enAnimation(h)Walk");
	m_animationClip[enAnimationClip_walk].SetLoopFlag(true);
	m_animationClip[enAnimationClip_attack].Load(L"Assets/animData/hunter03_attack.tka", L"enAnimation(h)Attack");
	m_animationClip[enAnimationClip_attack].SetLoopFlag(false);
	//m_animationClip[enAnimationClip_damage].Load(L"Assets/animData/hunter_damage.tka",L"enAnimtion(h)Damage");
	//m_animationClip[enAnimationClip_damage].Load(L"Assets/animData/hunter_test.tka", L"enAnimtion(h)Damage");
	m_animationClip[enAnimationClip_idle].Load(L"Assets/animData/hunter03_idle.tka",L"enAnimation(h)Idle");
	m_animationClip[enAnimationClip_idle].SetLoopFlag(true);
	//m_animationClip[enAnimationClip_damage].SetLoopFlag(false);
	//m_animation.Init(m_model, m_animationClip, enAnimationClip_num);
	m_animation.Init(*m_skinModelRender[Hunter]->GetSkinModel(), m_animationClip, enAnimationClip_num);
	m_skinModelRender[Hunter]->SetActiveFlag(true);
	m_skinModelRender[RightHand]->SetActiveFlag(false);
	m_skinModelRender[LeftHand]->SetActiveFlag(false);
	m_skinModelRender[Weapon]->SetActiveFlag(false);
	//m_skeleton = &m_model[Hunter].GetSkeleton();
	m_skeleton = m_skinModelRender[Hunter]->GetSkeleton();
	const wchar_t * bonename[41];


	for (int i = 0; i < 23; i++)
	{
		bonename[i] = m_skeleton->GetBone(i)->GetName();
		if (i==22)
		{
			bonename[i+1] = L"end";
		}
	}
	
}


Player::~Player()
{
	
}

void Player::Move()
{
	auto m_dragon = Game::instance()->m_dragon;

	if (p_state != die&&p_state !=attack)
	{
		float IStick_x = g_pad[0].GetLStickXF();
		float IStick_y = g_pad[0].GetLStickYF();

		CVector3 cameraForward = g_camera3D.GetFront();
		CVector3 cameraRight = g_camera3D.GetRight();

		cameraForward.y = 0.0f;
		cameraForward.Normalize();
		cameraRight.y = 0.0f;
		cameraRight.Normalize();

		if (p_state != damage)
		{
			m_speed.x = 0.0f;
			m_speed.z = 0.0f;
			m_speed.y -= 4.0f;


			m_speed += cameraForward * IStick_y*20.0f;
			m_speed += cameraRight * IStick_x*20.0f;

		}
		if (g_pad[0].IsTrigger(enButtonB)&&p_state !=jump)
		{
			m_speed.y += 40.0f;
			p_state = jump;
			m_jumpflag = true;

		}
		if (p_state == run)
		{
			m_speed.x *= 1.8f;
			m_speed.z *= 1.8f;
			if (m_plinfo.Stamina > 0.1f)
			{
				m_plinfo.Stamina -= 1.0f;
			}

		}
		else if (p_state != run && m_plinfo.Stamina < 100.0f)
		{
			m_plinfo.Stamina += 2.0f;
		}
		if (p_state == damage)
		{
			m_speed += m_dragon->GetFront();

		}
		CVector3 bonePos[Modeltype::ModelType_num];
		bonePos[Hunter] =CVector3::Zero();
		/*for (int i = 1; i < Modeltype::ModelType_num; i++)
		{
			
			bonePos[i].Set(
				m_skeleton->GetBone(14+i*4)->GetWorldMatrix().m[3][0],
				m_skeleton->GetBone(14+i*4)->GetWorldMatrix().m[3][1],
				m_skeleton->GetBone(14+i*4)->GetWorldMatrix().m[3][2]
			);
		}*/
		/*m_position[RightHand] = bonePos[RightHand];
		m_position[LeftHand] = bonePos[LeftHand];
		m_position[Weapon] = bonePos[Weapon];*/
		

		m_position[RightHand] = bonePos[RightHand];
		m_position[LeftHand] = bonePos[LeftHand];
		m_position[Weapon] = bonePos[Weapon];
	}
	if (m_damageTimer > 0 && m_damageTimer < 10)
	{
		m_speed.y += 5.0f;
	}
	if (m_damageTimer >= 5 && m_damageTimer < 30)
	{
	//	m_speed.y = 0;
		m_speed.y -= 6.0f;
		if (m_charaCon.IsOnGround())
		{
			
		}
	}
	m_position[Hunter] = m_charaCon.Execute(1.0f, m_speed);

}
void Player::Turn()
{
	float angle = 0.0f;
	if (fabsf(m_speed.x) < 0.001f
		&& fabsf(m_speed.z) < 0.001f) {
		
		return;
	}
	if (p_state != damage)
	{
		angle = atan2(m_speed.x, m_speed.z);
	}
	else angle = atan2(-m_speed.x, -m_speed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	m_rotation[Hunter].SetRotation(CVector3::AxisY(), angle);
	CQuaternion m_boneQuaternion[Modeltype::ModelType_num];
	m_boneQuaternion[Hunter] = CQuaternion::Identity();
	/*for (int i = 1; i < Modeltype::ModelType_num; i++)
	{
		m_boneQuaternion[i].SetRotation(m_skeleton->GetBone(14 + i * 4)->GetWorldMatrix());
	}*/
	m_rotation[RightHand].Set(m_boneQuaternion[RightHand]);
	m_rotation[LeftHand].Set(m_boneQuaternion[LeftHand]);
	m_rotation[Weapon].Set(m_boneQuaternion[Weapon]);

}
void Player::StateChange()
{	
	
	if (g_pad[0].IsTrigger(enButtonY)&&m_charaCon.IsOnGround())
	{
		p_state = attack;
		
	}
	if (m_attackTimer == 10)
	{
		MessageBox(NULL, "ハンターの攻撃！！", "Game Over", MB_OK);
	}
	if (m_attackTimer > 20)
	{
		m_attackTimer = 0;
		p_state = idle;
	}
	if (m_damageFlag)
	{
		m_damageTimer++;
		p_state = damage;
		if(m_damageTimer ==1)
		{
			m_plinfo.HP -= 20.0f;
			
		}
		if (m_damageTimer > 30)
		{
			m_damageFlag = false;
			m_damageTimer =0;
			p_state = idle;
		}
		
	}
	if (p_state != damage && p_state != die)
	{
		if (m_charaCon.IsOnGround()&&p_state !=attack) {
			if (fabsf(m_speed.x*m_speed.z) > 0.01f)
			{
				p_state = walk;
				if (g_pad[0].IsPress(enButtonRB1))
				{
					p_state = run;
				}
			}
			else p_state = idle;
		}
	}
	if (m_plinfo.HP < 0.001f)
	{
		p_state = die;
		
			MessageBox(NULL, "力尽きました…", "Game Over", MB_OK);
		
	}
}
void Player::AnimationPlay()
{
	if (p_state == idle)
	{
			m_animation.Play(enAnimationClip_idle);

			m_animation.Update(0.1f);
		
	}
	if (p_state ==walk)
	{
		m_animation.Play(enAnimationClip_walk);
		m_animation.Update(0.1f);
	}
	if (p_state  ==jump)
	{
		m_animation.Play(enAnimationClip_jump);
		m_animation.Update(0.04f);
		if (m_charaCon.IsOnGround()) {
			m_jumpflag = false;
		}
	}

	if (p_state == run)
	{
		m_animation.Play(enAnimationClip_run);
		m_animation.Update(0.3f);
	}
	if (p_state == attack)
	{
		//bone[13] Weapon
		m_animation.Play(enAnimationClip_attack);
		
		m_animation.Update(0.04f);
		m_attackTimer++;

	}
	/*if (p_state == damage)
	{
		m_animation.Play(enAnimationClip_damage);
		m_animation.Update(0.3f);
	}*/
}


void Player::Update()
{
	
	if (p_state != die)
	{
		StateChange();
	}
	AnimationPlay();
	Move();
	Turn();
	//ワールド行列の更新。
	
	//m_model[Hunter].UpdateWorldMatrix(m_position[Hunter], m_rotation[Hunter], m_scale);
	m_skinModelRender[Hunter]->SetPosition(m_position[Hunter]);
	m_skinModelRender[Hunter]->SetRotation(m_rotation[Hunter]);
	m_skinModelRender[Hunter]->SetScale(m_scale);
	for (int i = 1; i < Modeltype::ModelType_num; i++) {
		//m_model[i].UpdateWorldMatrix(m_position[i], m_rotation[i], m_scale);
		m_skinModelRender[i]->SetPosition(m_position[i]);
		m_skinModelRender[i]->SetRotation(m_rotation[i]);
		m_skinModelRender[i]->SetScale(m_scale);
	}
}
void Player::Render()
{
	//MessageBox(NULL, "aa", "aaa",MB_OK);
	/*for (int i = 0; i < Modeltype::ModelType_num; i++)
	{
		m_model[i].Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}*/
	
}

