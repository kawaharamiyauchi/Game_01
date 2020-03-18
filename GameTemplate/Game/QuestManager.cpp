#include "stdafx.h"
#include "QuestManager.h"
#include"UI.h"
#include "Game.h"
#include"Dragon.h"
//#include<iostream>
//#include<string>
//using namespace std;

string INPUT_FOLDER_NAME = "Assets/QuestData/";


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
			OutputDebugStringA(win32fd.cFileName);
			
		}

	} while (FindNextFile(Find, &win32fd));

	FindClose(Find);
	return file_names;

}

QuestManager::QuestManager()
{
}


QuestManager::~QuestManager()
{
}
bool QuestManager::Load(const wchar_t*filePath)
{
	m_state = normal;
	FILE* fp = _wfopen(filePath, L"rb");
	if (fp == nullptr) {
		return false;
	}
	int nameCount = 0;
	//クエストの名前の文字数を読み込む。
	fread(&nameCount, 1, 1, fp);
	char* name = new char[nameCount + 2];
	fread(name, nameCount + 1, 1, fp);

	int BossType = 0;
	fread(&BossType, sizeof(BossType), 1, fp);
	float Boss_HP = 0.0f;
	fread(&Boss_HP, sizeof(Boss_HP), 1, fp);
	int zakoType = 0;
	fread(&zakoType, sizeof(zakoType), 1, fp);
	float zako_HP = 0.0f;
	fread(&zako_HP, sizeof(zako_HP), 1, fp);
	fclose(fp);
	strcat(name,"\n");
	OutputDebugStringA(name);
	return true;
}
void QuestManager::Update()
{
	m_state = normal;
	auto &m_UI = Game::instance()->m_UI;
	auto &m_dragon = Game::instance()->m_dragon;
	auto &m_player = Game::instance()->m_player;
	if (Game::instance()->GetStageNum() == 3) {
		if (m_dragon->GetDragonInfo().isEnd == true)
		{			
			m_state = clear;
		}
	}
	if (m_player != nullptr)
	{
		if (m_player->GetPlayerInformation().isEnd == true)
		{
			m_state = over;
		}
	}	
	vector<string> file_names = GetQuestFileName(INPUT_FOLDER_NAME);
	for (auto f : file_names)
	{
		/*LPCSTR a = f[];
		OutputDebugString(f);*/
	}

}
