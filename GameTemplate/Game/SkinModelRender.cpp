#include "stdafx.h"
#include "SkinModelRender.h"


SkinModelRender::SkinModelRender()
{
}


SkinModelRender::~SkinModelRender()
{
}

void SkinModelRender::Init(const wchar_t*filepath,EnFbxUpAxis fbxUpAxis)
{
	m_enFbxUpAxis = fbxUpAxis;
	m_skinModel.Init(filepath, m_enFbxUpAxis);
}
void SkinModelRender::Update()
{
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}
void SkinModelRender::Render()
{

}
