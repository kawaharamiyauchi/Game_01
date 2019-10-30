#pragma once
#include"IGameObject.h"
#include"Sprite.h"
#include"SpriteRender.h"
class Game;
class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render();

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

private:
	
	SpriteRender*m_spriteRender;
	Sprite m_sprite;
	CVector3 m_scale = CVector3::One();
	CVector3 m_position = CVector3::Zero();


};

