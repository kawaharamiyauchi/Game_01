#pragma once
#include "IGameObject.h"
#include "SpriteRender.h"
class UI:public IGameObject
{
public:
	UI();
	~UI();
	/// <summary>
	/// UIの更新処理。
	/// </summary>
	void Update();
	/// <summary>
	/// UIの描画処理。
	/// </summary>
	void Render()
	{

	}

private:
	SpriteRender*m_spriteRender[3] = { nullptr };				//スプライトレンダー
	
	CVector3 m_spritePos[4] = { CVector3::Zero() };				//2D画像の位置
	CVector3 m_spriteSca [4] = { CVector3::One() };					//2D画像の拡大率
	CQuaternion m_spriteRot[4] = { CQuaternion::Identity() };	//2D画像の回転

};

