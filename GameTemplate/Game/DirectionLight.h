#pragma once
#include "IGameObject.h"
#include "stdafx.h"
#include "system/system.h"
#include "graphics/Shader.h"
#include "graphics/Camera.h"

class DirectionLight:public IGameObject
{
public:
	DirectionLight();
	~DirectionLight();
	//DirectX::EffectFactory;

/// <summary>
/// ディレクションライトの情報
/// </summary>
	struct DirectionLightInfo {
		CVector4 direction;
		CVector4 color;
	};

};

