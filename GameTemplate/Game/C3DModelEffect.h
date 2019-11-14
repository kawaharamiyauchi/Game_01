#pragma once
#include "graphics/Shader.h"
#include <array>
#include "Game.h"

/*!
*@brief	���f���G�t�F�N�g�B
*@details
* DirectX::Model�̕`�揈���Ŏg�p�����V�F�[�_�[�������ւ��邽�߂̃N���X
*/
class C3DModelEffect : public DirectX::IEffect {
private:
	Shader m_vsShader;
	Shader m_psShader;
	Shader m_vsShadowMap;			//�V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
	Shader m_psShadowMap;		//�V���h�E�}�b�v�����p�̃s�N�Z���V�F�[�_�[�B
	ID3D11ShaderResourceView* m_albedoTexture = nullptr;
	std::array<ID3D11ShaderResourceView*, 4> m_albedoTextureStack = { nullptr };
	int m_albedoTextureStackPos = 0;
	EnRenderMode m_renderMode = enRenderMode_Invalid;	//�����_�����O���[�h�B

public:
	C3DModelEffect()
	{
		//���_�V�F�[�_�[�����[�h�B
		m_vsShader.Load("Assets/shader/model_2.fx", "VSMain", Shader::EnType::VS);
		m_psShader.Load("Assets/shader/model_2.fx", "PSMain", Shader::EnType::PS);
		//todo �V���h�E�}�b�v�p�̃V�F�[�_�[�����[�h�B
		m_psShadowMap.Load("Assets/shader/model_2.fx", "PSMain_ShadowMap", Shader::EnType::PS);
		m_vsShadowMap.Load("Assets/shader/model_2.fx", "VSMain_ShadowMap", Shader::EnType::VS);
	}
	~C3DModelEffect()
	{
		if (m_albedoTexture != nullptr) {
			m_albedoTexture->Release();
		}
	}
	void __cdecl Apply(ID3D11DeviceContext* deviceContext);
	//���̊֐���DirectX::Model�̏�������������Ă΂��B
	//���_�V�F�[�_�[�̃o�C�g�R�[�h�ƃR�[�h�̒�����ݒ肷��K�v������B
	void __cdecl GetVertexShaderBytecode(void const** pShaderByteCode, size_t* pByteCodeLength) override
	{
		*pShaderByteCode = m_vsShader.GetByteCode();
		*pByteCodeLength = m_vsShader.GetByteCodeSize();
	}
	void SetAlbedoTexture(ID3D11ShaderResourceView* texSRV)
	{
		if (m_albedoTexture != nullptr) {
			//�Q�ƃJ�E���^��������B
			m_albedoTexture->Release();
		}
		m_albedoTexture = texSRV;
		//�Q�ƃJ�E���^���グ��B
		m_albedoTexture->AddRef();
	}
	/// <summary>
	/// ���݂̃A���x�h�e�N�X�`�����X�^�b�N�ɑޔ�������B
	/// </summary>
	void PushAlbedoTexture()
	{
		m_albedoTextureStack[m_albedoTextureStackPos] = m_albedoTexture;
		m_albedoTexture = nullptr;
		m_albedoTextureStackPos++;
	}
	/// <summary>
	/// �X�^�b�N����A���x�h�e�N�X�`�����|�b�v����B
	/// </summary>
	void PopAlbedoTexture()
	{
		m_albedoTextureStackPos--;
		SetAlbedoTexture(m_albedoTextureStack[m_albedoTextureStackPos]);
	}

	void SetRenderMode(EnRenderMode renderMode)
	{
		m_renderMode = renderMode;
	}
private:

	

};
/*!
*@brief
*  �G�t�F�N�g�t�@�N�g���B
*@detail
* �G�t�F�N�g�̃t�@�N�g���B�}�e���A���̏��ɉ����č쐬����G�t�F�N�g��ύX����N���X�B
*
*/
class C3DModelEffectFactory : public DirectX::EffectFactory {
public:
	C3DModelEffectFactory(ID3D11Device* device) :
		EffectFactory(device) {}
	//�G�t�F�N�g���쐬�B
	std::shared_ptr<DirectX::IEffect> __cdecl CreateEffect(const EffectInfo& info, ID3D11DeviceContext* deviceContext)override
	{
		std::shared_ptr<C3DModelEffect> effect = std::make_shared< C3DModelEffect>();


		if (info.diffuseTexture && *info.diffuseTexture)
		{
			//�A���x�h�e�N�X�`�����\���Ă���B
			ID3D11ShaderResourceView* texSRV;
			DirectX::EffectFactory::CreateTexture(info.diffuseTexture, deviceContext, &texSRV);
			effect->SetAlbedoTexture(texSRV);
			texSRV->Release();
		}

		return effect;
	}
};