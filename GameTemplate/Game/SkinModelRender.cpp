#include "stdafx.h"
#include "SkinModelRender.h"
#include "ShadowMap.h"

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
	if (m_isCasterFlag == true)
	{
		SetShadowCasterUpdate();
	}
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}
void SkinModelRender::Render()
{	
	m_skinModel.Draw(
		m_renderMode,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void SkinModelRender::SetShadowCasterUpdate()
{
	//ShadowMap::instance().RegistShadowCaster(&m_skinModel);
	auto shadowMap = &ShadowMap::instance();
	shadowMap->RegistShadowCaster(&m_skinModel);
}