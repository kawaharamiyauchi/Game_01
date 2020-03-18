#pragma once
#include "IGameObject.h"
#include "SpriteRender.h"

class Item:public IGameObject
{
public:
	Item();
	~Item() {}
	void Update();
	void Render();
	enum ItemType
	{
		noneItem,
		kaihukuyaku,
		ItemDummy00,
		ItemDummy01,
		TypeNum
	};
	enum IsUse
	{
		User_Item,
		Drop_Item
	};
	struct ItemData
	{
		IsUse isUse;
		int num;
		int max;
		
	};
	void InitItem(ItemData *Item, IsUse isUse, int num, int max)
	{
		if (Item != nullptr) {
			Item->isUse = isUse;
			Item->num = num;
			Item->max = max;
		}
	}
	bool GetItem(ItemType type,int num)
	{
		if (m_Item[type].max >= m_Item[type].num + num)
		{
			m_Item[type].num += num;
			return true;
		}
		else return false;
	}
	int UseItem();
	ItemData GetData(int type)
	{
		return m_Item[type];
	}
private:
	ItemData m_Item[TypeNum];
	ItemType m_select = noneItem;
	//std::vector<ItemType> m_useItemList;
};
class UI:public IGameObject
{
public:

	enum UIType {

		
		HP,
		Stamina,
		Red,
		actionLine,
		Clear,
		GameOver,
		QuestPaper,
		Pause,
		UITypeNum
	};
	enum ItemUI
	{
		nonItem,
		kaihukuyaku,
		ItemDummy00,
		ItemDummy01,
		ItemSpriteTypeNum
	};
	UI();
	~UI();
	/// <summary>
	/// UIの更新処理。
	/// </summary>
	void Update();
	/// <summary>
	/// UIの描画処理。
	/// </summary>
	void Render()
	{

	}
	int CheckItem();
	void ChangeItem();

	int GetTargetItem()const
	{
		return targetItem;
	}
	void ClearDraw();
	void GameOverDraw();
private:
	SpriteRender*m_spriteRender[UITypeNum] = { nullptr };				//スプライトレンダー
	SpriteRender*m_ItemRender[ItemSpriteTypeNum] = { nullptr };
	SpriteRender*m_sideRender =nullptr;

	CVector3 m_spritePos[UITypeNum] = { CVector3::Zero() };				    //2D画像の位置
	CVector3 m_spriteSca [UITypeNum] = { CVector3::One() };					//2D画像の拡大率
	CQuaternion m_spriteRot[UITypeNum] = { CQuaternion::Identity() };		//2D画像の回転
	/// <summary>
	/// Itemの位置　と拡大率
	/// </summary>
	CVector3 m_mainItemPos = { 400.0f, -200.0f, 1.0f };
	CVector3 m_nextItemPos = { 550.0f, -200.0f, 1.0f };
	CVector3 m_backItemPos = { 250.0f, -200.0f, 1.0f };

	CVector3 m_mainItemSca = { 2.0f,2.0f,1.0f };
	CVector3 m_sideItemSca = CVector3::One();

	float m_alpha = 0.0f;
	float hp = 0.0f;
	int haveItemNum = 0;
	int lastItem = 0;
	int nextItem = 0;
	int backItem = 0;
	int nonhaveItem = 0;
	int targetItem = 0;
	int mainItem = 0;
	bool AttackEvent = false;
	std::vector<int> m_ItemList;
};

