#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite()
{
	InitVertexBuffer();
	LoadShader();
}


Sprite::~Sprite()
{
	//頂点バッファを解放。
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
	//頂点バッファの定義データを作成する。
	D3D11_BUFFER_DESC desc = { 0 };	//0クリア。
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(vertices);			//バッファの大きさ。
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//どのバッファにバインドするかを指定する。
	desc.CPUAccessFlags = 0;					//CPUからアクセスするか決める。0ならしない。

	//頂点バッファのソースデータを指定する。
	D3D11_SUBRESOURCE_DATA InitData = { 0 };	//0で初期化。
	InitData.pSysMem = vertices;

	//頂点バッファをVRAM上に作成する。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, &InitData, &m_vertexBuffer);
}
void Sprite::Draw()
{
	//デバイスコンテキストを取得。
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//デバイスコンテキストに描画コマンドを積む。
	//頂点バッファを設定。
	unsigned int stride = sizeof(SSimpleVertex);	//頂点バッファのストライド
	unsigned int offset = 0;						//頂点バッファのオフセット。
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	//プリミティブのトポロジーを設定。
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//頂点シェーダーを設定。
	deviceContext->VSSetShader(
		(ID3D11VertexShader*)m_vsShader.GetBody(),	//頂点シェーダー。
		NULL,										//NULLでいい。
		0											//0でいい。
	);
	//ピクセルシェーダーを設定。
	deviceContext->PSSetShader(
		(ID3D11PixelShader*)m_psShader.GetBody(),	//ピクセルシェーダー。
		NULL,										//NULLでいい。
		0											//0でいい。
	);
	//頂点レイアウトを設定。
	deviceContext->IASetInputLayout(m_vsShader.GetInputLayout());

	//ここまで設定した内容でドロー
	deviceContext->Draw(
		3,	//頂点数。
		0	//描画開始の頂点番号。大抵０。
	);
}
