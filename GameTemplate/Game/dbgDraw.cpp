#include "stdafx.h"
#include "dbgDraw.h"



void dbgDraw::Init()
{

	//ラインストリップのテスト。
	m_primitive.Create(
		D3D_PRIMITIVE_TOPOLOGY_LINELIST,
		static_cast<int>(m_vertexBuffer.size()),
		sizeof(CVector4),
		&m_vertexBuffer[0],
		0,
		CIndexBuffer::enIndexType_32,
		nullptr
	);
	m_vs.Load("shader/linePrimitive.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("shader/linePrimitive.fx", "PSMain", Shader::EnType::PS);
	m_cb.Create(nullptr, sizeof(ConstantBuffer));
}
void dbgDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	int baseIndex = m_numLine * 2;
	m_vertexBuffer[baseIndex].Set(CVector3(from.x(), from.y(), from.z()));
	m_vertexBuffer[baseIndex + 1].Set(CVector3(to.x(), to.y(), to.z()));
	m_numLine++;

}
void dbgDraw::EndDraw()
{
	ID3D11DeviceContext*d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//定数バッファの更新。
	ConstantBuffer cb;
	cb.m_View = g_camera3D.GetViewMatrix();
	cb.m_Proj = g_camera3D.GetProjectionMatrix();
	d3dDeviceContext->UpdateSubresource(m_cb, &cb);

	d3dDeviceContext->VSSetShader(m_vs);
	d3dDeviceContext->PSSetShader(m_ps);
	d3dDeviceContext->VSSetConstantBuffers(0,1, m_cb);
	d3dDeviceContext->UpdateSubresource(m_primitive.GetVertexBuffer(), &m_vertexBuffer[0]);
	m_primitive.Draw(*m_renderContext, m_numLine * 2);
}

