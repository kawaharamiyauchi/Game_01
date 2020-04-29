#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include"Game.h"
#include"GameObjectManager.h"
#include"QuestManager.h"
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
	g_camera3D.SetFar(100000.0f);
}


GameCamera::~GameCamera()
{
}

void GameCamera::ChangeCameraState()
{
	auto m_game = Game::instance();

	if (m_game->m_quest != nullptr)
	{
		if (m_game->m_quest->GetGameState() == QuestManager::normal)
		{
			m_CS = normal;
		}
	}
	if (m_game->m_player != nullptr) {
		if (m_game->m_player->GetPlayerInformation().HP < 0.001f)
		{
			m_CS = GameOver;

		}

	}

	if (m_game->GetStageNum()==3)
	{
		if (m_game->m_dragon->GetDragonInfo().HP<=0)
		{
			m_CS = GameClear;
		}
		if (m_game->m_dragon->GetDragonInfo().isEnd)
		{
			m_CS = normal;
		}
	}
	
}
void GameCamera::Reset()
{
	m_toCameraPos.Set(0.0f, 70.0f, -250.0f);
	
	g_camera3D.SetPosition({ 0.0f,250.0f,-300.0f });
	g_camera3D.SetNear(1.0f);
	g_camera3D.SetFar(100000.0f);
	
}
void GameCamera::Update()
{

	ChangeCameraState();
	auto m_game = Game::instance();
	CVector3 toCameraPosOld;
	float x;
	float y;

	float angle;
	CVector3 axisX;
	//Y������̉�]
	CQuaternion qRot;
	CVector3 toPosDir;
	CVector3 toDiff;
	CVector3 d;
	CVector3 plPos;
	CVector3 drPos;


	if (m_game->GetStageNum() == 3)
	{
		toDiff =m_game->m_player->GetPosition()- m_game->m_dragon->GetPosition() ;
		toDiff.Normalize();

		
	}
	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	if (!g_pad[0].IsPress(enButtonLB2))
	{
		x = g_pad[0].GetRStickXF() * 2;
		y = g_pad[0].GetRStickYF() * 2;
		
		
	}
	else {
		plPos = m_game->m_player->GetPosition();
	

	}

	//x = g_pad[0].GetRStickXF() * 2;
	//y = g_pad[0].GetRStickYF() * 2;
	switch (m_CS)
	{
	case(normal):
		m_target = m_game->m_player->GetPosition();
		
		m_target.y += 110.0f;
		
		toCameraPosOld = m_toCameraPos;
		angle = atan2(toDiff.x,toDiff.z);
		
	
		qRot.SetRotationDeg(CVector3::AxisY(), 2.0f * x);
		
		qRot.Multiply(m_toCameraPos);
		//X������̉�]�B
		
		axisX.Cross(CVector3::AxisY(), m_toCameraPos);
		axisX.Normalize();
		qRot.SetRotationDeg(axisX, 2.0f * y);
		qRot.Multiply(m_toCameraPos);
		//�J�����̉�]�̏�����`�F�b�N����B
		//�����_���王�_�܂ł̃x�N�g���𐳋K������B
		//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
		//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
		toPosDir = m_toCameraPos;
		toPosDir.Normalize();
		if (toPosDir.y < -0.5f) {
			//�J����������������B
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.8f) {
			//�J�����������������B
			m_toCameraPos = toCameraPosOld;
		}
		
		m_position = m_target + m_toCameraPos;

		break;
	case(GameClear):
		drPos = m_game->m_dragon->GetPosition();
		m_position.y += 5.0f;
		m_target = drPos;
		
		break;
	case(GameOver):

		plBone = m_game->m_player->GetPlayerBone(23);
		pltarget.Set(
			plBone->GetWorldMatrix().m[3][0],
			plBone->GetWorldMatrix().m[3][1],
			plBone->GetWorldMatrix().m[3][2]
		);
		
		d = m_position - pltarget;
		
		if (d.Length() > 100.0f)
		{
			d.Normalize();
			m_position -= d * 2.0f;
		}
		m_target = pltarget;
		break;

	default:
		break;
	}

	if (m_game->instance()->GetIsNonGame())
	{
		m_CS = normal;
	}
	
	if (m_game->GetStageNum() == 3)
	{
		if (g_pad[0].IsPress(enButtonLB2))
		{
			drPos = m_game->m_dragon->GetPosition();
			drPos.y += 20.0f;
			m_target = drPos;
			//CVector3 exPos;
			m_toCameraPos.Set(toDiff.x*200.0f, 120.0f, toDiff.z*200.0f);
			m_position.Set(plPos+m_toCameraPos);
		}
	}

	g_camera3D.SetPosition(m_position);

	g_camera3D.SetTarget(m_target);
	//�J�����̍X�V�B
	g_camera3D.Update();
	
}
void GameCamera::Render()
{
	
}