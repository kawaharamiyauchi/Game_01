#include "stdafx.h"
#include "GameObjectManager.h"

//GameObjectManager�N���X�̃C���X�^���X�쐬
GameObjectManager g_goMgr;

void GameObjectManager::Update()
{
	//�o�^�ς݂̃Q�[���I�u�W�F�N�g��
	//Update�֐����ĂԁB
	for (auto go : m_goList)
	{
		go->Update();
	}
	//Render�֐����ĂԁB
	for (auto go : m_goList)
	{
		go->Render();
	}

	//�S�ẴQ�[���I�u�W�F�N�g��1�t���[�����̏������I����Ă���A�폜����B
	for (auto it = m_goList.begin();it !=m_goList.end();)
	{
		//�����폜���N�G�X�g���󂯂Ă����Ȃ�
		if ((*it)->IsRequestDelete() ==true)
		{
			//�폜
			delete* it;
			it = m_goList.erase(it);
		}
		//����ȊO�Ȃ�
		else {
			//����
			it++;
		}
	}




}