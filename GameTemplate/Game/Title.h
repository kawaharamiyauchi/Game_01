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

	void SetPosition(CVector3 pos,int type)
	{
		m_position[type] = pos;
	}

private:
	enum SpriteType {
		
		Menu,
		GameStart_Grey,
		GameStart_Yellow,
		Exit_Grey,
		
		Exit_Yellow,
		Triangle,
		
		Typenum
	};
	SpriteRender* m_spriteRender[Typenum];
	Sprite m_sprite;
	CVector3 m_scale = CVector3::One();
	CVector3 m_position[Typenum] = { CVector3::Zero() };
	bool StartFlag = true;
	bool ExitFlag = false;

};

