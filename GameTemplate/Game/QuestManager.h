#pragma once
#include "Player.h"
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
	enum GameState
	{
		normal,
		clear,
		over
	};

	void PlayerBackUp(Player::plinfo info)
	{
		m_backUp = info;
	}
	Player::plinfo GetBackUp()
	{
		return m_backUp;
	}
	/*void SetIsClear(bool flag)
	{
		m_isClear = flag;
	}
	void SetIsGameOver(bool flag)
	{
		m_isOver = flag;
	}*/
	void SetGameState(GameState state)
	{
		m_state = state;
	}
	GameState GetGameState()const
	{
		return m_state;
	}
	static QuestManager& instance()
	{
		static QuestManager instance;
		return instance;
	}
	QuestManager();
	~QuestManager();
	bool Load(const wchar_t * filePath);
	void Update();
	
private:
	GameState m_state;
	Player::plinfo m_backUp;

};

