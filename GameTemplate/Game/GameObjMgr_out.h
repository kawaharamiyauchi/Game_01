/*
 *@brief	CGameObjectのマネージャー
*/

#ifndef INCLUDE_GameObjectManager_h_
#define INCLUDE_GameObjectManager_h_

#include "GameObject.h"

namespace MyEngine {
	struct SRenderContextMap;
	class CpreRender;
	/*
	 *@brief	GameObjectのマネージャー
	 */
	class CGameObjectManager {
		
	private:
		CGameObjectManager() :
			m_gameObjectPriorityMax(0)
		{
		}
		~CGameObjectManager()
		{
		}
		/*
		@brief	ゲームオブジェクトの名前登録
		*/
		static unsigned int MakeGameNameKey(const char*objectName)
		{

		}
		/*!
		@brief	インスタンスの取得。
		*/
		static CGameObjectManager& instance()
		{
			static CGameObjectManager instance;
			return instance;
		}

		/// <summary>ゲームオブジェクトの作成
		/// 
		/// @param[in]		objectName	オブジェクト名。
		/// 
		template<class T,class... TArgs>
		T*NewGameObject(GameObjectPrio prio, const char*objectName)
		{
			(void*)objectName;
			T*newObject = new T();
			newObject->Awake();
			newObject->SetMarkNewFromGame
		}


	};




#endif // !INCLUDE_GameObjectManager_h_
