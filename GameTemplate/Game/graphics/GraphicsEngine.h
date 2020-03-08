#pragma once

/// <summary>
/// レンダリングモード。
/// </summary>
enum EnRenderMode {
	enRenderMode_Invalid,			//不正なレンダリングモード。
	enRenderMode_CreateShadowMap,	//シャドウマップ生成。
	enRenderMode_Normal,			//通常レンダリング。
	enRenderMode_Num,				//レンダリングモードの数。
};


/*!
 *@brief	グラフィックスエンジン。
 */
class RenderTarget;
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	初期化。
	 *@param[in]	hWnd		ウィンドウハンドル。
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	解放。
	 */
	void Release();
	/*!
	 *@brief	D3D11デバイスを取得。
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}


	/*!
	 *@brief	D3D11デバイスコンテキストを取得。
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/// <summary>
		/// SpriteFontの取得。
		/// </summary>
		/// <remarks>
		/// エンジン内部で使用されます。ゲーム層では使用しないように。
		/// </remarks>
		/// <returns></returns>
	DirectX::SpriteFont* GetSpriteFont() const
	{
		return m_spriteFont.get();
	}

	/*!
		*@brief	SpriteBatchの取得。
		*@details
		* ゲーム層では使用しないように。
		*/
		/// <summary>
		/// SpriteBatchの取得
		/// </summary>
		/// <remarks>
		/// エンジン内部で使用されます。ゲーム層では使用しないように。
		/// </remarks>
		/// <returns></returns>
	DirectX::SpriteBatch* GetSpriteBatch() const
	{
		return m_spriteBatch.get();
	}

	/// <summary>
		/// フレームバッファの幅を取得。
		/// </summary>
	int GetFrameBufferWidth() const
	{
		return m_frameBufferWidth;
	}
	/// <summary>
	/// フレームバッファの高さを取得。
	/// </summary>
	int GetFrameBufferHeight() const
	{
		return m_frameBufferHeight;
	}

	/// <summary>
		/// 2D空間のスクリーンの幅を取得。
		/// </summary>
	int Get2DSpaceScreenWidth() const
	{
		return m_2dSpaceScreenWidth;
	}
	/// <summary>
	/// 2D空間のスクリーンの高さを取得。
	/// </summary>
	int Get2DSpaceScreenHeight() const
	{
		return m_2dSpaceScreenHeight;
	}
	/*!
	 *@brief	描画開始。
	 */
	void BegineRender();
	/*!
	 *@brief	描画終了。
	 */
	void EndRender();

	void SaveBackUpState();
	
	void SetBackUpState()
	{
		m_pd3dDeviceContext->PSSetSamplers(0, 4, m_backup.m_samplers);

		m_pd3dDeviceContext->OMSetBlendState(m_backup.m_BS, 0, 0xFFFFFFFF);
		m_pd3dDeviceContext->OMSetDepthStencilState(m_backup.m_DS, 0);
		m_pd3dDeviceContext->RSSetState(m_backup.m_RS);

	}
	struct BackupState
	{
		ID3D11RasterizerState*	m_RS = NULL;	//ラスタライザステートのバックアップ
		ID3D11BlendState *		m_BS = NULL;	//ブレンディングステートのバックアップ
		ID3D11DepthStencilState*m_DS = NULL;	//デプスステンシルステートのバックアップ
		float				m_blendFactor[4];
		UINT				m_blendSampleMask;
		UINT				m_depthStencilStateRef;
		ID3D11SamplerState*	m_samplers[4];

	};
	BackupState Getbackup()const
	{
		return m_backup;
	}
private:
	
	BackupState m_backup;
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11デバイス。
	IDXGISwapChain*			m_pSwapChain = NULL;		//スワップチェイン。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11デバイスコンテキスト。
	ID3D11RenderTargetView* m_backBuffer = NULL;		//バックバッファ。
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//ラスタライザステート。
	ID3D11Texture2D*		m_depthStencil = NULL;		//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//デプスステンシルビュー。
	std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;				//!<スプライトバッチ。
	std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;
	RenderTarget *m_rendertarget;
	int						m_frameBufferWidth = 0;						//!<フレームバッファの幅。これが内部解像度。
	int						m_frameBufferHeight = 0;
	const int				m_2dSpaceScreenWidth = 1280;				//!<2D空間のスクリーンの幅。2Dはこの座標系を前提に表示されていれば、解像度が変わっても大丈夫。
	const int				m_2dSpaceScreenHeight = 720;				//!<2D空間のスクリーンの高さ。2Dはこの座標系を前提に表示されていれば、解像度が変わっても大丈夫。
};

extern GraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン