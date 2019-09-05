/*
 *@brief	CGameObject�̃}�l�[�W���[
*/

#ifndef INCLUDE_GameObjectManager_h_
#define INCLUDE_GameObjectManager_h_

#include "GameObject.h"

namespace MyEngine {
	struct SRenderContextMap;
	class CpreRender;
	/*
	 *@brief	GameObject�̃}�l�[�W���[
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
		@brief	�Q�[���I�u�W�F�N�g�̖��O�o�^
		*/
		static unsigned int MakeGameNameKey(const char*objectName)
		{

		}
		/*!
		@brief	�C���X�^���X�̎擾�B
		*/
		static CGameObjectManager& instance()
		{
			static CGameObjectManager instance;
			return instance;
		}

		/// <summary>�Q�[���I�u�W�F�N�g�̍쐬
		/// 
		/// @param[in]		objectName	�I�u�W�F�N�g���B
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
