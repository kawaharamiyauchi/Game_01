#pragma once

#include "Skeleton.h"
#include "C3DModelEffect.h"
#include"SkinModelEffect.h"

using namespace std;
/*!
*@brief	FBXの上方向。
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
/*!
*@brief	スキンモデルクラス。
*/
class SkinModel
{
public:

	/// <summary>
	/// モデルエフェクト用の構造体。
	/// </summary>
	/// <remarks>
	/// これを変更したら、Asserts/shader/model.fxの
	/// VSCbも変更する必要があります。
	/// この構造体は16byteアライメントになっている必要があります。
	/// </remarks>
	struct SModelFxConstantBuffer {
		CMatrix mWorld;			//ワールド行列。
		CMatrix mView;			//ビュー行列。
		CMatrix mProj;			//プロジェクション行列。
		CMatrix mLightView;		//todo ライトビュー行列。
		CMatrix mLightProj;		//todo ライトプロジェクション行列。
		int isShadowReciever;	//todo シャドウレシーバーのフラグ。
	};
public:
	//メッシュが見つかったときのコールバック関数。
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	デストラクタ。
	*/
	~SkinModel();
	
	/*!
	*@brief	初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*@param[in] enFbxUpAxis		fbxの上軸。デフォルトはenFbxUpAxisZ。
	*/
	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	モデルをワールド座標系に変換するためのワールド行列を更新する。
	*@param[in]	position	モデルの座標。
	*@param[in]	rotation	モデルの回転。
	*@param[in]	scale		モデルの拡大率。
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	*@brief	ボーンを検索。
	*@param[in]		boneName	ボーンの名前。
	*@return	見つかったボーン。見つからなかった場合はnullptrを返します。
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	/// <summary>
	/// 描画処理を行うかどうか
	/// </summary>
	/// <param name="flag">アクティブフラグ</param>
	void SetActiveFlag(bool flag)
	{
		IsActiveflag = flag;
	}
	/// <summary>
	/// アクティブフラグを取得
	/// </summary>
	/// <returns>アクティブフラグ</returns>
	bool GetActiveFlag()
	{
		return IsActiveflag;
	}
	/// <summary>
	/// ディレクションライトを付与するかどうか
	/// </summary>
	/// <param name="flag">ディレクションライトフラグ</param>
	void SetlightFlag(bool flag)
	{
		lightFlag = flag;
	}
	/// <summary>
	/// 謎関数
	/// </summary>
	/// <param name="flag"></param>
	void SetColorFlag(bool flag)
	{
		colorFlag = flag;
	}
	/// <summary>
	/// 自己発光
	/// </summary>
	void SetGlowColor(CVector3 color)
	{
		m_glowColor = color;
	}
	/// <summary>
	/// スペキュラ(鏡面反射)光
	/// </summary>
	/// <param name="spec"></param>
	void SetSpecPow(float spec)
	{
		m_light.specPow = spec;
	}
	/*!
	*@brief	モデルを描画。
	*@param[in]	viewMatrix		カメラ行列。
	*  ワールド座標系の3Dモデルをカメラ座標系に変換する行列です。
	*@param[in]	projMatrix		プロジェクション行列。
	*  カメラ座標系の3Dモデルをスクリーン座標系に変換する行列です。
	*/
	void Draw(EnRenderMode renderMode,CMatrix viewMatrix, CMatrix projMatrix );
	/*!
	*@brief	スケルトンの取得。
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}
	//ワールド行列の取得
	CMatrix& GetWorldMatrix()
	{
		return m_worldMatrix;
	}
	/*!
	*@brief	メッシュを検索する。
	*@param[in] onFindMesh		メッシュが見つかったときのコールバック関数
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}
	/*!
	*@brief	SRVのレジスタ番号。
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<ディフューズテクスチャ。
		enSkinModelSRVReg_BoneMatrix,				//!<ボーン行列。
	};
	/// <summary>
	/// 
	/// </summary>
	/// <param name="flag"></param>
	void SetShadowCasterFlag(bool flag)
	{
		m_isShadowCaster = flag;
	}
	/// <summary>
	/// シャドウレシーバーのフラグを設定する。
	/// </summary>
	/// <param name="flag">trueを渡すとシャドウレシーバーになる</param>
	/// <remarks>
	/// シャドウレシーバーとは影を落とされるオブジェクトのことです。
	/// シャドウキャスターによって生成された、シャドウマップを利用して
	/// 自身に影を落とします。
	/// オブジェクトがシャドウレシーバーかつシャドウキャスターになっている場合は
	/// セルフシャドウ(自分の影が自分に落ちる)を行うことができます。
	/// </remarks>
	void SetShadowReciever(bool flag)
	{
		m_isShadowReciever = flag;
	}

	/// <summary>
	/// マテリアルに対してクエリを行う。
	/// </summary>
	/// <param name="func">問い合わせ関数</param>
	void QueryMaterials(std::function<void(SkinModelEffect*)> func)
	{
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			func(reinterpret_cast<SkinModelEffect*>(material));
			});
	}
private:
	/*!
	*@brief	サンプラステートの初期化。
	*/
	void InitSamplerState();
	/*!
	*@brief	定数バッファの作成。
	*/
	void InitConstantBuffer();
	/*!
	*@brief	スケルトンの初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*/
	void InitSkeleton(const wchar_t* filePath);
	
