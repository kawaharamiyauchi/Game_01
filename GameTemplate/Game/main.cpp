#include "stdafx.h"
#include "system/system.h"
#include"GameObjectManager.h"
#include "Player.h"
#include"BackGround.h"
#include "level/Level.h"
#include"QuestManager.h"
#include "Sprite.h"
#include"GameCamera.h"
#include"Game.h"
#include "Title.h"




///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	
	bool DebugDrawFlag = false;
	Title*m_title = GameObjectManager::instance().NewGO<Title>();
	//FontRender *m_font = GameObjectManager::instance().NewGO<FontRender>();
	

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		GameObjectManager::instance().BackUp();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		if (g_pad[0].IsPress(enButtonLB1) && g_pad[0].IsTrigger(enButtonRB1))
		{
			DebugDrawFlag = true;
		}

		//�����G���W���̍X�V�B
		g_physics.Update();
		//GameObjectManager::instance().Start();		
		GameObjectManager::instance().Update();  //�Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�B
		if (DebugDrawFlag) {
			g_physics.DebugDraw();
		}
		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}
