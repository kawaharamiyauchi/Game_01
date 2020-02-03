#pragma once
#include "SpriteRender.h"

class QuestData {

public:
	QuestData(
		const wchar_t*questName
		) :
		m_questName(questName)
	{
	}
private:
	std::wstring m_questName;
};
class QuestManager
{
public:


	static QuestManager& instance()
	{
		static QuestManager instance;
		return instance;
	}
	QuestManager();
	~QuestManager();
	bool Load(const wchar_t * filePath);
	void Update(){}
	enum LogoType {
		GameClear,
		GameOver,

	};
private:
	bool m_isClear = false;
	bool m_isOver = false;

};

