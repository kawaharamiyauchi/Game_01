#include "stdafx.h"
#include "Fade.h"


Fade::Fade()
{
	m_spriteRender = GameObjectManager::instance().NewGO<SpriteRender>();
	m_spriteRender->Init(L"ago_free_03.dds",1280.0f,720.0f);
	FadeIn();
	m_alpha = 0.0f;

}
Fade::~Fade()
{
	GameObjectManager::instance().DeleteGO(m_spriteRender);
}

void Fade::Update()
{

	switch (m_state)
	{
	case Fade::Fadein:
		m_alpha += 0.02f;
		break;
	case Fade::Fadeout:
		m_alpha -= 0.02f;
		break;
	case Fade::idle:
		m_timer++;
		break;
	default:
		break;
	}
	if (m_alpha > 0.99f)
	{
		m_state = idle;
	}
	if (m_timer > 600)
	{
		FadeOut();
	}
	m_spriteRender->SetAlpha(m_alpha);
	if (m_alpha < 0.1f)
	{
		isFade = false;
		GameObjectManager::instance().DeleteGO(this);
	}
}
