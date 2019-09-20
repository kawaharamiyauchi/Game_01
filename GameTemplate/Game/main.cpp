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
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	
	//Game*m_game = g_goMgr.NewGO<Game>();
		auto m_game = Game::instance();
	////プレイヤー
	//Player*m_player = g_goMgr.NewGO<Player>();
	////map
	//BackGround*m_bg = g_goMgr.NewGO<BackGround>();
	//Sprite sprite;

	//カメラを初期化。
	/*g_camera3D.SetPosition({0.0f,250.0f,-300.0f});
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);*/
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		//ゲームオブジェクトマネージャーの更新。
		g_goMgr.Update();
		
		/*if (GetAsyncKeyState('A'))
		{
			g_goMgr.DeleteGO(m_player);
		}*/
		/*CVector3 target = m_game->m_player->GetPosition();
		target.y += 2.0f;*/
		//g_camera3D.SetTarget(CVector3::Zero());
		//カメラの更新。
		//g_camera3D.Update();
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}