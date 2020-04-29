#include "stdafx.h"
#include "QuestManager.h"
#include"UI.h"
#include "Game.h"
#include"Dragon.h"
#include <codecvt> 
#include <cstdio>
#include < locale.h >
#include<iostream>
string INPUT_FOLDER_NAME = "Assets/QuestData/";




void QuestManager::ResetPalam()
{
	QuestPoint = 0;
	m_targetdieflag = false;
	m_questNum = 0;
	isOnQuest = false;
	m_state = normal;
}

QuestManager::QuestManager()
{
}


QuestManager::~QuestManager()
{
}

/// <summary>
/// 拡張子が.queであるファイルの名前を抽出
/// </summary>
/// <param name="dir_name"></param>
/// <returns></returns>
vector<string>GetQuestFileName(string dir_name)
{
	HANDLE Find;

	WIN32_FIND_DATA win32fd;
	std::vector<std::string> file_names;


	//.que拡張子のファイルを読み込む。
	std::string extension = "que";
	string search_name = dir_name + "*." + extension;
	Find = FindFirstFile(search_name.c_str(), &win32fd);

	do {

		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		}
		else {
			file_names.push_back(win32fd.cFileName);
			//m_questList.push_back()
		

		}

	} while (FindNextFile(Find, &win32fd));

	FindClose(Find);
	return file_names;

}
bool QuestManager::Load(const wchar_t*filePath)
{
	//m_state = normal;

	std::wstring wadd = L"Assets/QuestData/";
	wadd += filePath;
	
	FILE* fp = _wfopen(wadd.c_str(), L"rb");


	if (fp == nullptr) {
		return false;
	}
	unsigned int nameCount = 0;
	//クエストの名前の文字数を読み込む。
	fread(&nameCount, sizeof(nameCount), 1, fp);
	char* name = new char[nameCount + 1];
	fread(name, nameCount + 1, 1, fp);
	unsigned int summrycount = 0;
	fread(&summrycount, sizeof(summrycount),1,fp);
	char *summry = new char[summrycount + 1];
	fread(summry, summrycount + 1, 1, fp);
	unsigned int questType = 0;
	fread(&questType, sizeof(questType), 1, fp);
	unsigned int targetType = 0;
	fread(&targetType, sizeof(targetType), 1, fp);
	unsigned int targetNum = 0;
	fread(&targetNum, sizeof(targetNum), 1, fp);
	unsigned int prizeMoney = 0;
	fread(&prizeMoney, sizeof(prizeMoney), 1, fp);
	unsigned int time = 0;
	fread(&time, sizeof(time), 1, fp);
	unsigned int reqNameCount = 0;
	fread(&reqNameCount,sizeof(reqNameCount), 1, fp);
	char *requesterName = new char[reqNameCount + 1];
	fread(requesterName, reqNameCount + 1, 1, fp);
	setlocale(LC_ALL, "japanese");
	errno_t err = 0;
	size_t wLen = 0;

	fclose(fp);

	//文字列型変換&文字列格納
	err = mbstowcs_s(&wLen, m_infoDisp.m_questName,sizeof(name),name, _TRUNCATE);
	err = mbstowcs_s(&wLen, m_infoDisp.m_questSummry, sizeof(summry)+2, summry, _TRUNCATE);
	err = mbstowcs_s(&wLen, m_infoDisp.m_requesterName, sizeof(requesterName), requesterName, _TRUNCATE);

	//各パラメータ格納
	m_infoDisp.m_questType = (QuestType)questType;
	m_infoDisp.m_prizeMoney = prizeMoney;
	m_infoDisp.m_targetType = targetType;
	m_infoDisp.m_targetNum = targetNum;
	m_infoDisp.m_limitTime = time;
	
	return true;
}
void QuestManager::Update()
{
	m_state = normal;
	auto &m_UI = Game::instance()->m_UI;
	auto &m_dragon = Game::instance()->m_dragon;
	auto &m_player = Game::instance()->m_player;
	
	m_targetdieflag = false;
	if (m_info.m_targetNum <= QuestPoint&&isOnQuest)
	{
		m_state = clear;
	}
	if (m_info.m_questType == QuestType::Collect)
	{

	}
	if (m_info.m_questType == QuestType::Littlebattle)
	{
		//QuestPoint++;
	
	}
	/*if (Game::instance()->GetStageNum() == 3) {
		
		if (m_info.m_questType == QuestType::Bossbattle) {
			if (m_dragon->GetDragonInfo().HP <= 0)
			{
				m_targetdieflag = true;
			}
			if (m_dragon->GetDragonInfo().isEnd == true)
			{
				QuestPoint=1;
			}

			
		}
		
	}*/

	
	if (m_player != nullptr)
	{
		if (m_player->GetPlayerInformation().isEnd == true)
		{
			m_state = over;
		}
	}	
	vector<string>file_names = GetQuestFileName(INPUT_FOLDER_NAME);
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;

	//string→wstring
	std::wstring fn = cv.from_bytes(file_names[m_questNum]);
	wcscpy(selectfileName, fn.c_str());
	
	if (Game::instance()->IsLookBoard()) {

		
		if (g_pad[0].IsTrigger(enButtonRight))
		{
			if (m_questNum < file_names.size()-1)
			{
				m_questNum++;
			}
		}
		if (g_pad[0].IsTrigger(enButtonLeft))
		{
			if (m_questNum > 0)
			{
				m_questNum--;
			}
		}
		Load(selectfileName);
		if (g_pad[0].IsTrigger(enButtonRB1))
		{
			m_info = m_infoDisp;
			isOnQuest = true;
			addmoney = m_infoDisp.m_prizeMoney / 100;
		}
		
	}
	
}
