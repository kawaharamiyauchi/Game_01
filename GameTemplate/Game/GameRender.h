#pragma once
#include "RenderTarget.h"
#include "Sprite.h"
class GameRender
{
public:
	GameRender();
	~GameRender();
	void Update();
	void Render();

private:
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
	/// �����_�����O�^�[�Q�b�g�̐؂�ւ��B
	/// </summary>
	/// <param name="d3dDeviceContext">D3D�f�o�C�X�R���e�L�X�g</param>
	/// <param name="renderTarget">�����_�����O�^�[�Q�b�g</param>
	/// <param name="viewport">�r���[�|�[�g</param>
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);

	/// <summary>
	/// �J�������������B
	/// </summary>
	void InitCamera();

private:
	RenderTarget m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B
	CVector3 m_unityChanPos = { 0.0f, 0.0f, 0.0f };	//���j�e�B�����̍��W�B
	C3DModelDraw m_unityChanModelDraw;		//���j�e�B�����̃��f���̕`�揈���B�B
	C3DModelDraw m_bgModelDraw;				//�w�i�̃��f���̕`�揈���B
	ShadowMap m_shadowMap;					//�V���h�E�}�b�v�B

	Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	D3D11_VIEWPORT m_frameBufferViewports;			//�t���[���o�b�t�@�̃r���[�|�[�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B

};

