#pragma once
#include "Player.h"
#include<iostream>
#include<string>


class QuestManager
{
public:

	enum QuestType
	{
		Collect,
		Littlebattle,
		Bossbattle
	};

	struct QuestInfo
	{

		wchar_t m_questFileName[255];
		wchar_t m_questName[255];
		wchar_t m_questSummry[255];
		QuestType m_questType;
		int m_targetType = 0;
		int m_targetNum = 0;
		int m_prizeMoney = 0;
		int m_limitTime = 0;
		wchar_t m_requesterName[255];


	};
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
	QuestInfo GetDispInfo()const
	{
		return m_infoDisp;
	}
	QuestInfo GetQuestInfo()const
	{
		return m_info;
	}
	bool GetTargetDieFlag()const
	{
		return m_targetdieflag;
	}
	void SetTargetDieFlag(bool flag)
	{
		m_targetdieflag = flag;
	}
	bool IsOnQuest()const
	{
		return isOnQuest;
	}	
	int GetQuestPoint()const
	{
		return QuestPoint;
	}
	void AddQuestPoint()
	{
		QuestPoint++;
	}
	/// <summary>
	/// Œ»İ‚ÌŠ‹à‚ğæ“¾iGet PrizeMoney() ‚ÆŠÔˆá‚¦‚È‚¢‚æ‚¤‚Éj 
	/// </summary>
	/// <returns>Š‹à</returns>
	int GetMoney()
	{
		return m_money;
	}
	/// <summary>
	/// Š‹à‚É•ñV‚ğ‰ÁZ
	/// </summary>
	bool GetPrizeMoney()
	{
		
		if (0< m_info.m_prizeMoney) {
			m_money +=addmoney;
			m_info.m_prizeMoney -= addmoney;
			return true;
		}
		else return false;
		
	}
	void ResetPalam();
	QuestManager();
	~QuestManager();

	//vector<string> GetQuestFileName(string dir_name);
	bool Load(const wchar_t * filePath);
	void Update();
	
private:
	GameState m_state;
	Player::plinfo m_backUp;
	bool m_targetdieflag =false;
	
	int QuestPoint = 0;
	int m_questNum = 0;
	QuestInfo m_infoDisp;
	QuestInfo m_info;
	bool isOnQuest =false;
	wchar_t selectfileName[255];


	int m_money = 1000;
	int addmoney = 0;
};
