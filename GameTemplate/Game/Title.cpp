#include "stdafx.h"
#include "Title.h"
#include"Game.h"
#include "SpriteRender.h"

Title::Title()
{
	//m_sprite.Init(L"Assets/sprite/ago_free_03.dds", 1280.0f, 720.0f);
	m_spriteRender = g_goMgr.NewGO<SpriteRender>();
	m_spriteRender->Init(L"Assets/sprite/ago_free_03.dds", 1280.0f, 720.0f);
}


Title::~Title()
{
	m_spriteRender->~SpriteRender();
	//m_sprite.~Sprite();
	
}

void Title::Update()
{
	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_scale.x -= 0.001f;
	//m_scale.y += 0.001f;
	m_spriteRender->SetPivot({ 0.0f,0.5f });
	m_spriteRender->SetScale(m_scale);
	
	
	if (g_pad[0].IsPress(enButtonStart))
	{
		auto m_game = Game::instance();
		g_goMgr.DeleteGO(this);
	}

}
void Title::Render()
{
	
}