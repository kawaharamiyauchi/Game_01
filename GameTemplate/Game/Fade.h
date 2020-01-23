#pragma once
#include "SpriteRender.h"
class Fade:public IGameObject
{
public:
	Fade();
	~Fade();
	void Update();
	void Render() {};
	void FadeIn()
	{
		m_state = Fadein;
	}
	void FadeOut()
	{
		m_state = Fadeout;
	}

	
	bool IsFade()const 
	{
		return isFade;
	}
	float GetAlpha()
	{
		return m_alpha;
	}
private:
	enum FadeState {
		Fadein,
		Fadeout,
		idle
	};
	FadeState m_state = Fadein;
	SpriteRender *m_spriteRender = nullptr;
	float m_alpha = 0.0f;
	bool isFade = true;
	int m_timer = 0;
};

