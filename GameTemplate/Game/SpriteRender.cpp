#include "stdafx.h"
#include "SpriteRender.h"



SpriteRender::~SpriteRender()
{
	m_sprite.~Sprite();
}
void SpriteRender::Init(const wchar_t*FileName, float w, float h)
{
	m_sprite.Init(FileName, w, h);
}
void SpriteRender::Update()
{
	m_sprite.Update(
		m_position,
		m_rotation,
		m_scale,
		m_pivot
	);
	

}
void SpriteRender::Render()
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
	m_sprite.Draw(mView, mProj);
	//m_sprite.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
	
}
