#include "stdafx.h"
#include "Fade.h"


Fade::Fade()
{
	/*m_spriteRender[0] = GameObjectManager::instance().NewGO<SpriteRender>();
	m_spriteRender[1] = GameObjectManager::instance().NewGO<SpriteRender>();
	m_spriteRender[0]->Init(L"Assets/sprite/MH_menu.dds", 400.0f, 100.0f);
	m_spriteRender[1]->Init(L"Assets/sprite/MH_HP.dds", 1280.0f, 720.0f);

	m_spriteRender[1]->SetPosition(CVector3::Zero());
	m_spriteRender[1]->SetRotation(CQuaternion::Identity());
	m_spriteRender[1]->SetScale(CVector3::One());
	m_spriteRender[1]->SetPivot({ 0.5f,0.5f });

	m_spriteRender[0]->SetIsActive(false);*/

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
		}
		else isFade = false;
		break;
	case Fadeout:
		if (m_alpha > 0.02f) {
			m_alpha -= 0.02f;
			isFade = true;
		}
		
		break;
	case idle:
		break;
	default:
		break;
	}
	m_sprite.SetAlpha(m_alpha);
	
	//m_spriteRender->SetAlpha(m_alpha);
	/*m_spriteRender[1]->SetPosition(CVector3::Zero());
	m_spriteRender[1]->SetRotation(CQuaternion::Identity());
	m_spriteRender[1]->SetScale(CVector3::One());
	m_spriteRender[1]->SetPivot({ 0.5f,0.5f });*/

	
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
	//m_sprite.SetAlpha(m_alpha);
	m_sprite.Draw(mView, mProj);
}
