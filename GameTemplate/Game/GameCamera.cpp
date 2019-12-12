#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include"Game.h"
#include"GameObjectManager.h"
#include"Dragon.h"

GameCamera::GameCamera()
{
	m_toCameraPos.Set(0.0f, 70.0f, -250.0f);
	//m_position = {m_player->GetPosition().x,m_player->GetPosition().y + 10.0f, m_player->GetPosition().z-50.0f };
	//m_position = { 0.0f,10.0f,-100.0f };
	//g_camera3D.SetViewAngle(60.0f);
	g_camera3D.SetPosition({ 0.0f,250.0f,-300.0f });
	//g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetNear(1.0f);
	g_camera3D.SetFar(1000000.0f);
}


GameCamera::~GameCamera()
{
}

void GameCamera::Update()
{
	auto m_game = Game::instance();
	

	if (m_game->m_player->GetPlayerInformation().HP < 0.001f)
	{
		auto plPos = m_game->m_player->GetPosition();
		plPos.y += 100.0f;
		
		auto d = m_position - plPos;
		if (d.Length() > 100.0f)
		{
			d.Normalize();
			m_position -= d * 2.0f;
		}
		m_target = m_game->m_player->GetPosition();
		m_timer++;
		if (m_timer < 120)
		{
			
		}
	}
	else {
		

		m_target = m_game->m_player->GetPosition();

		m_target.y += 110.0f;
		//m_target.y += 200.0f;
		CVector3 toCameraPosOld = m_toCameraPos;
		//�p�b�h�̓��͂��g���ăJ�������񂷁B
		float x = g_pad[0].GetRStickXF() * 2;
		float y = g_pad[0].GetRStickYF() * 2;
		//Y������̉�]
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3::AxisY(), 2.0f * x);
		qRot.Multiply(m_toCameraPos);
		//X������̉�]�B
		CVector3 axisX;
		axisX.Cross(CVector3::AxisY(), m_toCameraPos);
		axisX.Normalize();
		qRot.SetRotationDeg(axisX, 2.0f * y);
		qRot.Multiply(m_toCameraPos);
		//�J�����̉�]�̏�����`�F�b�N����B
		//�����_���王�_�܂ł̃x�N�g���𐳋K������B
		//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
		//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
		CVector3 toPosDir = m_toCameraPos;
		toPosDir.Normalize();
		if (toPosDir.y < -0.5f) {
			//�J����������������B
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.8f) {
			//�J�����������������B
			m_toCameraPos = toCameraPosOld;
		}
		//g_camera3D.SetViewAngle(x);

		m_position = m_target + m_toCameraPos;
		//m_position.y += 200.0f;
		

	}
	g_camera3D.SetPosition(m_position);
	g_camera3D.SetTarget(m_target);
	//�J�����̍X�V�B
	g_camera3D.Update();
	
}
void GameCamera::Render()
{
	
}