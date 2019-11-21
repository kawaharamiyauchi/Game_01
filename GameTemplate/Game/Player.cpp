#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include"GameObjectManager.h"
#include"HID/Pad.h"

Player::Player()
{
	
	m_charaCon.Init(

		20.0f,		//半径
		40.0f,		//高さ
		m_position	//初期座標
	);	
	//cmoファイルの読み込み。
	m_skleton.Load(L"Assets/modelData/hunter.tks");
	m_model.Init(L"Assets/modelData/hunter.cmo");

	m_animationClip[enAnimationClip_run].Load(L"Assets/animData/hunter_run.tka",L"enAnimation(h)Run");
	m_animationClip[enAnimationClip_run].SetLoopFlag(true);
	m_animationClip[enAnimationClip_damage].Load(L"Assets/animData/hunter_damage.tka",L"enAnimtion(h)Damage");
	m_animationClip[enAnimationClip_damage].SetLoopFlag(false);
	m_animation.Init(m_model, m_animationClip, enAnimationClip_num);
}


Player::~Player()
{
}

void Player::Move()
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
	if (g_pad[0].IsTrigger(enButtonB))
	{
		m_speed.y += 40.0f;
		
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
		m_speed += cameraForward * -10.0f;
		
	}
	m_position =m_charaCon.Execute(1.0f,m_speed);

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
	m_rotation.SetRotation(CVector3::AxisY(), angle);

}
void Player::StateChange()
{	
	/*if (m_plinfo.HP < 0.1)
	{
		p_state = dye;
	}*/
	if (!m_animation.IsPlaying())
	{
		p_state = idle;
	}
	if (g_pad[0].IsPress(enButtonLB1))
	{
		p_state = damage;
	}
	if (p_state != damage && p_state != dye)
	{
		
		if (g_pad[0].IsPress(enButtonRB1))
		{
			p_state = run;
		}
		else p_state = idle;

	}

}
void Player::AnimationPlay()
{
	/*if (p_state == idle)
	{
		m_animation.Play(enAnimationClip_run);
		m_animation.Update(0.4f);
	}*/
	if (p_state == run)
	{
		m_animation.Play(enAnimationClip_run);
		m_animation.Update(0.3f);
	}
	if (p_state == damage)
	{
		m_animation.Play(enAnimationClip_damage);
		m_animation.Update(0.3f);
	}
}


void Player::Update()
{
	StateChange();
	AnimationPlay();
	Move();
	Turn();
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position,m_rotation,m_scale);
	if (m_plinfo.HP < 0.01f)
	{
		isPlus = true;
	}
	else if (m_plinfo.HP > 99.9f)
	{
		isPlus = false;
	}
	if (isPlus == false) {
		m_plinfo.HP -= 1.0f;
	}
	else m_plinfo.HP += 1.0f;
}
void Player::Render()
{
	//MessageBox(NULL, "aa", "aaa",MB_OK);
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
	
}

