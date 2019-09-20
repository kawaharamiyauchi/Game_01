#include "stdafx.h"
#include "system/system.h"
#include"GameObjectManager.h"
#include "Player.h"
#include"BackGround.h"
#include "level/Level.h"
#include "Sprite.h"
#include"GameCamera.h"
#include"Game.h"
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	
	//Game*m_game = g_goMgr.NewGO<Game>();
		auto m_game = Game::instance();
	////�v���C���[
	//Player*m_player = g_goMgr.NewGO<Player>();
	////map
	//BackGround*m_bg = g_goMgr.NewGO<BackGround>();
	//Sprite sprite;

	//�J�������������B
	/*g_camera3D.SetPosition({0.0f,250.0f,-300.0f});
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);*/
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�B
		g_goMgr.Update();
		
		/*if (GetAsyncKeyState('A'))
		{
			g_goMgr.DeleteGO(m_player);
		}*/
		/*CVector3 target = m_game->m_player->GetPosition();
		target.y += 2.0f;*/
		//g_camera3D.SetTarget(CVector3::Zero());
		//�J�����̍X�V�B
		//g_camera3D.Update();
		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}