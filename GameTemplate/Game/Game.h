#pragma once
#include"IGameObject.h"
#include"GameObjectManager.h"
class Player;
class BackGround;
class GameCamera;
class Game:public IGameObject
{

	
public:
	Game();
	~Game();

	
	static Game* instance()
	{
		
		static Game*gam = g_goMgr.NewGO<Game>();
		return gam;
	}
	

	void Update();
	void Render();
	Player*m_player = nullptr;
	BackGround*m_background = nullptr;
	GameCamera *m_gamecamera = nullptr;
private:

	
	
};
