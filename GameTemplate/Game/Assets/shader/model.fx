/*!
 * @brief	モデルシェーダー。
 */


 /////////////////////////////////////////////////////////////
 // Shader Resource View
 /////////////////////////////////////////////////////////////
Texture2D<float4> g_albedoTexture : register(t0);	//アルベドテクスチャ。
Texture2D<float4> g_shadowMap:register(t2);
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler g_sampler : register(s0);

/*!
 * @brief	頂点シェーダー用の定数バッファ。
 */
cbuffer VSCb : register(b0) {
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	
	//todo ライトビュー行列を追加。
	float4x4 mLightView;	//ライトビュー行列。
	float4x4 mLightProj;	//ライトプロジェクション行列。
	int isShadowReciever;	//シャドウレシーバーフラグ。
};

/// <summary>
/// ディレクションライト
/// </summary>
struct SDirectionLight {
	float3 direction;
	float4 color;

};
static const int NUM_DIRECTION_LIG = 4;
/*!
 *@brief	ライト用の定数バッファ。
 */
cbuffer LightCb : register(b1) {
	/*float3 dligDirection[NUM_DIRECTION_LIG];
	float4 dligColor[NUM_DIRECTION_LIG];
	float3 eyePos;
	float specPow;*/
	SDirectionLight directionLight;
	float3 eyePos;
	float specPow;
	float3 ambientLight;
};

/// <summary>
/// シャドウマップ用の定数バッファ。
/// </summary>
cbuffer ShadowMapCb : register(b1) {
	float4x4 lightViewProjMatrix;	//ライトビュープロジェクション行列。
}
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
	float4 Position : SV_Position;		//頂点座標。
	float3 Normal   : NORMAL;			//法線。
	float3 Tangent	: TANGENT;
	float2 TexCoord	: TEXCOORD0;		//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
	float4 Position : SV_Position;			//頂点座標。
	float3 Normal   : NORMAL;				//法線。
	float2 TexCoord	: TEXCOORD0;			//UV座標。
	float3 Tangent	: TANGENT;				//接ベクトル。
	uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
	float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput {
	float4 Position 	: SV_POSITION;	//座標。
	float3 Normal		: NORMAL;		//法線。
	float3 Tangent		: TANGENT;
	float2 TexCoord		: TEXCOORD0;	//UV座標。
	float4 posInLVP		: TEXCOORD1;	//ライトビュープロジェクション空間での座標。
	float3 WorldPos		: TEXCOORD2;	//ワールド座標。解説６


};

/// <summary>
/// シャドウマップ用のピクセルシェーダへの入力構造体。
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//座標。
};

