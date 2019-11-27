#include "stdafx.h"
#include "SkinModelRender.h"


SkinModelRender::SkinModelRender()
{
}


SkinModelRender::~SkinModelRender()
{
}

void SkinModelRender::Init(const wchar_t*filepath)
{
	m_skinModel.Init(filepath,enFbxUpAxisZ);
}
void SkinModelRender::Update()
{
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}
void SkinModelRender::Render()
{	
	m_skinModel.Draw(

		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
