#include "stdafx.h"
#include "GameObjectManager.h"

//GameObjectManagerクラスのインスタンス作成
GameObjectManager g_goMgr;

GameObjectManager::GameObjectManager()
{
	m_deleteObject.reserve(32);
}

void GameObjectManager::Update()
{
	//登録済みのゲームオブジェクトの
	//Update関数を呼ぶ。
	for (auto go : m_goList)
	{
		go->Update();
	}
	//Render関数を呼ぶ。
	for (auto go : m_goList)
	{
		go->Render();
	}

	
	

	//全てのゲームオブジェクトの1フレーム分の処理が終わってから、削除する。
	for (auto& it = m_goList.begin();it !=m_goList.end();)
	{
		//もし削除リクエストを受けていたなら
		if ((*it)->IsRequestDelete() ==true)
		{
			//m_deleteObject.push_back((*it));
			//削除
			delete(*it);
			it = m_goList.erase(it);
		}
		//それ以外なら
		else {
			//次へ
			it++;
		}
	}

	for (auto& go : m_deleteObject)
	{
		delete (go);
	}
	m_deleteObject.clear();

}