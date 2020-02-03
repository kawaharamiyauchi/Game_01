#include "stdafx.h"
#include "QuestManager.h"


QuestManager::QuestManager()
{
}


QuestManager::~QuestManager()
{
}
bool QuestManager::Load(const wchar_t*filePath)
{
	FILE* fp = _wfopen(filePath, L"rb");
	if (fp == nullptr) {
		return false;
	}
	int nameCount = 0;
	//クエストの名前の文字数を読み込む。
	fread(&nameCount, 1, 1, fp);
	char* name = new char[nameCount + 1];
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
void Update()
{
	
}
