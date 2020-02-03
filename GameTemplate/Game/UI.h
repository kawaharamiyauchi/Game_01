#pragma once
#include "IGameObject.h"
#include "SpriteRender.h"
class UI:public IGameObject
{
public:

	enum UIType {
		HP,
		Stamina,
		Red,
		UITypeNum
	};
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
	SpriteRender*m_spriteRender[UITypeNum] = { nullptr };				//�X�v���C�g�����_�[
	
	CVector3 m_spritePos[UITypeNum] = { CVector3::Zero() };				    //2D�摜�̈ʒu
	CVector3 m_spriteSca [UITypeNum] = { CVector3::One() };					//2D�摜�̊g�嗦
	CQuaternion m_spriteRot[UITypeNum] = { CQuaternion::Identity() };		//2D�摜�̉�]
	float a = 0.0f;
};

