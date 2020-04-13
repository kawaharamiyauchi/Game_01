#pragma once
#include "IGameObject.h"
#include "SpriteRender.h"
class FontRender;
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
		
		//DropItem
		Herbs,					//薬草
		PoisonouMushroom,		//毒キノコ
		mushroom,				//キノコ
		Treenut,				//木の実
		smallstone,				//小石
		B_L_LizardTail,				//青紋小竜の尻尾
		B_L_LizardClaw,				//青紋小竜の爪
		B_L_LizardScales,			//青紋小竜の鱗
		B_L_LizardFang,				//青紋小竜の牙

		TypeNum,

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
		int SellingPrice;
		
	};
	// Herbs,					//薬草
	//PoisonouMushroom,			//毒キノコ
	//	mushroom,				//キノコ
	//	Treenut,				//木の実
	//	smallstone,				//小石
	//	B_L_LizardTail,			//青紋小竜の尻尾
	//	B_L_LizardClaw,			//青紋小竜の爪
	//	B_L_LizardScales,		//青紋小竜の鱗
	void InitItem(ItemData *Item, IsUse isUse, int num, int max,int price)
	{
		if (Item != nullptr) {
			Item->isUse = isUse;
			Item->num = num;
			Item->max = max;
			Item->SellingPrice = price;
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
		ReturnCamp,
		Result,

		FrameIcon00,
		FrameIcon01,
		FrameIcon02,
		FrameIcon03,

		FrameIcon04,
		FrameIcon05,
		FrameIcon06,
		FrameIcon07,
		FrameIcon08,

		TargetMark,
		ManeyPouch,

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

	enum FontType
	{
		QuestName,				//クエスト名
		QuestSummary,			//クエストの概要
		PrizeMoney,				//報酬金
		RequesterName,			//依頼主名

		HaveMoney,				//所持金
		GoalNum,				//目標の数
		QuestPoint,				//現在のクエストターゲット達成数

		ItemNumber,				//UserItem用　アイテム数
		DropItemNumber,			//DropItem用　アイテム数
		ItemName,				//Itemの名称
		ItemSummry,				//Itemの説明文

		U_Pouch,				//道具ポーチ
		D_Pouch,				//素材ポーチ
		m_help,
		m_exit,

		Resulttime,				//時間
		ResultMoney,			//リザルトで渡される金
		FontTypeNum				

	};
	enum PouseMenuButton
	{
		UserItemPouch,
		DropItemPouch,
		Help,
		Exit,
		MenuSize

	};
	struct FontPalam {
		wchar_t m_text[255] =L"NonText";
		
		bool frameFlag = false;
		float m_frameWidth = 0.0f;
		CVector4 m_textColor = {0.0f,0.0f,0.0f,0.0f};
		CVector2 pos = CVector2::Zero();
		float size = 1.0f;
		CVector2 pivot = { 0.5f,0.5f };

	};
	UI();
	~UI();
	void PauseMenu();
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

	bool GetResultFlag()const
	{
		return ResultFlag;
	}
	void ResetPauseMenuPalam()
	{
		MenuStageNum = 0;
		p_target = 0;
	}
	void SetFont(int ft, wchar_t text[15],bool frameflag, float frame, CVector4& color, CVector2& pos, float size, CVector2& pivot);

	void SetFontPalam();
	
	void ClearDraw();
	void GameOverDraw();
	
	
private:
	SpriteRender*m_spriteRender[UITypeNum] = { nullptr };				//スプライトレンダー
	SpriteRender*m_ItemRender[ItemSpriteTypeNum] = { nullptr };
	SpriteRender*m_Rendertest =nullptr;

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
	int haveItemNum = 0;			//選択対象のアイテム数
	int lastItem = 0;				//登録されているアイテムの末尾
	int nextItem = 0;				//ItemUIの右に該当するアイテム
	int backItem = 0;				//ItemUIの左に該当するアイテム
	int nonhaveItem = 0;			
	int targetItem = 0;				//選択中のアイテム
	
	int DropTarget = 0;				//DropItem登録されている配列の添え字
	int d_target = 0;				//選択中のDropItem

	int p_target = 0;				//ポーズ画面で選択中のアイコン

	int mainItem = 0;
	bool AttackEvent = false;
	bool ResultFlag = false;
	bool MenuFlag[MenuSize] = { false };
	int MenuStageNum = 0;			//Menuの段階

	std::vector<int> m_ItemList;
	std::vector<int> m_DropItemList;
	FontRender *m_font[FontTypeNum] = { nullptr };
	FontPalam m_fontPalam[FontTypeNum];
	
	PouseMenuButton m_state = UserItemPouch;
};

