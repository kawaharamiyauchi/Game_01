#pragma once
#include "IGameObject.h"
#include "SpriteRender.h"
class UI:public IGameObject
{
public:
	UI();
	~UI();
	/// <summary>
	/// UI�̍X�V�����B
	/// </summary>
	void Update();
	/// <summary>
	/// UI�̕`�揈���B
	/// </summary>
	void Render()
	{

	}

private:
	SpriteRender*m_spriteRender[3] = { nullptr };				//�X�v���C�g�����_�[
	
	CVector3 m_spritePos[4] = { CVector3::Zero() };				//2D�摜�̈ʒu
	CVector3 m_spriteSca [4] = { CVector3::One() };					//2D�摜�̊g�嗦
	CQuaternion m_spriteRot[4] = { CQuaternion::Identity() };	//2D�摜�̉�]

};

