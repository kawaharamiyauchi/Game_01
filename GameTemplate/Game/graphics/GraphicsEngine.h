#pragma once

/// <summary>
/// �����_�����O���[�h�B
/// </summary>
enum EnRenderMode {
	enRenderMode_Invalid,			//�s���ȃ����_�����O���[�h�B
	enRenderMode_CreateShadowMap,	//�V���h�E�}�b�v�����B
	enRenderMode_Normal,			//�ʏ탌���_�����O�B
	enRenderMode_Num,				//�����_�����O���[�h�̐��B
};


/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */
class RenderTarget;
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	�������B
	 *@param[in]	hWnd		�E�B���h�E�n���h���B
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	����B
	 */
	void Release();
	/*!
	 *@brief	D3D11�f�o�C�X���擾�B
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}


	/*!
	 *@brief	D3D11�f�o�C�X�R���e�L�X�g���擾�B
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/// <summary>
		/// SpriteFont�̎擾�B
		/// </summary>
		/// <remarks>
		/// �G���W�������Ŏg�p����܂��B�Q�[���w�ł͎g�p���Ȃ��悤�ɁB
		/// </remarks>
		/// <returns></returns>
	DirectX::SpriteFont* GetSpriteFont() const
	{
		return m_spriteFont.get();
	}

	/*!
		*@brief	SpriteBatch�̎擾�B
		*@details
		* �Q�[���w�ł͎g�p���Ȃ��悤�ɁB
		*/
		/// <summary>
		/// SpriteBatch�̎擾
		/// </summary>
		/// <remarks>
		/// �G���W�������Ŏg�p����܂��B�Q�[���w�ł͎g�p���Ȃ��悤�ɁB
		/// </remarks>
		/// <returns></returns>
	DirectX::SpriteBatch* GetSpriteBatch() const
	{
		return m_spriteBatch.get();
	}

	/// <summary>
		/// �t���[���o�b�t�@�̕����擾�B
		/// </summary>
	int GetFrameBufferWidth() const
	{
		return m_frameBufferWidth;
	}
	/// <summary>
	/// �t���[���o�b�t�@�̍������擾�B
	/// </summary>
	int GetFrameBufferHeight() const
	{
		return m_frameBufferHeight;
	}

	/// <summary>
		/// 2D��Ԃ̃X�N���[���̕����擾�B
		/// </summary>
	int Get2DSpaceScreenWidth() const
	{
		return m_2dSpaceScreenWidth;
	}
	/// <summary>
	/// 2D��Ԃ̃X�N���[���̍������擾�B
	/// </summary>
	int Get2DSpaceScreenHeight() const
	{
		return m_2dSpaceScreenHeight;
	}
	/*!
	 *@brief	�`��J�n�B
	 */
	void BegineRender();
	/*!
	 *@brief	�`��I���B
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
		ID3D11RasterizerState*	m_RS = NULL;	//���X�^���C�U�X�e�[�g�̃o�b�N�A�b�v
		ID3D11BlendState *		m_BS = NULL;	//�u�����f�B���O�X�e�[�g�̃o�b�N�A�b�v
		ID3D11DepthStencilState*m_DS = NULL;	//�f�v�X�X�e���V���X�e�[�g�̃o�b�N�A�b�v
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
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11�f�o�C�X�B
	IDXGISwapChain*			m_pSwapChain = NULL;		//�X���b�v�`�F�C���B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11�f�o�C�X�R���e�L�X�g�B
	ID3D11RenderTargetView* m_backBuffer = NULL;		//�o�b�N�o�b�t�@�B
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//���X�^���C�U�X�e�[�g�B
	ID3D11Texture2D*		m_depthStencil = NULL;		//�f�v�X�X�e���V���B
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//�f�v�X�X�e���V���r���[�B
	std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;				//!<�X�v���C�g�o�b�`�B
	std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;
	RenderTarget *m_rendertarget;
	int						m_frameBufferWidth = 0;						//!<�t���[���o�b�t�@�̕��B���ꂪ�����𑜓x�B
	int						m_frameBufferHeight = 0;
	const int				m_2dSpaceScreenWidth = 1280;				//!<2D��Ԃ̃X�N���[���̕��B2D�͂��̍��W�n��O��ɕ\������Ă���΁A�𑜓x���ς���Ă����v�B
	const int				m_2dSpaceScreenHeight = 720;				//!<2D��Ԃ̃X�N���[���̍����B2D�͂��̍��W�n��O��ɕ\������Ă���΁A�𑜓x���ς���Ă����v�B
};

extern GraphicsEngine* g_graphicsEngine;			//�O���t�B�b�N�X�G���W��