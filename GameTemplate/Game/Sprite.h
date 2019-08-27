#pragma once
#include "system/system.h"
#include "level/Level.h"
#include "graphics/Shader.h"

class Sprite
{
public:
	Shader m_vsShader;
	Shader m_psShader;
	ID3D11Buffer*m_vertexBuffer = nullptr;

	struct SSimpleVertex {
		CVector4 pos;
	};
	Sprite();
	~Sprite();

	void LoadShader();
	void InitVertexBuffer();
	void Draw();
};


