#pragma once
#include<array>
#include "graphics/Shader.h"
#include "graphics/Camera.h"
#include "system/system.h"

class dbgDraw:public btIDebugDraw 
{
	struct ConstantBuffer {
		CMatrix m_View;
		CMatrix m_Proj;
	};
	int m_debugMode = btIDebugDraw::DBG_NoDebug;
	//CRenderContext* m_renderContext = nullptr;
	//CPrimitive m_primitive;
	Shader m_vs;	//頂点シェーダー。
	Shader m_ps;	//ピクセルシェーダー。
	ConstantBuffer m_cb;
	static const int VERTEX_MAX = 1000000;
	std::array<CVector4, VERTEX_MAX> m_vertexBuffer;

	int m_numLine = 0;
public:
	void Init();

	/*void BeginDraw(CRenderContext& rc)
	{
		m_renderContext = &rc;
		m_numLine = 0;
	}*/

	void EndDraw();
	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
	void drawContactPoint(const btVector3&, const btVector3&, btScalar, int, const btVector3&) override
	{
	}
	void reportErrorWarning(const char*) override
	{
	}
	void draw3dText(const btVector3&, const char*) override
	{
	}
	void setDebugMode(int debugMode) override
	{
		m_debugMode = debugMode;
	}
	int	getDebugMode() const override
	{
		return m_debugMode;
	}
};


