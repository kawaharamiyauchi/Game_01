#include "stdafx.h"
#include "C3DModelEffect.h"
#include "Game.h"




void __cdecl C3DModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{

	switch (m_renderMode) {
	case enRenderMode_Normal: {
		//�ʏ�`��B
		//�V�F�[�_�[��K�p����B
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
		//todo �V�F�[�_�[���\�[�X�r���[����C�ɐݒ肷��B
		ID3D11ShaderResourceView* srvArray[] = {
			m_albedoTexture,							//�A���x�h�e�N�X�`���B
			Game::instance()->GetShadowMap()->GetShadowMapSRV()	//�V���h�E�}�b�v�B
		};
		deviceContext->PSSetShaderResources(0, 2, srvArray);
	}break;
	case enRenderMode_CreateShadowMap:
		//�V���h�E�}�b�v�����B
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	}
}