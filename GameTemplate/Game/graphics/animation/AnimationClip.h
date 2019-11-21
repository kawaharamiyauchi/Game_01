/*!
 *@brief	�A�j���[�V�����N���b�v�B
 */

#pragma once

//////////////////////////////////////////////////////////////////////
// �e��\����
//////////////////////////////////////////////////////////////////////
/*!
*@brief	�A�j���[�V�����N���b�v�̃w�b�_�[�B
*/
struct AnimClipHeader {
	std::uint32_t numKey;				//!<�L�[�t���[���̐��B
	std::uint32_t numAnimationEvent;	//!<�A�j���[�V�����C�x���g�̐��B
};
/*!
*@brief	�A�j���[�V�����C�x���g
*@�A�j���[�V�����C�x���g�͖��Ή��B
* ��肽�������玩���Ŏ�������悤�ɁB
*/
struct AnimationEventData {
	float	invokeTime;					//!<�A�j���[�V�����C�x���g���������鎞��(�P��:�b)
	std::uint32_t eventNameLength;		//!<�C�x���g���̒����B
};
/*!
*@brief	�L�[�t���[���B
*/
struct Keyframe {
	std::uint32_t boneIndex;	//!<�{�[���C���f�b�N�X�B
	float time;					//!<���ԁB
	CMatrix transform;			//!<�g�����X�t�H�[���B
};
/// <summary>
/// �A�j���[�V�����C�x���g
/// </summary>
struct AnimationEvent {
	float	invokeTime;					//!<�A�j���[�V�����C�x���g���������鎞��(�P��:�b)
	std::uint32_t eventNameLength;		//!<�C�x���g���̒����B
};
/*!
*@brief	�L�[�t���[���B
*/
struct KeyframeRow {
	std::uint32_t boneIndex;	//!<�{�[���C���f�b�N�X�B
	float time;					//!<���ԁB
	CVector3 transform[4];		//!<�g�����X�t�H�[���B
};

/// <summary>
/// �A�j���[�V�����C�x���g
/// </summary>
class CAnimationEvent {
public:
	CAnimationEvent()
	{

	}
	/// <summary>
	/// �C�x���g�������Ԃ̐ݒ�
	/// </summary>
	/// <returns>�C�x���g�̔�������</returns>
	float GetInvokeTime()const
	{
		return m_invokeTime;
	}
	/// <summary>
	/// �C�x���g�����擾
	/// </summary>
	/// <returns>�C�x���g�̖��O</returns>
	const wchar_t*GetEventName()const
	{
		return m_eventName.c_str();
	}
	/// <summary>
	/// �C�x���g�������ς݂�����
	/// </summary>
	/// <returns>�C�x���g�������ς݂��ǂ����̃t���O</returns>
	bool GetisInvoked()const
	{
		return m_isInvoked;
	}
	/// <summary>
	/// �C�x���g�������Ԃ�ݒ�
	/// </summary>
	/// <param name="time">�C�x���g��������</param>
	void SetInvokeTime(float time)
	{
		m_invokeTime = time;
	}
	/// <summary>
	/// �C�x���g����ݒ�
	/// </summary>
	/// <param name="name">�C�x���g�̖��O</param>
	void SetEventName(const wchar_t* name)
	{
		m_eventName = name;
	}
	/// <summary>
	/// �C�x���g�������ς݂̃t���O��ݒ�
	/// </summary>
	/// <param name="flag">�C�x���g�������ς݂��ǂ����̃t���O</param>
	void SetInvokedFlag(bool flag)
	{
		m_isInvoked = flag;
	}
private:
	bool m_isInvoked = false;	//!<�C�x���g�����ς݁H
	float m_invokeTime;			//!<�C�x���g�������ԁB
	std::wstring m_eventName;	//!<�C�x���g���B
};
/*!
*@brief	�A�j���[�V�����N���b�v�B
*/
class AnimationClip  {
public:
	//�^�C�v�ʂ��������炵���āA�������̂�std::vector<KeyFrame*>�̕ʖ���`�B
	using keyFramePtrList = std::vector<Keyframe*>;
	/*!
	* @brief	�R���X�g���N�^
	*/
	AnimationClip() 
	{
	}
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~AnimationClip();
	/*!
	*@brief	�A�j���[�V�����N���b�v�����[�h�B
	*@param[in]	filePath	�t�@�C���p�X�B
	*/
	void Load(const wchar_t* filePath,const wchar_t* clipName);

	/*!
	*@brief	���[�v����H
	*/
	bool IsLoop() const
	{
		return m_isLoop;
	}
	/*!
	*@brief	���[�v�t���O��ݒ肷��B
	*/
	void SetLoopFlag(bool flag)
	{
		m_isLoop = flag;
	}
	/*!
	*@brief
	*/
	const std::vector<keyFramePtrList>& GetKeyFramePtrListArray() const
	{
		return m_keyFramePtrListArray;
	}
	const keyFramePtrList& GetTopBoneKeyFrameList() const
	{
		return *m_topBoneKeyFramList;
	}

	/// <summary>
	/// �A�j���[�V�����C�x���g���擾
	/// </summary>
	/// <returns>�A�j���[�V�����C�x���g</returns>
	std::unique_ptr<CAnimationEvent[]>& GetAnimationEvent()
	{
		return m_animationEvent;
	}
	/// <summary>
	/// �A�j���[�V�����C�x���g�̐����擾
	/// </summary>
	/// <returns>�A�j���[�V�����C�x���g�̐�</returns>
	int GetNumAnimationEvent() const
	{
		return m_numAnimationEvent;
	}

	const wchar_t* GetName()const
	{
		return m_clipName.c_str();
	}
private:

	std::wstring m_clipName;	//!<�A�j���[�V�����N���b�v�̖��O�B
	int		m_numAnimationEvent = 0;	//�A�j���[�V�����C�x���g�̐��B
	using KeyframePtr = std::unique_ptr<Keyframe>;
	bool m_isLoop = false;									//!<���[�v�t���O�B
	std::vector<Keyframe*> m_keyframes;						//�S�ẴL�[�t���[���B
	std::vector<keyFramePtrList> m_keyFramePtrListArray;	//�{�[�����Ƃ̃L�[�t���[���̃��X�g���Ǘ����邽�߂̔z��B
	std::unique_ptr<CAnimationEvent[]>	m_animationEvent;			//�A�j���[�V�����C�x���g�B
						
	keyFramePtrList* m_topBoneKeyFramList = nullptr;
	using CAnimationClipPtr = std::unique_ptr<AnimationClip>;
};

