/*!
 * @brief	フォント。
 */
//#include "tkEngine/tkEnginePreCompile.h"
//#include "tkEngine/graphics/font/tkFont.h"
//#include "tkEngine/graphics/tkPresetRenderState.h"
#include"stdafx.h"
#include"Font.h"
#include"EffekseerRendererDX11.h"
#include "GameObjectManager.h"
	Font::Font()
	{
		m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
		m_spriteFont = g_graphicsEngine->GetSpriteFont();
		auto& ge = g_graphicsEngine;
		auto a = g_graphicsEngine->GetFrameBufferWidth() /*/ static_cast<float>(ge.Get2DSpaceScreenWidth())*/;
		auto b = g_graphicsEngine->GetFrameBufferHeight() /*/ static_cast<float>(ge.Get2DSpaceScreenHeight())*/;

		m_scaleMat.MakeScaling(
			{
				/*ge.GetFrameBufferWidth() / static_cast<float>(ge.Get2DSpaceScreenWidth()),
				ge.GetFrameBufferHeight() / static_cast<float>(ge.Get2DSpaceScreenHeight()),*/
				1.5f,
				1.5f,
				1.0f
			}
		);
	}
	Font::~Font()
	{
	}

	void Font::Begin()
	{
		//レンダリングステートを退避させる。
		//rc.PushRenderState();
		//if(g_graphicsEngine->BegineRender)
		g_graphicsEngine->SaveBackUpState();
		//auto g = GameObjectManager::instance().GetMainRenderTarget();
		//auto m_state = g_graphicsEngine->Getbackup();
		
		/*m_spriteBatch->Begin(
			DirectX::SpriteSortMode_Deferred,
			m_state.m_BS,
			*m_state.m_samplers,
			m_state.m_DS,
			m_state.m_RS,
			nullptr,
			m_scaleMat
		);*/
		
		m_spriteBatch->Begin(
			DirectX::SpriteSortMode_Deferred,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			CMatrix::Identity()
		);
		
		
	}
	void Font::End()
	{
		m_spriteBatch->End();
		//レンダリングステートを復活させる。
		g_graphicsEngine->SetBackUpState();

	}
	void Font::Draw(
		wchar_t const* text,
		const CVector2& position,
		const CVector4& color,
		float rotation,
		float scale,
		CVector2 pivot)
	{
		if (text == nullptr) {
			return;
		}
		pivot.y = 1.0f - pivot.y;
		DirectX::XMFLOAT2 tkFloat2Zero(0, 0);
		//座標系をスプライトと合わせる。
		CVector2 pos = position;
		float frameBufferHalfWidth = g_graphicsEngine->Get2DSpaceScreenWidth() * 0.5f;
		float frameBufferHalfHeight = g_graphicsEngine->Get2DSpaceScreenHeight() * 0.5f;
		pos.x += frameBufferHalfWidth;
		pos.y = -pos.y + frameBufferHalfHeight;


		if (m_isDrawShadow) {
			//影を書く。
			CVector2 offsetTbl[] = {
				{ m_shadowOffset , 0.0f},
				{ -m_shadowOffset , 0.0f },
				{ 0.0f , m_shadowOffset },
				{ 0.0f , -m_shadowOffset },

				{ m_shadowOffset ,  m_shadowOffset },
				{ m_shadowOffset ,  -m_shadowOffset },
				{ -m_shadowOffset , m_shadowOffset },
				{ -m_shadowOffset , -m_shadowOffset },
			};
			for (auto offset : offsetTbl) {

				CVector2 sPos = pos;
				sPos.x += offset.x;
				sPos.y += offset.y;
				m_spriteFont->DrawString(
					m_spriteBatch,
					text,
					sPos.vec,
					m_shadowColor,
					rotation,
					DirectX::XMFLOAT2(pivot.x, pivot.y),
					scale
				);
			}

		}
		
		m_spriteFont->DrawString(
			m_spriteBatch,
			text,
			pos.vec,
			color,
			rotation,
			DirectX::XMFLOAT2(pivot.x, pivot.y),
			scale
		);
	}
	