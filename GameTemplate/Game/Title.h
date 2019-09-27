#pragma once
#include"IGameObject.h"
#include"Sprite.h"
class Game;
class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render();

private:
	
	Sprite m_sprite;
};

