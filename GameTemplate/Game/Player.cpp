#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Dragon.h"
#include"GameObjectManager.h"
#include"HID/Pad.h"

Player::Player()
{
	

	//m_position[Hunter].Set(0.0f, 200.0f, -300.0f);
	for (int i = 0; i < Modeltype::ModelType_num; i++) {
		m_skinModelRender[i] =GameObjectManager::instance().NewGO<SkinModelRender>();
	}
	m_charaCon.Init(

		40.0f,		//半径
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
	m_animationClip[enAnimationClip_damage].Load(L"Assets/animData/hunter03_damage.tka",L"enAnimtion(h)Damage");
	//m_animationClip[enAnimationClip_damage].Load(L"Assets/animData/hunter_test.tka", L"enAnimtion(h)Damage");
	m_animationClip[enAnimationClip_idle].Load(L"Assets/animData/hunter03_idle.tka",L"enAnimation(h)Idle");
	m_animationClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_damage].SetLoopFlag(false);
	m_animationClip[enAnimationClip_die].Load(L"Assets/animData/hunter03_die.tka", L"enAnimation(h)Die");
	m_animationClip[enAnimationClip_die].SetLoopFlag(false);
	m_animationClip[enAnimationClip_drink].Load(L"Assets/animData/hunter03_drink.tka", L"enAnimation(h)Drink");
	m_animationClip[enAnimationClip_drink].SetLoopFlag(false);
	m_animation.Init(*m_skinModelRender[Hunter]->GetSkinModel(), m_animationClip, enAnimationClip_num);
	m_skinModelRender[Hunter]->SetActiveFlag(true);
	m_skinModelRender[RightHand]->SetActiveFlag(false);
	m_skinModelRender[LeftHand]->SetActiveFlag(false);
	m_skinModelRender[Weapon]->SetActiveFlag(false);
	//m_skeleton = &m_model[Hunter].GetSkeleton();
	m_skeleton = m_skinModelRender[Hunter]->GetSkeleton();
	const wchar_t * bonename[41];
	m_animation.AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);

		});

	for (int i = 0; i < 24; i++)
	{
		bonename[i] = m_skeleton->GetBone(i)->GetName();

		if (i==23)
		{
			
			bonename[i+1] = L"end";
		}
	}
	m_sound[GetHit].Init(L"Assets/sound/punch-middle2.wav");
	m_sound[move].Init(L"Assets/sound/walk-soil1.wav");
}


