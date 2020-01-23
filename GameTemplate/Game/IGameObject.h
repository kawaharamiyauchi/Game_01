#pragma once
class IGameObject
{
public:
	IGameObject()
	{
		m_isStart =false;
	}
	virtual ~IGameObject() {}
	/// <summary>
	///	�X�V�֐�
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`��
	/// </summary>

	virtual void Render() = 0;
	/// <summary>
	/// �폜���N�G�X�g
	/// </summary>

	void RequestDelete()
	{
		isReqDelete = true;
	}
	virtual bool Start()
	{
		return true;
	}
	//�����𖞂����Έ�x����Start�֐������s����
	void StartWrapper()
	{
		if (!m_isStart&&!isReqDelete) {
			if (Start()) {
				m_isStart = true;
			}
		}
	}
	//�����𖞂�����Update�֐������s����
	void UpdateWrapper()
	{
		if ( m_isStart && !isReqDelete) {
			Update();
		}
	}
	/// <summary>
	/// �폜���N�G�X�g���󂯂Ă��邩���ׂ�B
	/// </summary>
	///<returns>
	///true���A���Ă�����A���N�G�X�g���󂯂Ă���
	///</returns>

	bool IsRequestDelete()
	{
		return isReqDelete;
	}

	virtual void OnDestroy() {}
private:
	bool isReqDelete = false;
protected:
	bool m_isStart = false;					//�X�^�[�g�֐��������������ǂ���



};

