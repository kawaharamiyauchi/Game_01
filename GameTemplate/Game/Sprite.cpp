#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite()
{
	InitVertexBuffer();
	LoadShader();
}


Sprite::~Sprite()
{
	//���_�o�b�t�@������B
	if (m_vertexBuffer != nullptr) {
		m_vertexBuffer->Release();
	}
}

void Sprite::LoadShader()
{
	m_vsShader.Load(
		"Assets/shader/Tutorial.fx",
		"PS",
		Shader::EnType::PS
	);
}

void Sprite::InitVertexBuffer()
{
	SSimpleVertex vertices[] = 
	{
		CVector4(0.0f,1.0f,0.0f,1.0f),
		CVector4(1.0f,-1.0f,0.0f,1.0f),
		CVector4(-1.0f,-1.0f,0.0f,1.0f)
		
	};
	//���_�o�b�t�@�̒�`�f�[�^���쐬����B
	D3D11_BUFFER_DESC desc = { 0 };	//0�N���A�B
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(vertices);			//�o�b�t�@�̑傫���B
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//�ǂ̃o�b�t�@�Ƀo�C���h���邩���w�肷��B
	desc.CPUAccessFlags = 0;					//CPU����A�N�Z�X���邩���߂�B0�Ȃ炵�Ȃ��B

	//���_�o�b�t�@�̃\�[�X�f�[�^���w�肷��B
	D3D11_SUBRESOURCE_DATA InitData = { 0 };	//0�ŏ������B
	InitData.pSysMem = vertices;

	//���_�o�b�t�@��VRAM��ɍ쐬����B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, &InitData, &m_vertexBuffer);
}
void Sprite::Draw()
{
	//�f�o�C�X�R���e�L�X�g���擾�B
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//�f�o�C�X�R���e�L�X�g�ɕ`��R�}���h��ςށB
	//���_�o�b�t�@��ݒ�B
	unsigned int stride = sizeof(SSimpleVertex);	//���_�o�b�t�@�̃X�g���C�h
	unsigned int offset = 0;						//���_�o�b�t�@�̃I�t�Z�b�g�B
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	//�v���~�e�B�u�̃g�|���W�[��ݒ�B
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//���_�V�F�[�_�[��ݒ�B
	deviceContext->VSSetShader(
		(ID3D11VertexShader*)m_vsShader.GetBody(),	//���_�V�F�[�_�[�B
		NULL,										//NULL�ł����B
		0											//0�ł����B
	);
	//�s�N�Z���V�F�[�_�[��ݒ�B
	deviceContext->PSSetShader(
		(ID3D11PixelShader*)m_psShader.GetBody(),	//�s�N�Z���V�F�[�_�[�B
		NULL,										//NULL�ł����B
		0											//0�ł����B
	);
	//���_���C�A�E�g��ݒ�B
	deviceContext->IASetInputLayout(m_vsShader.GetInputLayout());

	//�����܂Őݒ肵�����e�Ńh���[
	deviceContext->Draw(
		3,	//���_���B
		0	//�`��J�n�̒��_�ԍ��B���O�B
	);
}
