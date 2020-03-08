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
#include "FontRender.h"

class Player;
class BackGround;
class GameCamera;
class Dragon;
class Fade;
class QuestManager;
class LittleEnemy;
class FontRender;
class Item;
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
	void InitQuest(const wchar_t*filePath);
	void Update();
	void Render();
	void LoadGame(int LoadNum);

	bool GetIsNonGame()const
	{
		return isNonGame;
	}
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
	QuestManager *m_quest =nullptr;
	LittleEnemy *m_little[5] = { nullptr };
	FontRender *m_font = nullptr;
	Item *m_Item = nullptr;
private:
	enum GhostType
	{	
		quest_board,
		//   Stage Information
		//
		//A(stage1)->B(stage2)----------->D(stage4)
		//				↳C(stage3)------⇗
		AtoB,
		BtoC,
		CtoB,
		BtoD,
		CtoD,
		GhostTypeNum

	};
	enum BGMType
	{
		camp,
		wind,
		Boss,
		GameClear,
		GameOver,
		BGMTypeNum
	};
	wchar_t*LoadGameText;
	int StageNum =0;
	Level m_level;
	Sprite m_sprite;
	/*C3DModelDraw m_unityChanModelDraw;
	C3DModelDraw m_bgModelDraw;*/
	bool GameOverFlag = false;
	bool GameLoadFlag = false;
	bool isNonGame = false;

	GhostObject m_ghost[GhostTypeNum];
	CSoundSource m_BGM[BGMTypeNum];
};
