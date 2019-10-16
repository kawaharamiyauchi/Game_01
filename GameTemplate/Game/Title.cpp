#include "stdafx.h"
#include "Title.h"
#include"Game.h"

Title::Title()
{
	m_sprite.Init(L"Assets/sprite/ago_free_03.dds", 1280, 720);
}


Title::~Title()
{
	m_sprite.~Sprite();
	
}

void Title::Update()
{
	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_sprite.UpdateWorldMatrix(CVector3::Zero(), rot, CVector3::One());

	if (g_pad[0].IsPress(enButtonStart))
	{
		auto m_game = Game::instance();
		g_goMgr.DeleteGO(this);
	}

}
void Title::Render()
{
	CMatrix mView;
	CMatrix mViewInv;
	CMatrix mProj;
	mView.MakeLookAt(
		{ 0, 0, 1 },
		{ 0, 0, 0 },
		{ 0,1,0 }
	);
	//mViewInv.Inverse(mView);
	mProj.MakeOrthoProjectionMatrix(1280, 720, 0.1, 100);
	//m_sprite.Draw(mView, mProj);
}