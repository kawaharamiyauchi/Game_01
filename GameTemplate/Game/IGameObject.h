#pragma once
class IGameObject
{
public:
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
private:
	bool isReqDelete = false;



};