float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;
	float w = 0.0f;
	[unroll]
	for (int i = 0; i < 3; i++)
	{
		skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
		w += In.Weights[i];
	}

	skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain(VSInputNmTxVcTangent In)
{
	
	PSInput psInput = (PSInput)0;
	//ローカル座標系からワールド座標系に変換する。
	float4 m_worldPos = mul(mWorld, In.Position);
	//ワールド座標系からカメラ座標系に変換する。
	psInput.Position = mul(mView, m_worldPos);
	//カメラ座標系からスクリーン座標系に変換する。
	psInput.Position = mul(mProj, psInput.Position);

	if (isShadowReciever == 1) {
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, m_worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	//UV座標はそのままピクセルシェーダーに渡す。
	psInput.TexCoord = In.TexCoord;
	//法線はそのままピクセルシェーダーに渡す。
	//psInput.Normal = In.Normal;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));

	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin(VSInputNmTxWeights In)
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;
	{

		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//最後のボーンを計算する。
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
		pos = mul(skinning, In.Position);
	}

	psInput.Normal = normalize(mul(skinning, In.Normal));
	psInput.Tangent = normalize(mul(skinning, In.Tangent));
	
	//ローカル座標系からワールド座標系に変換する。
	float4 m_worldPos = mul(mWorld, In.Position);
	//ワールド座標系からカメラ座標系に変換する。
	psInput.Position = mul(mView, m_worldPos);
	//カメラ座標系からスクリーン座標系に変換する。
	psInput.Position = mul(mProj, psInput.Position);

	psInput.WorldPos = m_worldPos;

	if (isShadowReciever == 1) {
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, m_worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	return psInput;
}

//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain(PSInput In) : SV_Target0
{
	//albedoテクスチャからカラーをフェッチする。
	float4 albedoColor = g_albedoTexture.Sample(g_sampler, In.TexCoord);
	//ディレクションライトの拡散反射光を計算する。


	
	/// <summary>
	/// ライト4本(ディレクションライト＋鏡面反射)
	/// </summary>
	/*float3 toEyeDir[NUM_DIRECTION_LIG];
	float3 reflectEyeDir[NUM_DIRECTION_LIG];
	float t[NUM_DIRECTION_LIG];
	float3 specLig[NUM_DIRECTION_LIG];*/
	//for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
	//	lig += max(0.0f, dot(In.Normal * -1.0f, dligDirection[i])) *  dligColor[i];
	//	toEyeDir[i] = normalize(eyePos - In.WorldPos);
	//	reflectEyeDir[i] = -toEyeDir[i] + 2 * dot(In.Normal, toEyeDir[i]) * In.Normal;
	//	t[i] = max(0.0f, dot(-dligDirection[i], reflectEyeDir[i]));
	//	//鏡面反射を反射光に加算する。
	//	lig += pow(0.1, 1.0f) * dligColor[i].xyz;

	//}
	/// <summary>
	/// ライト1本
	/// </summary>
	/// 拡散反射光
	float3 lig = max(0.0f, dot(In.Normal * -1.0f, directionLight.direction)) * directionLight.color.xyz;
	
	float3 toEyeDir = normalize(eyePos - In.WorldPos);

	float3 reflectEyeDir = -toEyeDir + 2 * dot(In.Normal, toEyeDir) * In.Normal;

	float t = max(0.0f, dot(-directionLight.direction, reflectEyeDir));

	float3 specLig = pow(t, specPow) * directionLight.color.xyz;
	

	

	float3 halflig = lig*0.5 ;

		if (isShadowReciever == 1) {	//シャドウレシーバー。
			//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する。
			float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
			shadowMapUV *= float2(0.5f, -0.5f);
			shadowMapUV += 0.5f;
			//シャドウマップの範囲内かどうかを判定する。
			if (shadowMapUV.x < 1.0f
				&& shadowMapUV.x > 0.0f
				&& shadowMapUV.y < 1.0f
				&& shadowMapUV.y > 0.0f
				) {

				///LVP空間での深度値を計算。
				float zInLVP = In.posInLVP.z / In.posInLVP.w;
				//シャドウマップに書き込まれている深度値を取得。
				float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV);
				

				//float z = zInLVP - zInShadowMap;
				if (zInLVP - zInShadowMap > 0.005f) {
					//影が落ちているので、光を弱くする
					lig *= 0.1f;
				}
				//VSM??
				//Variance Shadow Maps（分散シャドウマップ）
				float add = 0.0f;
				//for (int i = 2; i < 20; i++) {
				//	//2*0.05 =0.1
				//	add = 0.01f*i;
				//	if (zInLVP - zInShadowMap > add) {

				//		lig += halflig / 20.0f;
				//		//lig *= 0.99f;
				//	}
				//}
				}
			
		}
	
		
	
	lig += ambientLight;

	//鏡面反射を反射光に加算する。
	lig += specLig;
	
	
	
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
}
/// <summary>
/// スキン無し用シャドウマップ生成用の頂点シェーダー。
/// </summary>
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
// <summary>
/// スキンありシャドウマップ生成用の頂点シェーダー。
/// </summary>
PSInput_ShadowMap VSMainSkin_ShadowMap(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4x4 skinning = CalcSkinMatrix(In);
	float4 pos = mul(skinning, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
/// <summary>
/// ピクセルシェーダーのエントリ関数。
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//射影空間でのZ値を返す。
	return In.Position.z / In.Position.w;
}
