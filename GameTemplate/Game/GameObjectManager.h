#pragma once
#include "IGameObject.h"
#include <iostream>
using namespace std;
class GameObjectManager
{
public:
	GameObjectManager();
	
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �Q�[���I�u�W�F�N�g��ǉ�
	/// </summary>
	/// <param name ="name">�쐬����Q�[���I�u�W�F�N�g</param>
	template<class T>
	T*NewGO()
	{
		T*newObj = new T;
		m_goList.push_back(newObj);
		
		return newObj;
	}

	/// <summary>
	/// �Q�[���I�u�W�F�N�g�������B
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
	/// �Q�[���I�u�W�F�N�g�����X�g����폜�B
	/// </summary>
	///<param name ="go">�폜����Q�[���I�u�W�F�N�g</param>
	void DeleteGO(IGameObject* go)
	{
		for (auto it = m_goList.begin(); it != m_goList.end(); it++)
		{
			if ((*it) == go) {

				go->RequestDelete();
				//���������B
				//���X�g����폜����B
				//m_goList.erase(it);
				//�C���X�^���X���̂��폜�B
				//delete go;
				////�폜�ł����̂ŏI���B
				//return;
			}
		}
	}
	



private:
	//�Q�[���I�u�W�F�N�g�̃��X�g
	std::vector<IGameObject*> m_goList;

	std::vector<IGameObject*> m_deleteObject;

};

extern GameObjectManager g_goMgr;