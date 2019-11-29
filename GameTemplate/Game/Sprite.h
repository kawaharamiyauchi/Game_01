#pragma once

#include "graphics/shader.h"

class Sprite {
public:

	static const CVector2 NORMAL;
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Sprite::Sprite();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	Sprite::~Sprite();
	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="textureFilePath">テクスチャのファイルパス。</param>
	void Init(const wchar_t* textureFilePath, float w, float h);
	void Init(ID3D11ShaderResourceView * srv, float w, float h);
	/// <summary>
	/// ワールド行列を更新。
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大率</param>
	void UpdateWorldMatrix(CVector3 pos, CQuaternion rot, CVector3 scale);
	/// <summary>
	/// 描画。
	/// </summary>
	/// <param name="mView">カメラ行列</param>
	/// /// <param name="mView">プロジェクション行列</param>
	void Draw(CMatrix mView, CMatrix mProj);
	void Draw();
	/// <summary>
	/// 2Dの基点を設定。
	/// </summary>
	/// <param name="piv"></param>
	void SetPivot(CVector2 piv)
	{
		m_pivot = piv;
	}
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="trans">平行移動</param>
	/// <param name="rot">回転</param>
	/// <param name="sca">拡大</param>
	/// <param name="pivot">基点</param>
	void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& sca, const CVector2& pivot);
private:
	/// <summary>
	/// シェーダーをロード。
	/// </summary>
	void LoadShader();
	/// <summary>
	/// 頂点バッファを作成。
	/// </summary>
	void CreateVertexBuffer(float w, float h);
	/// <summary>
	/// インデックスバッファを作成。
	/// </summary>
	void CreateIndexBuffer();
	/// <summary>
	/// サンプラステートを作成。
	/// </summary>
	void CreateSamplerState();
	/// <summary>
	/// 定数バッファの作成。
	/// </summary>
	void CreateConstantBuffer();
	/// <summary>
	/// テクスチャをロ―ド。
	/// </summary>
	/// <param name="textureFIlePath">ロードするテクスチャのファイルパス。</param>
	void LoadTexture(const wchar_t* textureFIlePath);
private:
	struct ConstantBuffer {
		CMatrix WVP;		//ワールドビュープロジェクション行列。
		float alpha;		//α値。
	};
	Shader	m_vs;											//頂点シェーダー。
	Shader	m_ps;	//ピクセルシェーダー。
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	CVector2 m_pivot;
	CVector2 m_size =CVector2::Zero();
	ID3D11Buffer*	m_vertexBuffer = nullptr;	//VRAM上の頂点バッファにアクセスするためのインターフェース。
	ID3D11Buffer*	m_indexBuffer = nullptr;		//VRAM上のインデックスバッファにアクセスするためのインターフェース。
	ID3D11Buffer*	m_cbGPU = nullptr;			//GPU側の定数バッファにアクセスするためのインターフェース。
	ID3D11ShaderResourceView* m_texture = nullptr;	//テクスチャにアクセスするためのインターフェース。
	ID3D11SamplerState* m_samplerState = nullptr;	//サンプラステート。
	CMatrix m_world = CMatrix::Identity();					//ワールド行列。
	//ID3D11Buffer*				m_cb = nullptr;							//定数バッファ。
	float						m_alpha = 1.0f;							//スプライトのα値。
};


