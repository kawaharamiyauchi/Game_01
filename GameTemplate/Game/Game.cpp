#include "stdafx.h"
#include"BackGround.h"
#include "GameCamera.h"
#include"GameObjectManager.h"
#include"QuestManager.h"
#include"Dragon.h"
#include"Title.h"
#include"level/Level.h"
#include"LittleEnemy.h"
#include "Player.h"

Game::Game()
{
	
	Fade::instance().FadeOut();
	StageNum = 0;
	auto m_manager = &GameObjectManager::instance();
	m_quest = &QuestManager::instance();
	InitQuest(L"Assets/ModelData/MH01.que");
	m_Item = m_manager->NewGO<Item>();

	m_level.Init(L"Assets/level/MH_Stage0-0.tkl",[&](const LevelObjectData& objData)
		{
			if (wcscmp(objData.name, L"MH_0-0")==0)
			{
				
				m_background = m_manager->NewGO<BackGround>();
				m_background->LoadStage(0);
				m_background->SetPosition(objData.position);
				return true;
			}
			if (wcscmp(objData.name, L"hunter03")==0)
			{
				m_player = m_manager->NewGO<Player>();
				m_player->SetPosition(objData.position);
				m_player->SetRotation(objData.rotation);
				return true;
			}
			if (wcscmp(objData.name, L"bord_ghorst") == 0)
			{
				
				return true;
			}
			if (wcscmp(objData.name, L"Quest_bord") == 0)
			{
				/*m_little = m_manager->NewGO<LittleEnemy>();
				m_little->SetCharaConPos(objData.position);*/
				return true;
			}
			if (wcscmp(objData.name, L"unityChan") == 0)
			{
				return true;
			}
			if (wcscmp(objData.name, L"nextstage") == 0)
			{
				m_ghost[1].CreateBox(objData.position, objData.rotation, {2600.0f,200.0f,1600.0f});
				return true;
			}
			
			return false;
		});

	/*m_BGM[camp].Init(L"Assets/sound/camp.wav");
	m_BGM[camp].Play(true);*/
	m_BGM[wind].Init(L"Assets/sound/wind1.wav");
	m_BGM[wind].Play(true);
	m_BGM[GameClear].Init(L"Assets/sound/GameClear.wav");
	m_BGM[GameOver].Init(L"Assets/sound/GameOver.wav");
	m_BGM[Boss].Init(L"Assets/sound/Boss01.wav");
	m_gamecamera = m_manager->NewGO<GameCamera>();
	m_UI = m_manager->NewGO<UI>();
		
}

Game::~Game()
{	
}
void Game::DeleteGame()
{
	if (m_background != nullptr) {
		GameObjectManager::instance().DeleteGO(m_background);
	}
	if (m_dragon != nullptr) {
		GameObjectManager::instance().DeleteGO(m_dragon);
	}
	if (m_little != nullptr) {
		for (int i = 0; i < 5; i++) {
			GameObjectManager::instance().DeleteGO(m_little[i]);
		}
	}
	if (m_player != nullptr) {
		GameObjectManager::instance().DeleteGO(m_player);
	}
	if (m_gamecamera != nullptr) {

		GameObjectManager::instance().DeleteGO(m_gamecamera);
	}

	if (m_UI != nullptr) {
		GameObjectManager::instance().DeleteGO(m_UI);
	}
	m_ghost[1].Release();
}
void Game::EventChange()
{
	if (m_player->GetPlayerInformation().HP < 0.1f)
	{
		GameOverFlag = true;
	}
}
void Game::InitQuest(const wchar_t*filePath)
{
	std::wstring questFilePath = filePath;
	int pos = (int)questFilePath.find(L".que");
	m_quest->instance().Load(questFilePath.c_str());
}
void Game::Update()
{
	//EventChange();
	
	if (g_pad[0].IsTrigger(enButtonSelect)&&!isNonGame)
	{
		
		DeleteGame();
		GameObjectManager::instance().NewGO<Title>();
	
		isNonGame = true;
		StageNum = 0;
	}
	if (m_quest->GetGameState() == QuestManager::clear)
	{
		m_BGM[wind].Stop();
		m_BGM[GameClear].SetVolume(10.0f);
		m_BGM[GameClear].Play(false);
	}
	if (m_quest->GetGameState() == QuestManager::over)
	{
		m_BGM[wind].Stop();
		m_BGM[GameOver].Play(false);
	}
	if (!isNonGame) {

		g_physics.ContactTest(m_player->GetcharaCon(), [&](const btCollisionObject & contactObject)
			{
				if (m_ghost[AtoB].IsSelf(contactObject))
				{
					Fade::instance().FadeIn();
				
					if (Fade::instance().IsFade() == false)
					{
						
						DeleteGame();
						m_quest->instance().PlayerBackUp(m_player->GetPlayerInformation());
						LoadGame(1);
						m_ghost[AtoB].Release();
					}
				}
				if (m_ghost[BtoD].IsSelf(contactObject))
				{
					Fade::instance().FadeIn();

					if (Fade::instance().IsFade() == false)
					{

						DeleteGame();
						m_quest->instance().PlayerBackUp(m_player->GetPlayerInformation());
						LoadGame(3);
						m_ghost[BtoD].Release();
						m_ghost[BtoC].Release();

					}
				}
				
		});
		
		m_quest->Update();
	}
	//m_font->SetColor(CVector3::Zero());
}
void Game::Render()
{
	

}

