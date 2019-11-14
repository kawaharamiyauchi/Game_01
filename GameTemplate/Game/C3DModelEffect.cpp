#include "stdafx.h"
#include "C3DModelEffect.h"
#include "Game.h"




void __cdecl C3DModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{

	switch (m_renderMode) {
	case enRenderMode_Normal: {
		//通常描画。
		//シェーダーを適用する。
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
		//todo シェーダーリソースビューを一気に設定する。
		ID3D11ShaderResourceView* srvArray[] = {
			m_albedoTexture,							//アルベドテクスチャ。
			Game::instance()->GetShadowMap()->GetShadowMapSRV()	//シャドウマップ。
		};
		deviceContext->PSSetShaderResources(0, 2, srvArray);
	}break;
	case enRenderMode_CreateShadowMap:
		//シャドウマップ生成。
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	}
}