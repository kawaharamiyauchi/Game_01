#pragma once
#include "IGameObject.h"
#include "SpriteRender.h"
class UI:public IGameObject
{
public:

	enum UIType {
		HP,
		Stamina,
		Red,
		actionLine,
		Clear,
		GameOver,
		UITypeNum
	};
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
	void ClearDraw();
	void GameOverDraw();
private:
	SpriteRender*m_spriteRender[UITypeNum] = { nullptr };				//スプライトレンダー
	
	CVector3 m_spritePos[UITypeNum] = { CVector3::Zero() };				    //2D画像の位置
	CVector3 m_spriteSca [UITypeNum] = { CVector3::One() };					//2D画像の拡大率
	CQuaternion m_spriteRot[UITypeNum] = { CQuaternion::Identity() };		//2D画像の回転
	float m_alpha = 0.0f;
	bool AttackEvent = false;
};

