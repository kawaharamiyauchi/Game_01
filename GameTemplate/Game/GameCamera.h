#pragma once
#include"IGameObject.h"
#include "Game.h"
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	enum CameraState {
		normal,
		GameClear,
		GameOver
	};
	/// <summary>
	/// �J�����̈ʒu�����擾
	/// </summary>
	/// <returns�@m_position>�J�����̈ʒu</returns>
	CVector3 GetPosition()
	{
		return m_toCameraPos;
	}

	/// <summary>
	/// �J�����̈ʒu��ݒ�
	/// </summary>
	/// <param name="pos">�J�����̈ʒu</param>
	void SetPosition(CVector3 pos)
	{
		m_toCameraPos = pos;
	}
	/// <summary>
	/// �����_�̍��W�ݒ�
	/// </summary>
	/// <param name="t">�ݒ肷�钍���_�ʒu���W</param>
	void SetTarget(CVector3 t)
	{
		m_target = t;
	}

	void Reset();
	
	void ChangeCameraState();
	void Update();		//�X�V����
	void Render();		//�`�揈��
private:
	CVector3 m_toCameraPos = CVector3::Zero();		//�ʒu
	CVector3 m_target = CVector3::Zero();		//�����_�̍��W
	CVector3 m_position;
	int m_timer = 0;
	CameraState m_CS = normal;
};