Player::~Player()
{
	for (int i = 0; i < ModelType_num; i++) {
		GameObjectManager::instance().DeleteGO(m_skinModelRender[i]);

	}
	

}
void Player::OnAnimationEvent(const wchar_t * clipName, const wchar_t * eventName)
{
	if (p_state == run)
	{
		stopflag = true;
		m_sound[move].Stop();
		m_sound[move].Play(false);
	}
}
void Player::Move()
{
	Dragon*m_dragon;
	
	
	{

	}
	if (Game::instance()->m_dragon != nullptr) {
		m_dragon = Game::instance()->m_dragon;
	}
	if (p_state != die&&p_state!=useitem)
	{
		float IStick_y = 0.0f;
		float IStick_x = 0.0f;
		if (p_state != attack) {
		//if (m_attackTimer < 5) {
			IStick_x = g_pad[0].GetLStickXF();
			IStick_y = g_pad[0].GetLStickYF();
		//}
		}

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


			m_speed += cameraForward * IStick_y*10.0f;
			m_speed += cameraRight * IStick_x*10.0f;

		}
		if (p_state != damage) {
			if (!g_pad[0].IsPress(enButtonLB1)) {
				if (g_pad[0].IsTrigger(enButtonB) && p_state != jump)
				{
					if (p_state != attack) {
						m_speed.y += 40.0f;
						p_state = jump;
						m_jumpflag = true;
					}
				}
			}
		}
		if (p_state == run)
		{
			m_speed.x *= 3.0f;
			m_speed.z *= 3.0f;
			if (m_plinfo.Stamina > 0.1f)
			{
				m_plinfo.Stamina -= 1.0f;
			}
			else m_dashflag = false;

		}
		else if (p_state != run && m_plinfo.Stamina < 100.0f)
		{
			m_plinfo.Stamina += 2.0f;
		}
		/*if (p_state == attack)
		{
			auto mat = m_skinModelRender[Hunter]->GetWorldMatrix();
			CVector3 m_front;
			m_front.Set(
				mat->m[3][0],
				mat->m[3][1],
				mat->m[3][2]);
			m_front.Normalize();
			m_speed += m_front*10.0f;
		}*/
		if (p_state == damage)
		{

			if (m_damageTimer == 1) {
				m_speed += m_dragon->GetFront()*30.0f;
			}

		}
		/*if (p_state == attack)
		{
			m_speed *= 2.0f;
		}*/
		CVector3 bonePos[Modeltype::ModelType_num];
		


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

		m_speed.y -= 6.0f;

	}
	if (p_state == die)
	{
		m_speed.x = 0.0f;
		m_speed.z = 0.0f;
		m_speed.y = 0.0f;
	}
	if (p_state == run) {
		if (stopflag)
		{
			runTimer = 0;
			footStop = 4.0f;
		}
		else if (!stopflag)
		{
			runTimer++;
			if (runTimer < 8&&footStop >1.0f) {
				footStop -= 1.0f;
			}
			else if (runTimer >= 8&&footStop<2.4f)
			{
				footStop += 0.5f;
			}
		}
	}
	else footStop = 1.0f;
	if (p_state == attack)
	{
		m_speed -= m_footStep;
	}
	m_speed.x /= footStop;
	m_speed.z /= footStop;
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
	auto m_Item = Game::instance()->m_Item;
	if (p_state == die)
	{
		if (!m_animation.IsPlaying())
		{
			m_plinfo.isEnd = true;
		}
	}
	if (p_state != die) {
		if (m_plinfo.Stamina > 99)
		{
			m_dashflag = true;
		}
		if (g_pad[0].IsTrigger(enButtonY) && m_charaCon.IsOnGround())
		{
			p_state = attack;

		}
		if (m_attackTimer == 10)
		{
			//MessageBox(NULL, "ハンターの攻撃！！", "Game Over", MB_OK);
		}
		if (m_attackTimer > 20)
		{
			m_attackTimer = 0;
			p_state = idle;
		}
		if (m_damageFlag)
		{
			
			m_damageTimer++;
			if (!m_sound[GetHit].IsPlaying()&&m_damageTimer ==1)
			{
				m_sound[GetHit].Play(false);
			}
			m_attackTimer = 0;
			p_state = damage;
			
			if (m_damageTimer > 30)
			{
				m_damageFlag = false;
				m_damageTimer = 0;
				p_state = idle;
			}

		}
		if (p_state != damage && p_state != die&&p_state !=useitem)
		{
			if (m_charaCon.IsOnGround() && p_state != attack) {
				if (fabsf(m_speed.x*m_speed.z) > 0.01f&&stopflag !=true)
				{
					p_state = walk;
					if (g_pad[0].IsPress(enButtonRB1)&&m_dashflag)
					{
						p_state = run;
					}
				}
				else p_state = idle;
			}
		}
		if (m_plinfo.HP<0.01f)
		{
			if (m_charaCon.IsOnGround())
			{
				p_state = die;
			}
		}
		


		if (g_pad[0].IsTrigger(enButtonX) && m_charaCon.IsOnGround())
		{

			if (!g_pad[0].IsPress(enButtonLB1)) {

				p_state = useitem;
				if (m_Item->UseItem() == Item::ItemType::kaihukuyaku)
				{
					m_plinfo.HP += 10.0f;
				}
			}
		}
		if (g_pad[0].IsTrigger(enButtonA))
		{
			m_Item->GetItem(Item::ItemType::kaihukuyaku, 2);
		}
		if (p_state == useitem&&!m_animation.IsPlaying())
		{
			p_state = idle;
		}
	}
}
void Player::AnimationPlay()
{
	const float interpolateTime = 0.2f;
	if (p_state == idle)
	{
		m_animation.Play(enAnimationClip_idle, interpolateTime);
		auto a =m_animation.Update(0.05f);
		m_speed = a;
		
	}
	if (p_state ==walk)
	{
		m_animation.Play(enAnimationClip_walk, interpolateTime);
		m_animation.Update(0.07f);
	}
	if (p_state  ==jump)
	{
		m_animation.Play(enAnimationClip_jump, interpolateTime);
		m_animation.Update(0.04f);
		if (m_charaCon.IsOnGround()) {
			m_jumpflag = false;
		}
	}

	if (p_state == run)
	{
		m_animation.Play(enAnimationClip_run, interpolateTime);
		m_animation.Update(0.11f);
	}
	if (p_state == attack)
	{
		m_footStep = m_animation.Update(0.04f);
		auto change = m_footStep.y;
		m_footStep.y = m_footStep.z;
		m_footStep.z = change;
		m_animation.Play(enAnimationClip_attack, interpolateTime);
		CMatrix rotMatrix;
		CMatrix mBias = CMatrix::Identity();
		//回転行列を作成する。
		rotMatrix.MakeRotationFromQuaternion(m_rotation[Hunter]);
		rotMatrix.Mul(mBias, rotMatrix);
		rotMatrix.Mul(m_footStep);
		m_attackTimer++;

	}
	if (p_state == damage)
	{
		m_animation.Play(enAnimationClip_damage, interpolateTime);
		/*auto a =*/m_animation.Update(0.06f);
		//m_speed = a;

	}
	if (p_state == die)
	{
		m_animation.Play(enAnimationClip_die, interpolateTime);
		m_animation.Update(0.04f);
	}
	if (p_state == useitem)
	{
		m_animation.Play(enAnimationClip_drink, interpolateTime);
		m_animation.Update(0.04f);
	}
}


void Player::Update()
{
	auto ispouse = Game::instance()->GetPauseFlag();
		
	if (!ispouse) {
		StateChange();
		AnimationPlay();

		if (Fade::instance().IsEnd())
		{
			Move();
			stopflag = false;

		}

		Turn();
		GameObjectManager::instance().SetLightCameraPos(m_position[Hunter]);
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
}
void Player::Render()
{
	
}

