#pragma once
#include "IGameObject.h"
#include "SpriteRender.h"
#include "SkinModelRender.h"
#include"GhostObject.h"
class FontRender;

class ItemBase:public IGameObject
{
public:
	ItemBase();
	~ItemBase() {}
	void Update();
	void Render();
	enum ItemType
	{

		//UserItem
		noneItem,
		kaihukuyaku,
		ItemDummy00,
		ItemDummy01,
		
		//DropItem
		Herbs,					//��
		PoisonouMushroom,		//�ŃL�m�R
		mushroom,				//�L�m�R
		Treenut,				//�؂̎�
		smallstone,				//����
		B_L_LizardTail,				//�䏬���̐K��
		B_L_LizardClaw,				//�䏬���̒�
		B_L_LizardScales,			//�䏬���̗�
		B_L_LizardFang,				//�䏬���̉�

		B_LizardTail,			//�䗳�̐K��
		B_LizardHorn,			//�䗳�̊p
		B_LizardFang,			//�䗳�̉�
		B_LizardScales,			//�䗳�̗�
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
	// Herbs,					//��
	//PoisonouMushroom,			//�ŃL�m�R
	//	mushroom,				//�L�m�R
	//	Treenut,				//�؂̎�
	//	smallstone,				//����
	//	B_L_LizardTail,			//�䏬���̐K��
	//	B_L_LizardClaw,			//�䏬���̒�
	//	B_L_LizardScales,		//�䏬���̗�
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
		OrdersQuest,
		ItemNext,
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
		QuestName,				//�N�G�X�g��
		QuestSummary,			//�N�G�X�g�̊T�v
		PrizeMoney,				//��V��
		RequesterName,			//�˗��喼

		HaveMoney,				//������
		GoalNum,				//�ڕW�̐�
		QuestPoint,				//���݂̃N�G�X�g�^�[�Q�b�g�B����

		ItemNumber,				//UserItem�p�@�A�C�e����
		DropItemNumber,			//DropItem�p�@�A�C�e����
		
		ItemName00,				//ItemBase�̖���
		ItemName01,
		ItemName02,
		ItemName03,
		ItemName04,


		ItemSummry,				//ItemBase�̐�����

		U_Pouch,				//����|�[�`
		D_Pouch,				//�f�ރ|�[�`
		m_help,
		m_exit,

		
		Resulttime,				//����
		ResultMoney,			//���U���g�œn������

		
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
	enum SoundType
	{
		Select,
		SoundTypeNum
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
	struct PickTextParts
	{
		ItemBase::ItemType pickItemType = ItemBase::ItemType::Herbs;
		int pickNum = 0;

	};
	UI();
	~UI();
	void PauseMenu();
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
	bool IsResultEnd()const
	{
		return m_endqestFlag;
	}
	void ResetPauseMenuPalam()
	{
		MenuStageNum = 0;
		p_target = 0;
	}
	void ResetList()
	{
		m_ItemList.clear();
		m_DropItemList.clear();
	}


	void PushPickText(FontRender* fontRender);
	void SetFont(int ft, wchar_t text[15],bool frameflag, float frame, CVector4& color, CVector2& pos, float size, CVector2& pivot);

	void SetFontPalam();
	
	void ClearDraw();
	void GameOverDraw();
	
	
private:
	SpriteRender*m_spriteRender[UITypeNum] = { nullptr };				//�X�v���C�g�����_�[
	SpriteRender*m_ItemRender[ItemSpriteTypeNum] = { nullptr };
	SpriteRender*m_Rendertest =nullptr;

	CVector3 m_spritePos[UITypeNum] = { CVector3::Zero() };				    //2D�摜�̈ʒu
	CVector3 m_spriteSca [UITypeNum] = { CVector3::One() };					//2D�摜�̊g�嗦
	CQuaternion m_spriteRot[UITypeNum] = { CQuaternion::Identity() };		//2D�摜�̉�]
	/// <summary>
	/// Item�̈ʒu�@�Ɗg�嗦
	/// </summary>
	CVector3 m_mainItemPos = { 400.0f, -200.0f, 1.0f };
	CVector3 m_nextItemPos = { 550.0f, -200.0f, 1.0f };
	CVector3 m_backItemPos = { 250.0f, -200.0f, 1.0f };

	CVector3 m_mainItemSca = { 2.0f,2.0f,1.0f };
	CVector3 m_sideItemSca = CVector3::One();

	float m_spriteAlpha[UITypeNum] = { 0.0f };
	float hp = 0.0f;
	int haveItemNum = 0;			//�I��Ώۂ̃A�C�e����
	int lastItem = 0;				//�o�^����Ă���A�C�e���̖���
	int nextItem = 0;				//ItemUI�̉E�ɊY������A�C�e��
	int backItem = 0;				//ItemUI�̍��ɊY������A�C�e��
	int nonhaveItem = 0;			
	int targetItem = 0;				//�I�𒆂̃A�C�e��
	
	int DropTarget = 0;				//DropItem�o�^����Ă���z��̓Y����
	int d_target[5] = { 0 };				//�I�𒆂�DropItem

	int UserTarget = 1;
	int u_target[5] = { 0 };

	int p_target = 0;				//�|�[�Y��ʂőI�𒆂̃A�C�R��

	int mainItem = 0;

	int sizeTag = 0;
	bool AttackEvent = false;
	bool ResultFlag = false;
	bool m_endqestFlag = false;

	bool MenuFlag[MenuSize] = { false };
	int MenuStageNum = 0;			//Menu�̒i�K

	std::vector<int> m_ItemList;
	std::vector<int> m_DropItemList;
	std::vector<wchar_t> m_picktext[255];
	std::vector<FontRender*> m_dropFontlist = { nullptr };
	FontRender *m_font[FontTypeNum] = { nullptr };
	FontPalam m_fontPalam[FontTypeNum];
	PickTextParts m_pickTextParts;
	PouseMenuButton m_state = UserItemPouch;
	CSoundSource m_sound[SoundTypeNum];
};

class Item :public IGameObject
{
public:
	Item(); 
	~Item();
	bool Start();
	void SetStageNum(int num)
	{
		m_stageNum = num;
	}
	enum DropType
	{
		PickHerbs,
		LBD_Die,
		BD_Die

	};
	void InitFontPalam(wchar_t text[255]);
	void Update();
	void Render() {}
	void MonoTypeItemCreate(CVector3 pos, CQuaternion rot, float size, ItemBase::ItemType type, int DropMax);
	void RandTypeItemCreate(CVector3 &pos, CQuaternion rot, float size, DropType type, int DropMax);

private:
	wchar_t m_picktext[15] = L" ����";
	GhostObject m_ghostObject;
	CVector3 m_position = CVector3::Zero();
	float m_size = 0.0f;
	CQuaternion m_rotation = CQuaternion::Identity();
	ItemBase::ItemType m_type = ItemBase::ItemType::Herbs;
	CVector2 m_fontpos = {-620.0f , -250.0f};
	int m_ItemNum = 0;
	int m_max = 0;
	int m_stageNum =0;
	bool m_pickFlag = false;
	UI::FontPalam m_fontPalam;
	FontRender *m_fontRender = nullptr;
	SkinModelRender *m_skinModelRender = nullptr;
	CSoundSource m_sound;
};