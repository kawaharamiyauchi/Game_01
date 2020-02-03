#pragma once
#include "SpriteRender.h"
#include "Sprite.h"
class Fade
{
public:

	static Fade& instance()
	{
		static Fade instance;
		return instance;
	}
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
	void PostRender();
private:
	enum FadeState {
		Fadein,
		Fadeout,
		idle
	};
	FadeState m_state = idle;
	//SpriteRender *m_spriteRender[2] = { nullptr };
	Sprite m_sprite;
	float m_alpha = 0.5f;
	bool isFade = true;
	int m_timer = 0;
};
