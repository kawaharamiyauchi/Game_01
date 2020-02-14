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
	g_camera3D.SetFar(1000000.0f);
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

	if (m_game->GetStageNum()==1)
	{
		if (m_game->m_quest->GetGameState()==QuestManager::clear)
		{
			m_CS = GameClear;
		}
		if (m_game->m_dragon->GetDragonInfo().isEnd)
		{
			m_CS = normal;
		}
	}
	
}

void GameCamera::Update()
{

	ChangeCameraState();
	auto m_game = Game::instance();
	CVector3 toCameraPosOld;
	float x;
	float y;
	CVector3 axisX;
	//Y軸周りの回転
	CQuaternion qRot;
	CVector3 toPosDir;

	CVector3 d;
	CVector3 plPos;
	CVector3 drPos;

	//パッドの入力を使ってカメラを回す。
	x = g_pad[0].GetRStickXF() * 2;
	y = g_pad[0].GetRStickYF() * 2;
	switch (m_CS)
	{
	case(normal):
		m_target = m_game->m_player->GetPosition();

		m_target.y += 110.0f;
		//m_target.y += 200.0f;
		toCameraPosOld = m_toCameraPos;
		
		
		
		qRot.SetRotationDeg(CVector3::AxisY(), 2.0f * x);
		qRot.Multiply(m_toCameraPos);
		//X軸周りの回転。
		
		axisX.Cross(CVector3::AxisY(), m_toCameraPos);
		axisX.Normalize();
		qRot.SetRotationDeg(axisX, 2.0f * y);
		qRot.Multiply(m_toCameraPos);
		//カメラの回転の上限をチェックする。
		//注視点から視点までのベクトルを正規化する。
		//正規化すると、ベクトルの大きさが１になる。
		//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
		toPosDir = m_toCameraPos;
		toPosDir.Normalize();
		if (toPosDir.y < -0.5f) {
			//カメラが上向きすぎ。
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.8f) {
			//カメラが下向きすぎ。
			m_toCameraPos = toCameraPosOld;
		}
		//g_camera3D.SetViewAngle(x);

		m_position = m_target + m_toCameraPos;
		//m_position.y += 200.0f;

		break;
	case(GameClear):
		drPos = m_game->m_dragon->GetPosition();
		m_position.y += 5.0f;
		m_target = drPos;
		
		break;
	case(GameOver):
		plPos = m_game->m_player->GetPosition();
		plPos.y += 100.0f;
		d = m_position - plPos;
		
		if (d.Length() > 100.0f)
		{
			d.Normalize();
			m_position -= d * 2.0f;
		}
		m_target = m_game->m_player->GetPosition();
		break;

	default:
		break;
	}

	if (m_game->instance()->GetIsNonGame())
	{
		m_CS = normal;
	}
	g_camera3D.SetPosition(m_position);
	g_camera3D.SetTarget(m_target);
	//カメラの更新。
	g_camera3D.Update();
	
}
void GameCamera::Render()
{
	
}