void Game::LoadGame(int LoadNum)
{
	Fade::instance().FadeOut();
	if (!m_BGM[wind].IsPlaying())
	{
		m_BGM[wind].Play(true);
	}
	if (LoadNum == 3)
	{
		m_BGM[Boss].Play(true);
	}
	InitQuest(L"Assets/ModelData/MH01.que");
	StageNum = LoadNum;
	isNonGame = false;
	auto m_manager = &GameObjectManager::instance();
	switch (LoadNum)
	{
	case(0):
		m_level.Init(L"Assets/level/MH_Stage0-0.tkl", [&](const LevelObjectData& objData)
			{
				if (wcscmp(objData.name, L"MH_0-0") == 0)
				{
					m_background = m_manager->NewGO<BackGround>();
					m_background->LoadStage(LoadNum);
					m_background->SetPosition(objData.position);
					return true;
				}
				if (wcscmp(objData.name, L"hunter03") == 0)
				{
					
					m_player = m_manager->NewGO<Player>();
					//m_player->SetPlInfo(m_quest->instance().GetBackUp());
					m_player->SetCharaConPos(objData.position);
					m_player->SetPosition(objData.position);
					m_player->SetRotation(objData.rotation);
					return true;
				}
				if (wcscmp(objData.name, L"bord_ghorst") == 0)
				{
					m_ghost[0].CreateBox(objData.position, objData.rotation, objData.scale);
					return true;
				}
				if (wcscmp(objData.name, L"Quest_bord") == 0)
				{
					//m_ghost[1].CreateBox(objData.position, objData.rotation, objData.scale);
					return true;
				}
				if (wcscmp(objData.name, L"nextstage") == 0)
				{
					m_ghost[1].CreateBox(objData.position, objData.rotation, { 2600.0f,200.0f,1600.0f });
					return true;
				}
				if (wcscmp(objData.name, L"unityChan") == 0)
				{
					return true;
				}
				return false;
			});
		break;
	case(1):
		m_level.Init(L"Assets/level/MH_Stage0-2.tkl", [&](const LevelObjectData& objData)
			{
				if (wcscmp(objData.name, L"MH_Stage1-2") == 0)
				{
					
					m_background = m_manager->NewGO<BackGround>();
					m_background->SetRotation(objData.rotation);
					m_background->LoadStage(1);
					m_background->SetPosition(objData.position);
					
					return true;
				}
				if (wcscmp(objData.name, L"hunter03") == 0)
				{
					m_player = m_manager->NewGO<Player>();
					m_player->SetPlInfo(m_quest->instance().GetBackUp());
					m_player->SetCharaConPos(objData.position);
					m_player->SetPosition(objData.position);
					m_player->SetRotation(objData.rotation);
					return true;
				}

				if (wcscmp(objData.name, L"LBD_00") == 0)
				{
					m_little[0] = m_manager->NewGO < LittleEnemy>();
					m_little[0]->SetCharaConPos(objData.position);
					m_little[0]->SetRotation(objData.rotation);
					return true;
				}
				if (wcscmp(objData.name, L"LBD_01") == 0)
				{
					m_little[1] = m_manager->NewGO < LittleEnemy>();
					m_little[1]->SetCharaConPos(objData.position);
					m_little[1]->SetRotation(objData.rotation);
					return true;
				}
				if (wcscmp(objData.name, L"LBD_02") == 0)
				{
					m_little[2] = m_manager->NewGO < LittleEnemy>();
					m_little[2]->SetCharaConPos(objData.position);
					m_little[2]->SetRotation(objData.rotation);
					return true;
				}
				if (wcscmp(objData.name, L"LBD_03") == 0)
				{
					m_little[3] = m_manager->NewGO < LittleEnemy>();
					m_little[3]->SetCharaConPos(objData.position);
					m_little[3]->SetRotation(objData.rotation);
					return true;
				}
				if (wcscmp(objData.name, L"LBD_04") == 0)
				{
					m_little[4] = m_manager->NewGO < LittleEnemy>();
					m_little[4]->SetCharaConPos(objData.position);
					m_little[4]->SetRotation(objData.rotation);
					return true;
				}
				if (wcscmp(objData.name, L"BtoC") == 0)
				{
					m_ghost[BtoC].CreateBox(objData.position, objData.rotation, { 2000.0f, 200.0f, 2000.0f });
					return true;
				}
				if (wcscmp(objData.name, L"BtoD") == 0)
				{
					m_ghost[BtoD].CreateBox(objData.position, objData.rotation, { 1000.0f, 200.0f, 1000.0f });
					return true;
				}
				
				return false;
			});
		break;
	case(2):
		break;
	case(3):
		m_level.Init(L"Assets/level/MH_Stage0-4.tkl", [&](const LevelObjectData& objData)
			{
				if (wcscmp(objData.name, L"Desert stage") == 0)
				{

					m_background = m_manager->NewGO<BackGround>();
					m_background->LoadStage(3);
					m_background->SetPosition(objData.position);
					return true;
				}
				if (wcscmp(objData.name, L"hunter03") == 0)
				{
					m_player = m_manager->NewGO<Player>();
					m_player->SetPlInfo(m_quest->instance().GetBackUp());
					m_player->SetCharaConPos(objData.position);
					m_player->SetPosition(objData.position);
					m_player->SetRotation(objData.rotation);
					return true;
				}

				if (wcscmp(objData.name, L"DragonBoar") == 0)
				{
					m_dragon = m_manager->NewGO<Dragon>();
					m_dragon->SetPosition(objData.position);
					m_dragon->SetRotation(objData.rotation);
					return true;
				}
				/*if (wcscmp(objData.name, L"Limit") == 0)
				{

				}*/
				return false;
			});
		break;
	default:
		break;
	}
	
	m_gamecamera = m_manager->NewGO<GameCamera>();
	
	m_UI = m_manager->NewGO<UI>();
	
}




