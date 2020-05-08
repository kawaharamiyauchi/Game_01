#include "stdafx.h"
#include "Fade.h"


Fade::Fade()
{
	

	m_sprite.Init(L"Assets/sprite/black.dds",1280.0f, 720.0f);
	m_sprite.SetAlpha(m_alpha);
}
Fade::~Fade()
{
}

void Fade::Update()
{
	
	
	switch (m_state)
	{
	case Fadein:
		if (m_alpha < 1.0f) {
			m_alpha += 0.02f;
			isFade = true;
			isEnd = false;
		}
		else isFade = false;
		break;
	case Fadeout:
		if (m_alpha > 0.02f) {
			m_alpha -= 0.02f;
			isFade = true;
		}
		else isEnd = true;
		break;
	case idle:
		break;
	default:
		break;
	}
	m_sprite.SetAlpha(m_alpha);
	
}
void Fade::PostRender()
{
	CMatrix mView;
	CMatrix mViewInv;
	CMatrix mProj;
	mView.MakeLookAt(
		{ 0, 0, -1 },
		{ 0, 0, 0 },
		{ 0,1,0 }
	);
	mProj.MakeOrthoProjectionMatrix(1280.0f, 720.0f, 0.1f, 100.0f);
	//m_sprite.SetAlpha(m_spriteAlpha);
	m_sprite.Draw(mView, mProj);
}
