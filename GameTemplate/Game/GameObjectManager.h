#pragma once
#include "IGameObject.h"
#include <iostream>
using namespace std;
class GameObjectManager
{
public:
	GameObjectManager();
	
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// ゲームオブジェクトを追加
	/// </summary>
	/// <param name ="name">作成するゲームオブジェクト</param>
	template<class T>
	T*NewGO()
	{
		T*newObj = new T;
		m_goList.push_back(newObj);
		
		return newObj;
	}

	/// <summary>
	/// ゲームオブジェクトを検索。
	/// </summary>
	/// 
	/// 
	/*void FindGO( const string name)
	{
		for (auto it = m_goList.begin(); it != m_goList.end;it++)
		{
			
		}
	}
*/

	/// /// <summary>
	/// ゲームオブジェクトをリストから削除。
	/// </summary>
	///<param name ="go">削除するゲームオブジェクト</param>
	void DeleteGO(IGameObject* go)
	{
		for (auto it = m_goList.begin(); it != m_goList.end(); it++)
		{
			if ((*it) == go) {

				go->RequestDelete();
				//見つかった。
				//リストから削除する。
				//m_goList.erase(it);
				//インスタンス自体も削除。
				//delete go;
				////削除できたので終わり。
				//return;
			}
		}
	}
	



private:
	//ゲームオブジェクトのリスト
	std::vector<IGameObject*> m_goList;

	std::vector<IGameObject*> m_deleteObject;

};

extern GameObjectManager g_goMgr;