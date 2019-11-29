#pragma once

#include "graphics/shader.h"

class Sprite {
public:

	static const CVector2 NORMAL;
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Sprite::Sprite();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	Sprite::~Sprite();
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="textureFilePath">�e�N�X�`���̃t�@�C���p�X�B</param>
	void Init(const wchar_t* textureFilePath, float w, float h);
	void Init(ID3D11ShaderResourceView * srv, float w, float h);
	/// <summary>
	/// ���[���h�s����X�V�B
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g�嗦</param>
	void UpdateWorldMatrix(CVector3 pos, CQuaternion rot, CVector3 scale);
	/// <summary>
	/// �`��B
	/// </summary>
	/// <param name="mView">�J�����s��</param>
	/// /// <param name="mView">�v���W�F�N�V�����s��</param>
	void Draw(CMatrix mView, CMatrix mProj);
	void Draw();
	/// <summary>
	/// 2D�̊�_��ݒ�B
	/// </summary>
	/// <param name="piv"></param>
	void SetPivot(CVector2 piv)
	{
		m_pivot = piv;
	}
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="trans">���s�ړ�</param>
	/// <param name="rot">��]</param>
	/// <param name="sca">�g��</param>
	/// <param name="pivot">��_</param>
	void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& sca, const CVector2& pivot);
private:
	/// <summary>
	/// �V�F�[�_�[�����[�h�B
	/// </summary>
	void LoadShader();
	/// <summary>
	/// ���_�o�b�t�@���쐬�B
	/// </summary>
	void CreateVertexBuffer(float w, float h);
	/// <summary>
	/// �C���f�b�N�X�o�b�t�@���쐬�B
	/// </summary>
	void CreateIndexBuffer();
	/// <summary>
	/// �T���v���X�e�[�g���쐬�B
	/// </summary>
	void CreateSamplerState();
	/// <summary>
	/// �萔�o�b�t�@�̍쐬�B
	/// </summary>
	void CreateConstantBuffer();
	/// <summary>
	/// �e�N�X�`�������\�h�B
	/// </summary>
	/// <param name="textureFIlePath">���[�h����e�N�X�`���̃t�@�C���p�X�B</param>
	void LoadTexture(const wchar_t* textureFIlePath);
private:
	struct ConstantBuffer {
		CMatrix WVP;		//���[���h�r���[�v���W�F�N�V�����s��B
		float alpha;		//���l�B
	};
	Shader	m_vs;											//���_�V�F�[�_�[�B
	Shader	m_ps;	//�s�N�Z���V�F�[�_�[�B
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	CVector2 m_pivot;
	CVector2 m_size =CVector2::Zero();
	ID3D11Buffer*	m_vertexBuffer = nullptr;	//VRAM��̒��_�o�b�t�@�ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X�B
	ID3D11Buffer*	m_indexBuffer = nullptr;		//VRAM��̃C���f�b�N�X�o�b�t�@�ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X�B
	ID3D11Buffer*	m_cbGPU = nullptr;			//GPU���̒萔�o�b�t�@�ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X�B
	ID3D11ShaderResourceView* m_texture = nullptr;	//�e�N�X�`���ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X�B
	ID3D11SamplerState* m_samplerState = nullptr;	//�T���v���X�e�[�g�B
	CMatrix m_world = CMatrix::Identity();					//���[���h�s��B
	//ID3D11Buffer*				m_cb = nullptr;							//�萔�o�b�t�@�B
	float						m_alpha = 1.0f;							//�X�v���C�g�̃��l�B
};


