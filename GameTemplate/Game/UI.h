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
		Herbs,					//��
		PoisonouMushroom,		//�ŃL�m�R
		mushroom,				//�L�m�R
		Treenut,				//�؂̎�
		smallstone,				//����
		B_L_LizardTail,				//�䏬���̐K��
		B_L_LizardClaw,				//�䏬���̒�
		B_L_LizardScales,			//�䏬���̗�
		B_L_LizardFang,				//�䏬���̉�

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
		ItemName,				//Item�̖���
		ItemSummry,				//Item�̐�����

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

	float m_alpha = 0.0f;
	float hp = 0.0f;
	int haveItemNum = 0;			//�I��Ώۂ̃A�C�e����
	int lastItem = 0;				//�o�^����Ă���A�C�e���̖���
	int nextItem = 0;				//ItemUI�̉E�ɊY������A�C�e��
	int backItem = 0;				//ItemUI�̍��ɊY������A�C�e��
	int nonhaveItem = 0;			
	int targetItem = 0;				//�I�𒆂̃A�C�e��
	
	int DropTarget = 0;				//DropItem�o�^����Ă���z��̓Y����
	int d_target = 0;				//�I�𒆂�DropItem

	int p_target = 0;				//�|�[�Y��ʂőI�𒆂̃A�C�R��

	int mainItem = 0;
	bool AttackEvent = false;
	bool ResultFlag = false;
	bool MenuFlag[MenuSize] = { false };
	int MenuStageNum = 0;			//Menu�̒i�K

	std::vector<int> m_ItemList;
	std::vector<int> m_DropItemList;
	FontRender *m_font[FontTypeNum] = { nullptr };
	FontPalam m_fontPalam[FontTypeNum];
	
	PouseMenuButton m_state = UserItemPouch;
};

