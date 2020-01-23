#pragma once
#include"IGameObject.h"
#include"GameObjectManager.h"
#include"Sprite.h"
#include "UI.h"
#include "Fade.h"
#include "ShadowMap.h"
#include"C3DModelDraw.h"
#include "level/Level.h"
#include "GhostObject.h"


class Player;
class BackGround;
class GameCamera;
class Dragon;
class Fade;
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
		static Game *gam = GameObjectManager::instance().NewGO<Game>();
		return gam;
	}
	ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}
	void DeleteGame();
	void EventChange();
	void Update();
	void Render();
	void LoadGame(int LoadNum);
	int GetStageNum()const
	{
		return StageNum;
	}
	Player*m_player = nullptr;		//プレイヤー
	BackGround*m_background = nullptr;		
	GameCamera *m_gamecamera = nullptr;
	Dragon *m_dragon =  nullptr ;
	UI*m_UI = nullptr;
	Fade *m_fade = nullptr;
	ShadowMap m_shadowMap;
	
private:
	wchar_t*LoadGameText;
	int StageNum =0;
	Level m_level;
	Sprite m_sprite;
	C3DModelDraw m_unityChanModelDraw;
	C3DModelDraw m_bgModelDraw;
	bool GameOverFlag = false;
	bool GameLoadFlag = false;
	bool isNonGame = false;
	GhostObject m_ghost[2];

	//Game* gam = nullptr;
};
