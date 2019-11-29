#pragma once
#include"IGameObject.h"
#include"GameObjectManager.h"
#include"Sprite.h"
#include "UI.h"
#include "ShadowMap.h"
#include"C3DModelDraw.h"
class Player;
class BackGround;
class GameCamera;
class Dragon;
class Game:public IGameObject
{

	
public:
	Game();
	~Game();

	/// <summary>
	/// シングルトンパターン
	/// </summary>
	/// <returns>Gameクラス</returns>
	static Game* instance()
	{
		
		static Game* gam = GameObjectManager::instance().NewGO<Game>();
		return gam;
	}
	ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}

	void Update();
	void Render();
	Player*m_player = nullptr;				//プレイヤー
	BackGround*m_background = nullptr;		
	GameCamera *m_gamecamera = nullptr;
	Dragon *m_dragon = nullptr;
	UI*m_UI = nullptr;
	ShadowMap m_shadowMap;
	
private:
	Sprite m_sprite;
	C3DModelDraw m_unityChanModelDraw;
	C3DModelDraw m_bgModelDraw;
	
	CVector3 m_unityChanPos = { 0.0f, 0.0f, 0.0f };	//ユニティちゃんの座標。
	
};
