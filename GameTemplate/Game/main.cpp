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
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	
	bool DebugDrawFlag = false;
	Title*m_title = GameObjectManager::instance().NewGO<Title>();
	//FontRender *m_font = GameObjectManager::instance().NewGO<FontRender>();
	

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		
		//描画開始。
		g_graphicsEngine->BegineRender();
		GameObjectManager::instance().BackUp();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		if (g_pad[0].IsPress(enButtonLB1) && g_pad[0].IsTrigger(enButtonRB1))
		{
			DebugDrawFlag = true;
		}

		//物理エンジンの更新。
		g_physics.Update();
		//GameObjectManager::instance().Start();		
		GameObjectManager::instance().Update();  //ゲームオブジェクトマネージャーの更新。
		if (DebugDrawFlag) {
			g_physics.DebugDraw();
		}
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}
