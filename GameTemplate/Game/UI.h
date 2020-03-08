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
		kaihukuyaku,
		b,
		c,
		d,
		e,
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
		if (m_Item[type].max > m_Item[type].num + num)
		{
			m_Item[type].num += num;
			return true;
		}
		else return false;
	}
	bool UseItem(ItemType type);
	ItemData GetData(ItemType type)
	{
		return m_Item[type];
	}
private:
	ItemData m_Item[TypeNum];
	//std::vector<ItemData> m_useItemList;
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
		kaihukuyaku,
		QuestPaper,
		UITypeNum
	};
	UI();
	~UI();
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
	
	void ClearDraw();
	void GameOverDraw();
private:
	SpriteRender*m_spriteRender[UITypeNum] = { nullptr };				//�X�v���C�g�����_�[
	
	CVector3 m_spritePos[UITypeNum] = { CVector3::Zero() };				    //2D�摜�̈ʒu
	CVector3 m_spriteSca [UITypeNum] = { CVector3::One() };					//2D�摜�̊g�嗦
	CQuaternion m_spriteRot[UITypeNum] = { CQuaternion::Identity() };		//2D�摜�̉�]
	float m_alpha = 0.0f;
	float hp = 0.0f;
	bool AttackEvent = false;
	
};

