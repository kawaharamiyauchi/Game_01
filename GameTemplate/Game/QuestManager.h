#pragma once
#include "SpriteRender.h"
class QuestManager
{
public:
	QuestManager();
	~QuestManager();
	enum LogoType {
		GameClear,
		GameOver,

	};
private:
	bool m_isClear = false;
	bool m_isOver = false;

};

