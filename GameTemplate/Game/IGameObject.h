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
	///	更新関数
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画
	/// </summary>

	virtual void Render() = 0;
	/// <summary>
	/// 削除リクエスト
	/// </summary>

	void RequestDelete()
	{
		isReqDelete = true;
	}
	virtual bool Start()
	{
		return true;
	}
	//条件を満たせば一度だけStart関数を実行する
	void StartWrapper()
	{
		if (!m_isStart&&!isReqDelete) {
			if (Start()) {
				m_isStart = true;
			}
		}
	}
	//条件を満たせばUpdate関数を実行する
	void UpdateWrapper()
	{
		if ( m_isStart && !isReqDelete) {
			Update();
		}
	}
	/// <summary>
	/// 削除リクエストを受けているか調べる。
	/// </summary>
	///<returns>
	///trueが帰ってきたら、リクエストを受けている
	///</returns>

	bool IsRequestDelete()
	{
		return isReqDelete;
	}

	virtual void OnDestroy() {}
private:
	bool isReqDelete = false;
protected:
	bool m_isStart = false;					//スタート関数が完了したかどうか



};

