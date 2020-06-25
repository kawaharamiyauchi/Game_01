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
class ItemBase;

class Game:public IGameObject
{

	
public:
	Game();
	~Game();

	enum StageType
	{
		//normal
		NA,
		NB,
		NC,
		ND,

		//return
		RBtoA,
		RCtoB,



	};
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
	
	void LoadGame(int LoadNum,StageType type);

	void ColliderInit(float radius, float height, CVector3 & position);

	bool GetIsNonGame()const
	{
		return isNonGame;
	}
	int GetStageNum()const
	{
		return StageNum;
	}
	bool GetPauseFlag()
	{
		return pauseFlag;
	}
	bool IsLookBoard()const
	{
		return islookBoard;
	}
	bool IsBackCamp()const
	{
		return m_backCampFlag;
	}
	void SetLookBoard(bool flag)
	{
		islookBoard = flag;
	}

	void SetPauseFlag(bool flag)
	{
		pauseFlag = flag;
	}
	CapsuleCollider m_collider;
	RigidBody m_rigidBody;

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
	ItemBase *m_ItemBase = nullptr;

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
		BtoD,
		BtoA,
		CtoB,
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
	CVector3 m_ghostsca =CVector3::Zero();
	int StageNum =0;
	Level m_level;
	Sprite m_sprite;
	/*C3DModelDraw m_unityChanModelDraw;
	C3DModelDraw m_bgModelDraw;*/
	bool GameOverFlag = false;
	bool GameLoadFlag = false;
	bool isNonGame = false;
	bool pauseFlag = false;
	bool m_backCampFlag = false;				 //ポーズ画面からキャンプに戻るかどうか
	bool islookBoard = false;
	GhostObject m_ghost[GhostTypeNum];
	CSoundSource m_BGM[BGMTypeNum];
	

};