	void InitDirectionLight()
	{
		
		m_light.specPow = 10.0f;
		m_light.ambientLight.Set( 0.3f,0.3f,0.3f);
		m_light.Dlig.direction = { 0.0f,-0.8f,0.2f,1.0f };
		m_light.Dlig.color = { 1.0f,1.0f,1.0f,1.0f };
		
		/// <summary>
		/// 4本
		/// </summary>
		/*m_light.direction[0] = { 0.0f,-0.8f,0.0f,0.0f };
		m_light.color[0] = { 1.0f,1.0f,1.0f,1.0f };
		
		
		m_light.direction[1] = { 0.0f,0.8f,0.0f,0.0f };
		m_light.color[1] = { 1.0f,1.0f,1.0f,1.0f };

		m_light.direction[2] = { 1.0f,0.0f,1.0f,0.0f };
		m_light.color[2] = { 1.0f,1.0f,1.0f,0.5f };

		m_light.direction[3] = { -1.0f,0.0f,-1.0f,0.0f };
		m_light.color[3] = { 1.0f,1.0f,1.0f,0.5f };*/

		//m_light.directionLight.direction[0]
	}
	void UpDate() {
		
	}
	
private:
	/// <summary>
	/// ディレクションライト
	/// </summary>
	struct SDirectionLight {
		CVector4 direction;
		CVector4 color;
		
	};

	struct Light {
		/// <summary>
		/// 4本
		/// </summary>
		/*CVector4 direction[4];
		CVector4 color[4];*/

		SDirectionLight Dlig;
		CVector3			eyePos;				//視点の座標
		float				specPow;			//鏡面反射の絞り。
		CVector3 ambientLight;					//環境光
	
	};
private:
	//定数バッファ。
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		CMatrix mLightView;		//todo ライトビュー行列。
		CMatrix mLightProj;		//todo ライトプロジェクション行列。
		int isShadowReciever;	//todo シャドウレシーバーのフラグ。
	};
	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBXの上方向。
	ID3D11Buffer*		m_cb = nullptr;					//!<定数バッファ。
	ID3D11Buffer*		m_lightCb = nullptr;			//!<ライト用の定数バッファ。>
	ID3D11Buffer*		m_nullCb = nullptr;				//null定数バッファ。>
	Skeleton			m_skeleton;						//!<スケルトン。
	CMatrix				m_worldMatrix;					//!<ワールド行列。
	DirectX::Model*		m_modelDx;						//!<DirectXTKが提供するモデルクラス。
	//std::unique_ptr<DirectX::Model>		m_modelDx;				//DirectXTKが提供するモデル。
	Light				m_light;
	ID3D11SamplerState* m_samplerState = nullptr;		//!<サンプラステート。
	
	bool m_isShadowCaster;	
	bool m_isShadowReciever;
	bool IsActiveflag = true;							//!<アクティブフラグ
	bool lightFlag = true;
	bool colorFlag = false;

	CVector3 m_glowColor = CVector3::Zero();
};

