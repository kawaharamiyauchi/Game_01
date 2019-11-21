/*!
 *@brief	アニメーションクリップ。
 */

#pragma once

//////////////////////////////////////////////////////////////////////
// 各種構造体
//////////////////////////////////////////////////////////////////////
/*!
*@brief	アニメーションクリップのヘッダー。
*/
struct AnimClipHeader {
	std::uint32_t numKey;				//!<キーフレームの数。
	std::uint32_t numAnimationEvent;	//!<アニメーションイベントの数。
};
/*!
*@brief	アニメーションイベント
*@アニメーションイベントは未対応。
* やりたかったら自分で実装するように。
*/
struct AnimationEventData {
	float	invokeTime;					//!<アニメーションイベントが発生する時間(単位:秒)
	std::uint32_t eventNameLength;		//!<イベント名の長さ。
};
/*!
*@brief	キーフレーム。
*/
struct Keyframe {
	std::uint32_t boneIndex;	//!<ボーンインデックス。
	float time;					//!<時間。
	CMatrix transform;			//!<トランスフォーム。
};
/// <summary>
/// アニメーションイベント
/// </summary>
struct AnimationEvent {
	float	invokeTime;					//!<アニメーションイベントが発生する時間(単位:秒)
	std::uint32_t eventNameLength;		//!<イベント名の長さ。
};
/*!
*@brief	キーフレーム。
*/
struct KeyframeRow {
	std::uint32_t boneIndex;	//!<ボーンインデックス。
	float time;					//!<時間。
	CVector3 transform[4];		//!<トランスフォーム。
};

/// <summary>
/// アニメーションイベント
/// </summary>
class CAnimationEvent {
public:
	CAnimationEvent()
	{

	}
	/// <summary>
	/// イベント発生時間の設定
	/// </summary>
	/// <returns>イベントの発生時間</returns>
	float GetInvokeTime()const
	{
		return m_invokeTime;
	}
	/// <summary>
	/// イベント名を取得
	/// </summary>
	/// <returns>イベントの名前</returns>
	const wchar_t*GetEventName()const
	{
		return m_eventName.c_str();
	}
	/// <summary>
	/// イベントが発生済みか判定
	/// </summary>
	/// <returns>イベントが発生済みかどうかのフラグ</returns>
	bool GetisInvoked()const
	{
		return m_isInvoked;
	}
	/// <summary>
	/// イベント発生時間を設定
	/// </summary>
	/// <param name="time">イベント発生時間</param>
	void SetInvokeTime(float time)
	{
		m_invokeTime = time;
	}
	/// <summary>
	/// イベント名を設定
	/// </summary>
	/// <param name="name">イベントの名前</param>
	void SetEventName(const wchar_t* name)
	{
		m_eventName = name;
	}
	/// <summary>
	/// イベントが発生済みのフラグを設定
	/// </summary>
	/// <param name="flag">イベントが発生済みかどうかのフラグ</param>
	void SetInvokedFlag(bool flag)
	{
		m_isInvoked = flag;
	}
private:
	bool m_isInvoked = false;	//!<イベント発生済み？
	float m_invokeTime;			//!<イベント発生時間。
	std::wstring m_eventName;	//!<イベント名。
};
/*!
*@brief	アニメーションクリップ。
*/
class AnimationClip  {
public:
	//タイプ量が長ったらしくて、うざいのでstd::vector<KeyFrame*>の別名定義。
	using keyFramePtrList = std::vector<Keyframe*>;
	/*!
	* @brief	コンストラクタ
	*/
	AnimationClip() 
	{
	}
	/*!
	*@brief	デストラクタ。
	*/
	~AnimationClip();
	/*!
	*@brief	アニメーションクリップをロード。
	*@param[in]	filePath	ファイルパス。
	*/
	void Load(const wchar_t* filePath,const wchar_t* clipName);

	/*!
	*@brief	ループする？
	*/
	bool IsLoop() const
	{
		return m_isLoop;
	}
	/*!
	*@brief	ループフラグを設定する。
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
	/// アニメーションイベントを取得
	/// </summary>
	/// <returns>アニメーションイベント</returns>
	std::unique_ptr<CAnimationEvent[]>& GetAnimationEvent()
	{
		return m_animationEvent;
	}
	/// <summary>
	/// アニメーションイベントの数を取得
	/// </summary>
	/// <returns>アニメーションイベントの数</returns>
	int GetNumAnimationEvent() const
	{
		return m_numAnimationEvent;
	}

	const wchar_t* GetName()const
	{
		return m_clipName.c_str();
	}
private:

	std::wstring m_clipName;	//!<アニメーションクリップの名前。
	int		m_numAnimationEvent = 0;	//アニメーションイベントの数。
	using KeyframePtr = std::unique_ptr<Keyframe>;
	bool m_isLoop = false;									//!<ループフラグ。
	std::vector<Keyframe*> m_keyframes;						//全てのキーフレーム。
	std::vector<keyFramePtrList> m_keyFramePtrListArray;	//ボーンごとのキーフレームのリストを管理するための配列。
	std::unique_ptr<CAnimationEvent[]>	m_animationEvent;			//アニメーションイベント。
						
	keyFramePtrList* m_topBoneKeyFramList = nullptr;
	using CAnimationClipPtr = std::unique_ptr<AnimationClip>;
};

