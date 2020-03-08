#pragma once


#include "stdafx.h"
#include "IGameObject.h"
#include <iostream>
#include "RenderTarget.h"
#include "Sprite.h"
#include "Fade.h"
#include "PostEffect.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
using namespace std;
class GameObjectManager
{
public:

	struct EffekseerTool
	{
		//Effekseer�}�l�[�W���Ǘ��B
		Effekseer::Manager*				m_effekseerManager = nullptr;
		EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;

		Effekseer::Effect* m_sampleEffect = nullptr;
		Effekseer::Handle m_playEffectHandle = -1;
	};
	static GameObjectManager& instance()
	{
		static GameObjectManager instance;
		return instance;
	}

	/// <summary>
	/// ���C�������_�����O�^�[�Q�b�g���擾�B
	/// </summary>
	/// 
	RenderTarget* GetMainRenderTarget()
	{
		return &m_mainRenderTarget;
	}
private:

	

	GameObjectManager();
	~GameObjectManager();
public:

	void Start();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	void BackUp();
	
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
				go->OnDestroy();
			}
		}
	}
	void SetLightCameraPos(CVector3 pos)
	{
		LightCameraPos = pos;
		

	}
private:
	void Draw();
	/// <summary>
	/// �v�������_�����O�B
	/// </summary>
	void PreRender();
	/// <summary>
	/// �t�H���[�h�����_�����O(�ʏ�̕`�悾�ƍl����OK)
	/// </summary>
	void ForwordRender();
	/// <summary>
	/// �|�X�g�����_�����O
	/// </summary>
	void PostRender();
	/// <summary>
	/// �J�������������B
	/// </summary>
	void InitCamera();
public:
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�̐؂�ւ��B
	/// </summary>
	/// <param name="d3dDeviceContext">D3D�f�o�C�X�R���e�L�X�g</param>
	/// <param name="renderTarget">�����_�����O�^�[�Q�b�g</param>
	/// <param name="viewport">�r���[�|�[�g</param>
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
public:
	void CountPlus()
	{
		GameCount++;
	}
	int GetGameCount()const
	{
		return GameCount;
	}
	void SetExecuteSpeed(int speed)
	{
		ExecuteSpeed = speed;
	}
	/// <summary>
	/// Effekseer�̏������B
	/// </summary>
	void InitEffekseer();
private:
	int GameCount = 0;
	int ExecuteSpeed = 100;
	int SpeedCount = 0;
	CVector3 LightCameraPos = CVector3::Zero();
	Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	RenderTarget m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B												
	PostEffect m_postEffect;
	CVector4 m_ligPower = { 2.0f,2.0f,2.0f,1.0f };
	//�Q�[���I�u�W�F�N�g�̃��X�g	
	std::vector<IGameObject*> m_goList;

	std::vector<IGameObject*> m_deleteObject;
	D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B

	CSoundEngine m_soundEngine;

	

	


};

extern GameObjectManager::EffekseerTool g_effect;