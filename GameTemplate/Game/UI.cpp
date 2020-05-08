#include "stdafx.h"
#include "UI.h"
#include"Game.h"
#include"Player.h"
#include "QuestManager.h"
#include"Dragon.h"
#include"FontRender.h"

const float LIMIT_Y = 250.0f;

ItemBase::ItemBase()
{
	InitItem(&m_Item[noneItem], User_Item, 255, 255,0);
	InitItem(&m_Item[kaihukuyaku], User_Item, 5, 10,100);
	InitItem(&m_Item[ItemDummy00], User_Item, 2, 10,100);
	InitItem(&m_Item[ItemDummy01], User_Item, 6, 10,100);

	/*InitItem(&m_ItemBase[Herbs], Drop_Item, 5, 99,20);
	InitItem(&m_ItemBase[PoisonouMushroom], Drop_Item, 6, 99,20);
	InitItem(&m_ItemBase[mushroom],Drop_Item, 10, 99,20);
	InitItem(&m_ItemBase[Treenut], Drop_Item, 11, 99,1);
	InitItem(&m_ItemBase[smallstone], Drop_Item, 12, 99,1);
	InitItem(&m_ItemBase[B_L_LizardTail], Drop_Item, 3, 99,5000);
	InitItem(&m_ItemBase[B_L_LizardClaw], Drop_Item, 1, 99,2500);
	InitItem(&m_ItemBase[B_L_LizardScales], Drop_Item, 3, 99,100);
	InitItem(&m_ItemBase[B_L_LizardFang], Drop_Item, 3, 99,2500);*/


	InitItem(&m_Item[Herbs], Drop_Item, 0, 99, 20);
	InitItem(&m_Item[PoisonouMushroom], Drop_Item, 0, 99, 20);
	InitItem(&m_Item[mushroom], Drop_Item,0, 99, 20);
	InitItem(&m_Item[Treenut], Drop_Item, 0, 99, 1);
	InitItem(&m_Item[smallstone], Drop_Item, 0, 99, 1);
	InitItem(&m_Item[B_L_LizardTail], Drop_Item, 0, 99, 5000);
	InitItem(&m_Item[B_L_LizardClaw], Drop_Item, 0, 99, 2500);
	InitItem(&m_Item[B_L_LizardScales], Drop_Item, 0, 99, 100);
	InitItem(&m_Item[B_L_LizardFang], Drop_Item, 0, 99, 2500);
	InitItem(&m_Item[B_LizardTail], Drop_Item, 0 ,99, 10000);
	InitItem(&m_Item[B_LizardHorn], Drop_Item, 0, 99, 5000);
	InitItem(&m_Item[B_LizardFang], Drop_Item, 0, 99, 5000);
	InitItem(&m_Item[B_LizardScales], Drop_Item, 0, 99, 1000);

}

int ItemBase::UseItem()
{
	auto m_selectItem = Game::instance()->m_UI->GetTargetItem();
	if (m_Item[m_selectItem].num > 0 && m_selectItem > 0)
	{
		m_Item[m_selectItem].num--;
		return m_selectItem;
	}

	else return -1;
}
void ItemBase::Update()
{

}
void ItemBase::Render()
{

}



Item::Item()
{
		m_fontRender = GameObjectManager::instance().NewGO<FontRender>();
		
		m_sound.Init(L"Assets/sound/pick2.wav");
		InitFontPalam(L"Init");
}

Item::~Item()
{
	m_ghostObject.Release();
	
	GameObjectManager::instance().DeleteGO(m_fontRender);
}
bool Item::Start()
{
	SetStageNum(Game::instance()->GetStageNum());
	return true;
}
void Item::InitFontPalam(wchar_t text[255])
{
	wcscpy(m_fontPalam.m_text, text);
	m_fontPalam.frameFlag = true;
	m_fontPalam.m_frameWidth = 5.0f;
	m_fontPalam.pos =m_fontpos;
	m_fontPalam.size = 0.6f;
	m_fontPalam.m_textColor = {0.0f,0.0f,0.0f,0.0f};
	m_fontRender->SetShadowParam(false, 0.0f, CVector4::Black());


}
void Item::MonoTypeItemCreate(CVector3 pos,CQuaternion rot,float size, ItemBase::ItemType type,int DropMax)
{
	m_skinModelRender = GameObjectManager::instance().NewGO<SkinModelRender>();
	if (type == ItemBase::Herbs)
	{
		m_skinModelRender->Init(L"Assets/modelData/Herbs.cmo");
		wcscpy(m_fontPalam.m_text, L"薬草");
	}

	m_skinModelRender->SetPosition(pos);
	m_skinModelRender->SetScale(CVector3::One());
	m_position = pos;
	m_rotation = rot;
	m_size = size;
	m_max = DropMax;
	m_type = type;
	m_ghostObject.CreateSphere(m_position, m_rotation,30.0f);
	

}
void Item::RandTypeItemCreate(CVector3 & pos, CQuaternion rot, float size, DropType type, int DropMax)
{
	m_position = pos;
	m_rotation = rot;
	m_size = size;
	m_max = DropMax;
	m_ghostObject.CreateSphere(m_position, m_rotation, m_size);


	


	switch (type)
	{
	case Item::PickHerbs:
		m_skinModelRender = GameObjectManager::instance().NewGO<SkinModelRender>();
		m_skinModelRender->SetPosition(m_position);
		m_skinModelRender->SetScale(CVector3::One());
		break;
	case Item::LBD_Die:
		int m_l_itemtype;
		m_l_itemtype = rand() % 4 +9;
		
		m_type = (ItemBase::ItemType)m_l_itemtype;
		switch (m_type)
		{
		case ItemBase::B_L_LizardTail:
			m_max = 1;
			wcscpy(m_fontPalam.m_text, L"青紋小竜の尻尾");
			break;
		case ItemBase::B_L_LizardClaw:
			m_max = DropMax;
			wcscpy(m_fontPalam.m_text, L"青紋小竜の爪");

			break;
		case ItemBase::B_L_LizardScales:
			wcscpy(m_fontPalam.m_text, L"青紋小竜の鱗");

			m_max = DropMax;
			break;
		case ItemBase::B_L_LizardFang:
			m_max = DropMax;
			wcscpy(m_fontPalam.m_text, L"青紋小竜の牙");

			break;
		
		default:
			break;
		}
		break;
	case Item::BD_Die:
		int m_itemtype;
		m_itemtype = rand() % 4 + 13;
		m_type = (ItemBase::ItemType)m_itemtype;
		switch (m_type)
		{
			
		case ItemBase::B_LizardTail:
			m_max = 1;
			wcscpy(m_fontPalam.m_text, L"青紋竜の尻尾");
			break;
		case ItemBase::B_LizardHorn:
			m_max = DropMax;
			wcscpy(m_fontPalam.m_text, L"青紋竜の角");
			break;
		case ItemBase::B_LizardFang:
			wcscpy(m_fontPalam.m_text, L"青紋竜の牙");

			m_max = DropMax;
			break;
		case ItemBase::B_LizardScales:
			wcscpy(m_fontPalam.m_text, L"青紋竜の鱗");

			m_max = DropMax;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
}
void Item::Update()
{
	
	auto m_player = Game::instance()->m_player;
	auto m_ItemBase = Game::instance()->m_ItemBase;
	int m_Itemsize;
	wchar_t mark[5] = L"x";
	wchar_t itemNum[3];
	
	if (&m_ghostObject != nullptr) {
		g_physics.ContactTest(m_player->GetcharaCon(), [&](const btCollisionObject & contactObject)
			{
				if (m_ghostObject.IsSelf(contactObject)&&m_player->GetPickFlag())
				{
					m_ItemNum = rand() % m_max + 1;
					_itow_s(m_ItemNum, itemNum, 10);
					wcscat(mark, itemNum);
					wcscat(m_fontPalam.m_text, mark);
					wcscat(m_fontPalam.m_text, m_picktext);
					
					
					m_pickFlag = true;
					m_sound.Stop();
					m_sound.Play(false);
					//Game::instance()->m_UI->PushPickText(m_fontRender);
					m_ItemBase->GetItem(m_type, m_ItemNum);
					m_ghostObject.Release();
					GameObjectManager::instance().DeleteGO(m_skinModelRender);
				}
			}
		);
	}
	
	if (m_pickFlag == true)
	{
		m_fontPalam.pos.y += 4.0f;
		m_fontPalam.m_textColor.Set(CVector4::White());
		m_fontPalam.pivot ={ 0.0f, 0.5f };
		m_fontRender->SetShadowParam(true, 2.0f, CVector4::Black());
		
	}

	if (m_fontPalam.pos.y > LIMIT_Y)
	{
		GameObjectManager::instance().DeleteGO(this);
	}
	if (Game::instance()->GetStageNum() != m_stageNum)
	{
		GameObjectManager::instance().DeleteGO(this);
		GameObjectManager::instance().DeleteGO(m_skinModelRender);
	}
	m_fontRender->SetColor(m_fontPalam.m_textColor);
	m_fontRender->SetPivot(m_fontPalam.pivot);
	m_fontRender->SetText(m_fontPalam.m_text);	
	m_fontRender->SetScale(m_fontPalam.size);
	m_fontRender->SetPosition(m_fontPalam.pos);
}



UI::UI()
{

	for (int i = 0; i < FontType::FontTypeNum; i++)
	{
		m_font[i] = GameObjectManager::instance().NewGO<FontRender>();
	}
	for (int i = 0; i < ItemSpriteTypeNum; i++)
	{
		m_ItemRender[i] = GameObjectManager::instance().NewGO<SpriteRender>();
	}
	for (int i = 0; i < UITypeNum; i++) {
		m_spriteRender[i] = GameObjectManager::instance().NewGO<SpriteRender>();
		//m_spriteSca[i].Set(100.0f, 2.0f, 1.0f);
		m_spriteSca[i].Set(CVector3::One());
		m_spritePos[i].Set(CVector3::One());
		m_spriteRender[i]->SetPivot({ 0.0f,0.5f });
	}
	m_spriteSca[HP].y = 2.0f;
	m_spriteSca[Red].y = 2.0f;
	m_spriteSca[Stamina].y = 2.0f;
	m_spriteSca[Clear].Set(100.0f, 2.0f, 1.0f);
	m_spriteSca[GameOver].Set(100.0f, 2.0f, 1.0f);

	m_Rendertest = GameObjectManager::instance().NewGO<SpriteRender>();
	m_spritePos[HP].Set(-550.0f, 340.0f, 0.0f);
	m_spritePos[Stamina].Set(-550.0f, 300.0f, 0.0f);
	m_spritePos[Red].Set(-550.0f, 340.0f, 0.0f);
	

	m_spriteRender[HP]->Init(L"Assets/sprite/MH_HP.dds",10.0f,10.0f);
	
	m_spriteRender[Stamina]->Init(L"Assets/sprite/MH_stamina.dds", 10.0f, 10.0f);
	m_spriteRender[Clear]->Init(L"Assets/sprite/MH_QUESTCLEAR .dds", 20.0f, 300.0f);
	m_spriteRender[Clear]->SetIsActive(false);
	m_spriteRender[Clear]->SetPivot({ 0.5f,0.5f });

	m_spriteRender[GameOver]->Init(L"Assets/sprite/MH_QUESTFAILED.dds", 20.0f, 300.0f);
	m_spriteRender[GameOver]->SetIsActive(false);
	m_spriteRender[GameOver]->SetPivot({ 0.5f,0.5f });

	m_spriteRender[Red]->Init(L"Assets/sprite/MH_Red.dds", 10.0f, 10.0f);
	m_spriteRender[Red]->SetIsActive(false);

	m_spriteRender[actionLine]->Init(L"Assets/sprite/001_line.dds", 10.0f, 10.0f);
	m_spriteRender[actionLine]->SetPivot({ 0.5f, 0.5f });
	m_spriteSca[actionLine].Set(1.0,1.0f,1.0f);
	m_spriteRender[actionLine]->SetAlpha(0.1f);
	m_spriteRender[actionLine]->SetIsActive(false);

	m_ItemRender[kaihukuyaku]->Init(L"Assets/sprite/HealingBottle02.dds", 80.0f, 80.0f);
	m_ItemRender[kaihukuyaku]->SetPivot({ 0.5f,0.5f });
	m_ItemRender[kaihukuyaku]->SetIsActive(false);
	m_ItemRender[kaihukuyaku]->SetAlpha(1.0f);
	

	m_ItemRender[nonItem]->Init(L"Assets/sprite/NonItem.dds", 80.0f, 80.0f);
	m_ItemRender[nonItem]->SetPivot({ 0.5f,0.5f });
	m_ItemRender[nonItem]->SetIsActive(false);
	m_ItemRender[nonItem]->SetAlpha(1.0f);
	
	m_ItemRender[ItemDummy00]->Init(L"Assets/sprite/001_line.dds", 80.0f, 80.0f);
	m_ItemRender[ItemDummy00]->SetPivot({ 0.5f,0.5f });
	m_ItemRender[ItemDummy00]->SetIsActive(false);
	m_ItemRender[ItemDummy00]->SetAlpha(1.0f);

	m_ItemRender[ItemDummy01]->Init(L"Assets/sprite/icon.dds", 80.0f, 80.0f);
	m_ItemRender[ItemDummy01]->SetPivot({ 0.5f,0.5f });
	m_ItemRender[ItemDummy01]->SetIsActive(false);
	m_ItemRender[ItemDummy01]->SetAlpha(1.0f);

	m_spriteRender[QuestPaper]->Init(L"Assets/sprite/QuestPaper.dds", 40.0f, 60.0f);
	m_spriteRender[QuestPaper]->SetPivot({ 0.5f,0.5f });
	m_spriteSca[QuestPaper].Set(10.0f, 10.0f, 1.0f);
	m_spriteRender[QuestPaper]->SetIsActive(true);

	m_spriteRender[Pause]->Init(L"Assets/sprite/PauseMenu.dds",1280.f, 720.0f);
	m_spriteRender[Pause]->SetIsActive(false);
	m_spritePos[Pause].Set(0.0f, 0.0f, 0.0f);
	m_spriteRender[Pause]->SetPivot({ 0.5f, 0.5f });

	m_spriteRender[ReturnCamp]->Init(L"Assets/sprite/Return toCamp.dds", 600.0f, 50.0f);
	m_spriteRender[ReturnCamp]->SetIsActive(false);
	m_spritePos[ReturnCamp].Set(400.0f, -300.0f, 0.0f);
	m_spriteRender[ReturnCamp]->SetPivot({ 0.5f, 0.5f });

	m_spriteRender[OrdersQuest]->Init(L"Assets/sprite/OrdersQuest.dds", 400.0f, 400.0f);
	m_spriteRender[OrdersQuest]->SetIsActive(true);
	m_spritePos[OrdersQuest].Set(0.0f, 0.0f, 0.0f);
	m_spriteRender[OrdersQuest]->SetPivot({ 0.5f, 0.5f });
	m_spriteRender[OrdersQuest]->SetAlpha(1.0f);

	m_spriteRender[Result]->Init(L"Assets/sprite/Result.dds", 1280.0f, 720.0f);
	m_spriteRender[Result]->SetIsActive(false);
	m_spritePos[Result].Set(0.0f, 0.0f, 0.0f);
	m_spriteRender[Result]->SetPivot({ 0.5f, 0.5f });

	m_spriteRender[ItemNext]->Init(L"Assets/sprite/ItemNextIcon.dds", 150.0f, 100.0f);
	m_spriteRender[ItemNext]->SetIsActive(false);
	m_spritePos[ItemNext].Set(0.0f, 0.0f, 0.0f);
	m_spriteRender[ItemNext]->SetPivot({ 0.5f, 0.5f });


	for (int i = FrameIcon00; i <= FrameIcon08; i++) {
		auto m_iconNum = i - 10;

		
		m_spriteRender[i]->Init(L"Assets/sprite/icon.dds", 600.0f, 300.0f);
		m_spriteSca[i].Set(0.3f, 0.3f, 0.2f);
		if (m_iconNum < 4) {
			m_spritePos[i].Set(-400.0f, 50.0f - m_iconNum * 80.0f, 0.0f);
		}
		else
		{
			m_spritePos[i].Set(-100.0f, 290.0f - m_iconNum * 60.0f, 0.0f);
			m_spriteSca[i].x = 0.45f;
		}
		m_spriteRender[i]->SetPivot({ 0.5f, 0.5f });
		m_spriteRender[i]->SetIsActive(false);
	}
	m_spriteRender[TargetMark]->Init(L"Assets/sprite/Triangle.dds",100.0f,100.0f);
	m_spritePos[TargetMark].Set(-660.0f, 0.0f, 0.0f);
	m_spriteRender[TargetMark]->SetIsActive(false);

	m_spriteRender[ManeyPouch]->Init(L"Assets/sprite/moneyPouch.dds", 300.0f, 100.0f);
	m_spritePos[ManeyPouch].Set( -640.0f, -300.0f,-0.0f );
	m_spriteRender[ManeyPouch]->SetIsActive(false);
	/*m_spriteRender[FrameIcon01]->Init(L"Assets/sprite/icon.dds", 600.0f, 300.0f);
	m_spriteRender[FrameIcon02]->Init(L"Assets/sprite/icon.dds", 600.0f, 300.0f);
	m_spriteRender[FrameIcon03]->Init(L"Assets/sprite/icon.dds", 600.0f, 300.0f);
	m_spriteRender[FrameIcon04]->Init(L"Assets/sprite/icon.dds", 600.0f, 300.0f);*/


	m_Rendertest->Init(L"Assets/sprite/icon.dds", 600.0f,300.0f);
	m_Rendertest->SetAlpha(1.0f);
	m_Rendertest->SetIsActive(false);
	m_Rendertest->SetPivot({ 0.5f, 0.5f });
	//SpriteRender *m_set = m_spriteRender[nonItem];

	AttackEvent = false;
	m_sound[Select].Init(L"Assets/sound/cursor2.wav");
}


UI::~UI()
{
	for (int i = 0; i < UITypeNum; i++) {
		GameObjectManager::instance().DeleteGO(m_spriteRender[i]);
	}
	for (int i = 0; i < ItemSpriteTypeNum; i++)
	{
		GameObjectManager::instance().DeleteGO(m_ItemRender[i]);
	}
	for (int i = 0; i < FontTypeNum; i++)
	{
		GameObjectManager::instance().DeleteGO(m_font[i]);
	}
}

int UI::CheckItem()
{

	auto m_Item = Game::instance()->m_ItemBase;
	nonhaveItem = 0;
	haveItemNum = 0;
	
	for (int i = 0; i < ItemBase::ItemType::TypeNum; i++)
	{
		if (m_Item->GetData(i).isUse == ItemBase::IsUse::User_Item) {
			if (m_Item->GetData(i).num > 0)
			{
			
				haveItemNum++;
				lastItem = i;
				m_ItemList.push_back(i);
			}
			else {
				nonhaveItem++;
			}
		}
		else if (m_Item->GetData(i).isUse == ItemBase::IsUse::Drop_Item)
		{
			if (m_Item->GetData(i).num > 0)
			{
				m_DropItemList.push_back(i);
			}
		}
	}
	
	lastItem = m_ItemList.size()-1;
	return haveItemNum;
}
void UI::ChangeItem()
{
	auto ItemNum =CheckItem();
	auto m_game = Game::instance();
	if (!m_game->GetPauseFlag())
	{
		if (ItemNum >= 3) {

			if (g_pad[0].IsPress(enButtonLB1))
			{
				if (g_pad[0].IsTrigger(enButtonX))
				{
					if (mainItem - 1 >= 0)
					{
						mainItem--;

					}
					else mainItem = lastItem;
				}
				else if (g_pad[0].IsTrigger(enButtonB))
				{
					if (mainItem + 1 < m_ItemList.size())
					{
						mainItem++;
					}
					else mainItem = 0;
				}
			}
			if (lastItem < mainItem)
			{
				mainItem = nonItem;
			}
			targetItem = m_ItemList[mainItem];
			m_ItemRender[targetItem]->SetIsActive(true);
			m_ItemRender[targetItem]->SetPosition(m_mainItemPos);
			m_ItemRender[targetItem]->SetScale(m_mainItemSca);
			if (mainItem - 1 < 0)
			{
				m_ItemRender[m_ItemList[lastItem]]->SetIsActive(true);
				m_ItemRender[m_ItemList[lastItem]]->SetPosition(m_backItemPos);
				m_ItemRender[m_ItemList[lastItem]]->SetScale(m_sideItemSca);
			}
			else {
				m_ItemRender[m_ItemList[mainItem - 1]]->SetIsActive(true);
				m_ItemRender[m_ItemList[mainItem - 1]]->SetPosition(m_backItemPos);
				m_ItemRender[m_ItemList[mainItem - 1]]->SetScale(m_sideItemSca);
			}
			if (mainItem + 1 >= m_ItemList.size())
			{
				m_ItemRender[nonItem]->SetIsActive(true);
				m_ItemRender[nonItem]->SetPosition(m_nextItemPos);
				m_ItemRender[nonItem]->SetScale(m_sideItemSca);
			}
			else {
				m_ItemRender[m_ItemList[mainItem + 1]]->SetIsActive(true);
				m_ItemRender[m_ItemList[mainItem + 1]]->SetPosition(m_nextItemPos);
				m_ItemRender[m_ItemList[mainItem + 1]]->SetScale(m_sideItemSca);
			}
		}
		else if (ItemNum == 2)
		{

			if (g_pad[0].IsPress(enButtonLB1))
			{
				if (g_pad[0].IsTrigger(enButtonX))
				{
					if (mainItem - 1 >= 0)
					{
						mainItem--;

					}
					else mainItem++;
				}
				else if (g_pad[0].IsTrigger(enButtonB))
				{
					if (mainItem + 1 < m_ItemList.size())
					{
						mainItem++;
					}
					else mainItem = 0;
				}
			}
			if (lastItem < mainItem)
			{
				mainItem = nonItem;
			}
			targetItem = m_ItemList[mainItem];
			m_ItemRender[targetItem]->SetIsActive(true);
			m_ItemRender[targetItem]->SetPosition(m_mainItemPos);
			m_ItemRender[targetItem]->SetScale(m_mainItemSca);




			if (mainItem - 1 < 0)
			{

				m_ItemRender[m_ItemList[targetItem + 1]]->SetIsActive(true);
				m_ItemRender[m_ItemList[targetItem + 1]]->SetPosition(m_nextItemPos);
				m_ItemRender[m_ItemList[targetItem + 1]]->SetScale(m_sideItemSca);


			}
			else {

				m_ItemRender[m_ItemList[mainItem - 1]]->SetIsActive(true);
				m_ItemRender[m_ItemList[mainItem - 1]]->SetPosition(m_nextItemPos);
				m_ItemRender[m_ItemList[mainItem - 1]]->SetScale(m_sideItemSca);


			}

		}
		else if (ItemNum == 1)
		{
			targetItem = m_ItemList[nonItem];
			m_ItemRender[nonItem]->SetIsActive(true);
			m_ItemRender[nonItem]->SetPosition(m_mainItemPos);
			m_ItemRender[nonItem]->SetScale(m_mainItemSca);
		}
	}

	
	if (m_game->GetPauseFlag())
	{
		if (MenuStageNum == 1) {

			if (g_pad[0].IsTrigger(enButtonDown))
			{
				if (p_target == DropItemPouch) {
					if (DropTarget < m_DropItemList.size() - 1)
					{
						DropTarget++;
						m_sound[Select].Stop();
						m_sound[Select].Play(false);
					}

				}
				if (p_target == UserItemPouch) {
					if (UserTarget < m_ItemList.size() - 1)
					{
						UserTarget++;
						m_sound[Select].Stop();
						m_sound[Select].Play(false);
					}

				}
			}
			if (g_pad[0].IsTrigger(enButtonUp))
			{
				if (p_target == DropItemPouch) {
					if (DropTarget > 0)
					{
						DropTarget--;
						m_sound[Select].Stop();
						m_sound[Select].Play(false);
					}
				}
				if (p_target == UserItemPouch) {
					if (UserTarget > 1)
					{
						UserTarget--;
						m_sound[Select].Stop();
						m_sound[Select].Play(false);
					}
				}
			}

			if (p_target == UserItemPouch)
			{
				if (m_ItemList.size() <= 5) {

					for (int i = 0; i < m_ItemList.size(); i++) {
						if (UserTarget + i < m_ItemList.size()) {
							u_target[i] = m_ItemList[UserTarget + i];
						}
						else u_target[i] = m_ItemList[m_ItemList.size() - 1 - i];
					}
				}
				else
				{
					u_target[0] = m_ItemList[UserTarget];

					for (int i = 1; i < 5; i++) {


						if (UserTarget + i < 5) {
							u_target[i] = m_ItemList[UserTarget + i];

						}
						else
						{
							u_target[i] = m_ItemList[4 - i];
							if (UserTarget > 4)
							{
								u_target[i] = m_ItemList[UserTarget - i];
							}

						}
					}
				}
			}
			if (p_target == DropItemPouch) {
				if (m_DropItemList.size() <= 5) {

					for (int i = 0; i < m_DropItemList.size(); i++) {
						if (DropTarget + i < m_DropItemList.size()) {
							d_target[i] = m_DropItemList[DropTarget + i];
						}
						else d_target[i] = m_DropItemList[m_DropItemList.size() - 1 - i];
					}

					
				}
				else
				{

					d_target[0] = m_DropItemList[DropTarget];

					for (int i = 1; i < 5; i++) {


						if (DropTarget + i < 5) {
							d_target[i] = m_DropItemList[DropTarget + i];

						}
						else
						{
							d_target[i] = m_DropItemList[4 - i];
							if (DropTarget > 4)
							{
								d_target[i] = m_DropItemList[DropTarget - i];
							}
							

						}
					}
				}
			}
			


		}
		else if (MenuStageNum == 0)
		{
			DropTarget = 0;
		}

	}
	
}
void UI::PushPickText(FontRender* fontRender)
{
	
	m_dropFontlist.push_back(fontRender);
	/*typedef ItemBase::ItemType Type;
	switch (m_pickTextParts.pickItemType)
	{
	case Type::Herbs:
		break;
	case Type::mushroom:
		break;
	default:
		break;
	}*/


}
void UI::SetFont(int ft, wchar_t text[15],bool frameflag, float frame, CVector4 & color, CVector2 & pos, float size, CVector2 & pivot)
{
	
		m_font[ft]->SetText(text);
		m_font[ft]->SetPivot(pivot);
		m_font[ft]->SetShadowParam(frameflag, frame, CVector4::Black());
		m_font[ft]->SetColor(color);
		m_font[ft]->SetPosition(pos);
		m_font[ft]->SetScale(size);
	
}
void UI::SetFontPalam()
{
	
	auto m_game = Game::instance();
	auto m_Item = Game::instance()->m_ItemBase;
	auto m_quest = Game::instance()->m_quest;
	auto m_queboardInfo = m_quest->GetDispInfo();
	auto m_queInfo = m_quest->GetQuestInfo();
	int itemnum = m_Item->GetData(targetItem).num;
	int d_itemnum = m_Item->GetData(d_target[0]).num;
	_itow_s(itemnum, m_fontPalam[ItemNumber].m_text, 10);
	m_fontPalam[ItemNumber].m_frameWidth = 3.0f;
	m_fontPalam[ItemNumber].pos = { 350.0f,-230.0f };
	m_fontPalam[ItemNumber].size = 0.7f;
	m_fontPalam[ItemNumber].pivot = { 0.5f,0.5f };


	m_fontPalam[GoalNum].size = 0.6f;
	m_fontPalam[QuestPoint].size = 0.6f;
	m_fontPalam[QuestName].size = 0.6f;
	m_fontPalam[QuestSummary].size = 0.6f;
	m_fontPalam[PrizeMoney].size = 0.6f;
	m_fontPalam[RequesterName].size = 0.6f;
	m_fontPalam[DropItemNumber].size = 0.6f;
	for (int i = ItemName00; i <= ItemName04; i++)
	{
		m_fontPalam[i].size = 0.6f;
	}
	m_fontPalam[ItemSummry].size = 0.6f;
	m_fontPalam[HaveMoney].size = 1.0f;
	m_fontPalam[U_Pouch].size = 0.6f;
	m_fontPalam[D_Pouch].size = 0.6f;
	m_fontPalam[m_help].size = 0.6f;
	m_fontPalam[m_exit].size = 0.6f;

	if (targetItem != nonItem) {
		m_fontPalam[ItemNumber].m_textColor = CVector4::White();
	}
	else m_fontPalam[ItemNumber].m_textColor = { 0.0f,0.0f, 0.0f, 0.0f };



	if (MenuFlag[DropItemPouch]) {
		for (int i = 0; i <= m_DropItemList.size(); i++) {

			switch (d_target[i])
			{
			case(ItemBase::Herbs):

				wcscpy(m_fontPalam[ItemName00 + i].m_text, L"薬草");
				if (i == 0)
					wcscpy(m_fontPalam[ItemSummry].m_text, L"フィールド広域で採取できる草。\n");
				break;
			case(ItemBase::PoisonouMushroom):
				wcscpy(m_fontPalam[ItemName00 + i].m_text, L"毒茸");
				if (i == 0)
					wcscpy(m_fontPalam[ItemSummry].m_text, L"毒を含むキノコ。\n");

				break;
			case(ItemBase::mushroom):
				wcscpy(m_fontPalam[ItemName00 + i].m_text, L"大茸");
				if (i == 0)
					wcscpy(m_fontPalam[ItemSummry].m_text, L"大きな美味しいキノコ。\n");

				break;
			case(ItemBase::Treenut):
				wcscpy(m_fontPalam[ItemName00 + i].m_text, L"木の実");
				if (i == 0)
					wcscpy(m_fontPalam[ItemSummry].m_text, L"。\n");

				break;
			case(ItemBase::smallstone):
				wcscpy(m_fontPalam[ItemName00 + i].m_text, L"小石");
				if (i == 0)
				{
					wcscpy(m_fontPalam[ItemSummry].m_text, L"ただの小石。\n");
				}
				break;
			case(ItemBase::B_L_LizardTail):
				wcscpy(m_fontPalam[ItemName00 + i].m_text, L"青紋小竜の尻尾");
				if (i == 0)
					wcscpy(m_fontPalam[ItemSummry].m_text, L"砂漠地帯に生息する青紋小竜の尻尾。\n切れてもまた生えてくる。");

				break;
			case(ItemBase::B_L_LizardClaw):
				wcscpy(m_fontPalam[ItemName00 + i].m_text, L"青紋小竜の爪");
				if (i == 0)
				{
					wcscpy(m_fontPalam[ItemSummry].m_text, L"砂漠地帯に生息する青紋小竜の爪。\n獲物の肉に食い込む強靭な爪。");
				}
				break;
			case(ItemBase::B_L_LizardScales):
				wcscpy(m_fontPalam[ItemName00 + i].m_text, L"青紋小竜の鱗");
				if (i == 0)
				{
					wcscpy(m_fontPalam[ItemSummry].m_text, L"砂漠地帯に生息する青紋小竜の鱗。\n薄く軽いわりに硬くて丈夫。");
				}
				break;
			case(ItemBase::B_L_LizardFang):
				wcscpy(m_fontPalam[ItemName00 + i].m_text, L"青紋小竜の牙");
				if (i == 0)
				{
					wcscpy(m_fontPalam[ItemSummry].m_text, L"砂漠地帯に生息する青紋小竜の牙。\n獲物をかみ切る強靭な牙。");
				}
				break;

			case(ItemBase::B_LizardTail):
				wcscpy(m_fontPalam[ItemName00 + i].m_text, L"青紋竜の尻尾");
				if (i == 0)
				{
					wcscpy(m_fontPalam[ItemSummry].m_text, L"砂漠地帯を支配する青紋竜の尻尾。");
				}
				break;
			case(ItemBase::B_LizardFang):
				wcscpy(m_fontPalam[ItemName00 + i].m_text, L"青紋竜の牙");
				if (i == 0)
				{
					wcscpy(m_fontPalam[ItemSummry].m_text, L"砂漠地帯を支配する青紋竜の牙。");
				}
				
				break;
			case(ItemBase::B_LizardHorn):
				wcscpy(m_fontPalam[ItemName00 + i].m_text, L"青紋竜の角");
				if (i == 0)
				{
					wcscpy(m_fontPalam[ItemSummry].m_text, L"砂漠地帯を支配する青紋竜の角。");
				}

				break;
			case(ItemBase::B_LizardScales):
				wcscpy(m_fontPalam[ItemName00 + i].m_text, L"青紋竜の鱗");
				if (i == 0)
				{
					wcscpy(m_fontPalam[ItemSummry].m_text, L"砂漠地帯を支配する青紋竜の鱗。");
				}

				break;
			default:
				if (i == 0)
				{
					wcscpy(m_fontPalam[ItemSummry].m_text, L"アイテム未所持");
				}
				break;
			}

		}
	}
	if (p_target == UserItemPouch)
	{
		for(int i =0;i<m_ItemList.size();i++)
		switch (u_target[i])
		{
		case(kaihukuyaku):
			wcscpy(m_fontPalam[ItemName00 + i].m_text, L"回復薬");
			if (i == 0)
			{
				wcscpy(m_fontPalam[ItemSummry].m_text, L"回復薬");
			}
			break;
		case(ItemDummy00):
			wcscpy(m_fontPalam[ItemName00 + i].m_text, L"鬼神薬");
			if (i == 0)
			{
				wcscpy(m_fontPalam[ItemSummry].m_text, L"鬼神薬");
			}
			break;
		case(ItemDummy01):
			wcscpy(m_fontPalam[ItemName00 + i].m_text, L"薬");
			if (i == 0)
			{
				wcscpy(m_fontPalam[ItemSummry].m_text, L"薬");
			}
			break;
		default:
			break;
		}
	}
	
	int m_prizemoney = m_queInfo.m_prizeMoney;
	int goalnum = m_queInfo.m_targetNum;
	int targetnum = m_quest->GetQuestPoint();

	int m_havemoney = m_quest->GetMoney();
	
	wchar_t m_prizetext[255];
	wchar_t m_itemnum[255];



	wcscpy(m_fontPalam[QuestName].m_text, m_queInfo.m_questName);
	wcscpy(m_fontPalam[QuestSummary].m_text, m_queInfo.m_questSummry);
	//wcscpy(m_fontPalam[HaveMoney].m_text, L"所持金　");
	wcscpy(m_fontPalam[PrizeMoney].m_text, L"報酬金\n");
	wcscpy(m_fontPalam[U_Pouch].m_text, L"道具");
	wcscpy(m_fontPalam[D_Pouch].m_text, L"素材");
	wcscpy(m_fontPalam[DropItemNumber].m_text, L"所持数");
	wcscpy(m_fontPalam[m_exit].m_text, L"ゲーム終了");
	wcscpy(m_fontPalam[m_help].m_text, L"操作説明");

	_itow_s(m_prizemoney, m_prizetext, 10);
	_itow_s(d_itemnum, m_itemnum, 10);
	_itow_s(goalnum, m_fontPalam[GoalNum].m_text, 10);
	_itow_s(targetnum, m_fontPalam[QuestPoint].m_text, 10);
	_itow_s(m_havemoney, m_fontPalam[HaveMoney].m_text, 10);
	wcscat(m_fontPalam[QuestPoint].m_text, L"/");
	//wcscat(m_fontPalam[HaveMoney].m_text, m_moneytext);
	wcscat(m_fontPalam[PrizeMoney].m_text, m_prizetext);
	wcscat(m_fontPalam[DropItemNumber].m_text, m_itemnum);
	/// <summary>
	/// 一時停止画面中
	/// </summary>
	if (m_game->GetPauseFlag())
	{

		
		

		

		m_fontPalam[QuestName].pivot = { 0.0f,0.5f };
		m_fontPalam[QuestSummary].pivot = { 0.0f,0.5f };
		m_fontPalam[PrizeMoney].pivot = { 0.0f,0.5f };
		m_fontPalam[RequesterName].pivot = { 0.0f,0.5f };
		m_fontPalam[GoalNum].pivot = { 0.0f,0.5f };
		m_fontPalam[QuestPoint].pivot = { 0.0f,0.5f }; 
		m_fontPalam[HaveMoney].pivot = { 0.0f,0.5f };
		m_fontPalam[DropItemNumber].pivot = { 0.5f,0.5f };
		m_fontPalam[ItemSummry].pivot = { 0.0f,0.5f };


		m_fontPalam[QuestName].pos = { -600.0f,220.0f };
		m_fontPalam[QuestSummary].pos = { -600.0f,190.0f };
		m_fontPalam[GoalNum].pos = { -560.0f,162.0f };
		m_fontPalam[QuestPoint].pos = { -600.0f,160.0f };
		m_fontPalam[PrizeMoney].pos = { -600.0f,130.0f };
		m_fontPalam[HaveMoney].pos = { -470.0f,-300.0f };
		m_fontPalam[DropItemNumber].pos = { 300.0f,-200.0f };
		m_fontPalam[ItemSummry].pos = { 150.0f,50.0f };

		//m_fontPalam[DropItemNumber].m_textColor = CVector4::White();
		//m_fontPalam[ItemName00].m_textColor = CVector4::White();
		m_fontPalam[QuestName].m_textColor = CVector4::White();
		m_fontPalam[QuestSummary].m_textColor = CVector4::White();
		m_fontPalam[PrizeMoney].m_textColor = CVector4::White();
		m_fontPalam[GoalNum].m_textColor = CVector4::White();
		m_fontPalam[QuestPoint].m_textColor = CVector4::White();
		m_fontPalam[HaveMoney].m_textColor = CVector4::White();
		m_fontPalam[U_Pouch].m_textColor = CVector4::White();
		m_fontPalam[D_Pouch].m_textColor = CVector4::White();
		m_fontPalam[m_help].m_textColor = CVector4::White();
		m_fontPalam[m_exit].m_textColor = CVector4::White();

		/// <summary>
		/// かつクエストを受けていない時
		/// </summary>
		if (!m_quest->IsOnQuest())
		{
			m_fontPalam[QuestPoint].m_textColor = { 0.0f,0.0f,0.0f,0.0f };
			m_fontPalam[GoalNum].m_textColor = { 0.0f,0.0f,0.0f,0.0f };
			wcscpy(m_fontPalam[QuestName].m_text, L"クエスト未受注");
			m_fontPalam[QuestName].size = 1.0f;
			m_fontPalam[QuestPoint].m_textColor = { 0.0f,0.0f,0.0f,0.0f };
			//m_fontPalam[QuestName].m_textColor = { 0.0f,0.0f,0.0f,0.0f };
			m_fontPalam[QuestSummary].m_textColor = { 0.0f,0.0f,0.0f,0.0f };
			m_fontPalam[PrizeMoney].m_textColor = { 0.0f,0.0f,0.0f,0.0f };

		}

		/// <summary>
		/// かつMenuの段階が０の時
		/// </summary>
		if (MenuStageNum == 0)
		{
			for (int i = ItemNumber; i <= ItemSummry; i++)
			{
				m_fontPalam[i].m_textColor.Set({ 0.0f,0.0f,0.0f,0.0f });
			}
		}
		/// /// <summary>
		/// かつ素材ポーチを見ているまたはアイテムポーチを見ている時
		/// </summary>
		if (MenuFlag[DropItemPouch]|| MenuFlag[UserItemPouch])
		{
			if (MenuStageNum == 1) {
				for (int i = ItemName00; i <= ItemName04; i++) {
					auto IconNum = i - ItemName00;

					if (p_target == 0 && IconNum < m_ItemList.size() - 1)
					{
						m_fontPalam[i].m_textColor.Set(CVector4::White());
					}
					if (p_target ==1&&IconNum < m_DropItemList.size()) {
						m_fontPalam[i].m_textColor.Set(CVector4::White());
					}
					
				}

				
			}
			if (MenuStageNum >= 1)
			{
				m_fontPalam[ItemSummry].m_textColor.Set(CVector4::White());

				if (p_target == 0 && m_ItemList.size() > 0)
				{
					m_fontPalam[ItemNumber].m_textColor.Set(CVector4::White());

				}
				if (p_target ==1 &&m_DropItemList.size() > 0) {
					m_fontPalam[DropItemNumber].m_textColor.Set(CVector4::White());
				}
				
			}
			else
			{
				m_fontPalam[ItemSummry].m_textColor.Set({ 0.0f,0.0f,0.0f,0.0f });
				m_fontPalam[DropItemNumber].m_textColor.Set({ 0.0f,0.0f,0.0f,0.0f });
			}

		}
		

	}
	else
	{
		
		
		for (int i=0; i < FontType::FontTypeNum; i++)
		{
			if (i != ItemNumber) {
				m_fontPalam[i].m_textColor = { 0.0f,0.0f,0.0f,0.0f };
			}
		}
		
	}
	/// <summary>
	/// クエストボードを見ている
	/// </summary>
	if (m_game->IsLookBoard())
	{
		m_fontPalam[QuestName].m_textColor = CVector4::Black();
		wcscpy(m_fontPalam[QuestName].m_text,m_queboardInfo.m_questName);
		m_fontPalam[QuestName].pivot ={ 0.5f,0.5f };
		m_fontPalam[QuestName].pos = { 0.0f,170.0f };
		

		m_fontPalam[QuestSummary].m_textColor = CVector4::Black();
		wcscpy(m_fontPalam[QuestSummary].m_text,m_queboardInfo.m_questSummry);
		m_fontPalam[QuestSummary].pivot = { 0.5f,0.5f };
		m_fontPalam[QuestSummary].pos = { 0.0f,50.0f };

		int money = m_queboardInfo.m_prizeMoney;
		
		m_fontPalam[PrizeMoney].m_textColor = CVector4::Black();
		_itow_s(money, m_fontPalam[PrizeMoney].m_text, 10);
		m_fontPalam[PrizeMoney].pivot = { 0.5f,0.5f };
		m_fontPalam[PrizeMoney].pos = { 0.0f,-120.0f };

		m_fontPalam[RequesterName].m_textColor = CVector4::Black();
		wcscpy(m_fontPalam[RequesterName].m_text, m_queboardInfo.m_requesterName);
		m_fontPalam[RequesterName].pivot = { 0.5f,0.5f };
		m_fontPalam[RequesterName].pos = { 0.0f,-200.0f };
	}
	else {
		m_fontPalam[QuestName].m_textColor.w = 0.0f;
		m_fontPalam[QuestSummary].m_textColor.w = 0.0f;
		m_fontPalam[PrizeMoney].m_textColor.w = 0.0f;
		m_fontPalam[RequesterName].m_textColor.w = 0.0f;
	}
	/// <summary>
	/// リザルト画面中
	/// </summary>
	if (ResultFlag)
	{

		

		if (m_spriteAlpha[Result] >= 1.0f)
		{
			
			if ( !m_quest->GetPrizeMoney()&&g_pad[0].IsPressAnyKey())
			{
				m_endqestFlag = true;
			}
			m_fontPalam[HaveMoney].m_textColor.Set(CVector4::White());
			m_fontPalam[HaveMoney].m_frameWidth = 3.0f;
			m_fontPalam[HaveMoney].frameFlag = true;
			m_fontPalam[HaveMoney].size = 2.0f;
			m_fontPalam[HaveMoney].pos = { -200.0f,-200.0f };
			m_fontPalam[HaveMoney].pivot = { 0.9f,0.5f };
			m_fontPalam[PrizeMoney].m_textColor.Set(1.0f, 1.0f, 1.0f, 1.0f);
			m_fontPalam[PrizeMoney].size = 2.0f;
			m_fontPalam[PrizeMoney].pos = { -400.0f,100.0f };
			//m_fontPalam[PrizeMoney].pivot = { 1.0f,0.5f };
			m_fontPalam[PrizeMoney].frameFlag = true;
			m_spriteRender[ManeyPouch]->SetIsActive(true);
			m_spriteRender[ManeyPouch]->SetPivot({ 0.75f, 0.5f });
			m_spritePos[ManeyPouch].Set(
				m_fontPalam[HaveMoney].pos.x,
				m_fontPalam[HaveMoney].pos.y,
				0.0f
			);
			m_spriteSca[ManeyPouch].Set(2.0f, 2.0f, 1.0f);
			
		}

	}
	else {


	}
	
	
	for (int i = 0; i < FontTypeNum; i++)
	{
		if (m_fontPalam[i].m_frameWidth > 0.0f)
		{
			m_fontPalam[i].frameFlag = true;
		}
		if (targetItem == nonItem)
		{
			m_fontPalam[ItemNumber].frameFlag = false;
		}
		SetFont(i, m_fontPalam[i].m_text,
			m_fontPalam[i].frameFlag,
			m_fontPalam[i].m_frameWidth,
			m_fontPalam[i].m_textColor,
			m_fontPalam[i].pos,
			m_fontPalam[i].size,
			m_fontPalam[i].pivot
		);

	}

	
	ResetList();
	
}
void UI::ClearDraw()
{

	
	if (!ResultFlag) {
		m_spriteRender[Clear]->SetIsActive(true);
		m_spriteRender[Clear]->SetAlpha(m_spriteAlpha[Clear]);
		if (m_spriteAlpha[Clear] < 1.0f) {
			m_spriteAlpha[Clear] += 0.02f;
		}
		
	}
	else
	{
		if (m_spriteAlpha[Result] < 1.0f) {
			m_spriteAlpha[Result] += 0.02f;
		}
	}
	if (g_pad[0].IsTrigger(enButtonStart))
	{
		m_spriteAlpha[Clear] = 0;
		m_spriteRender[Result]->SetIsActive(true);
		ResultFlag = true;
		m_spriteRender[Clear]->SetIsActive(false);
	}
	m_spriteRender[Result]->SetAlpha(m_spriteAlpha[Result]);
}

void UI::GameOverDraw()
{
	if (m_spriteAlpha[GameOver] < 1.0f) {
		m_spriteAlpha[GameOver] += 0.02f;
	}
	m_spriteRender[GameOver]->SetIsActive(true);
	m_spriteRender[GameOver]->SetAlpha(m_spriteAlpha[GameOver]);
}

void UI::PauseMenu()
{
	auto m_game = Game::instance();
	
	if (m_game->GetPauseFlag()) {
		
		for (int i = FrameIcon00; i <= FrameIcon03; i++)
		{
			auto FontNum = i - 10;
			FontNum += U_Pouch;
			m_spriteRender[i]->SetIsActive(true);
			m_fontPalam[FontNum].pos = m_spriteRender[i]->Get2DPosition();

		}
		if (MenuStageNum >= 1) {
			for (int i = FrameIcon04; i <= FrameIcon08; i++)
			{
				auto framenum = i - 14;
				if (p_target == 0) {
					if (framenum < m_ItemList.size()-1)
					{
						m_spriteRender[i]->SetIsActive(true);
					}
				}
				if (p_target == 1) {
					if (framenum < m_DropItemList.size())
					{
						m_spriteRender[i]->SetIsActive(true);
					}
				}

			}
		}
		else
		{
			for (int i = FrameIcon04; i <= FrameIcon08; i++)
			{
				m_spriteRender[i]->SetIsActive(false);
			}
		}
		m_spriteRender[Pause]->SetIsActive(true);
		m_spriteRender[ReturnCamp]->SetIsActive(true);
		m_spriteRender[TargetMark]->SetIsActive(true);
		m_spriteRender[ManeyPouch]->SetIsActive(true);

		auto m_Dsize = m_DropItemList.size();
		auto m_Usize = m_ItemList.size()-1;

		if (p_target == UserItemPouch)
		{
			sizeTag = (int)m_Usize;
		}
		if (p_target == DropItemPouch) {
			sizeTag = (int)m_Dsize;
		}
		if (sizeTag > 5)
		{
			sizeTag = 5;
		}
		switch (MenuStageNum)
		{
			/// <summary>
			/// メニューが０段階目の時
			/// </summary>
		case 0:

			m_spritePos[TargetMark].x = -660.0f;
			m_spriteRender[ItemNext]->SetIsActive(false);

			if (g_pad[0].IsTrigger(enButtonDown))
			{

				if (p_target != 3)
				{
					p_target++;
					m_sound[Select].Stop();
					m_sound[Select].Play(false);
				}
			}
			if (g_pad[0].IsTrigger(enButtonUp))
			{

				if (p_target != 0) {

					p_target--;
					m_sound[Select].Stop();
					m_sound[Select].Play(false);
				}
			}

			switch (p_target)
			{
			case 0:
				m_spritePos[TargetMark].y = m_spriteRender[FrameIcon00]->Get2DPosition().y;
				m_fontPalam[U_Pouch].m_textColor.Set(0.0f, 0.5f, 0.5f, 1.0f);
				if (m_spritePos[TargetMark].x + 250.0f < m_spriteRender[FrameIcon00]->Get2DPosition().x)
				{
					m_spritePos[FrameIcon00].x -= 50.0f;
					m_spriteSca[FrameIcon00] *= 1.5f;
				}

				break;
			case 1:
				m_spritePos[TargetMark].y = m_spriteRender[FrameIcon01]->Get2DPosition().y;
				m_fontPalam[D_Pouch].m_textColor.Set(0.0f, 0.5f, 0.5f, 1.0f);
				if (m_spritePos[TargetMark].x + 250.0f < m_spriteRender[FrameIcon01]->Get2DPosition().x)
				{
					m_spritePos[FrameIcon01].x -= 50.0f;
					m_spriteSca[FrameIcon01] *= 1.5f;

				}

				break;
			case 2:
				m_spritePos[TargetMark].y = m_spriteRender[FrameIcon02]->Get2DPosition().y;
				if (m_spritePos[TargetMark].x + 250.0f < m_spriteRender[FrameIcon02]->Get2DPosition().x)
				{
					m_spritePos[FrameIcon02].x -= 50.0f;
					m_spriteSca[FrameIcon02] *= 1.5f;

				}
				break;
			case 3:
				m_spritePos[TargetMark].y = m_spriteRender[FrameIcon03]->Get2DPosition().y;
				if (m_spritePos[TargetMark].x + 250.0f < m_spriteRender[FrameIcon03]->Get2DPosition().x)
				{
					m_spritePos[FrameIcon03].x -= 50.0f;
					m_spriteSca[FrameIcon03] *= 1.5f;

				}
				break;
			default:
				break;
			}
			break;
			/// <summary>
			/// メニューが１段階目の時
			/// </summary>
		case 1:
			m_spritePos[ItemNext].x = m_spriteRender[FrameIcon08]->Get2DPosition().x;
			m_spritePos[ItemNext].y = m_spriteRender[FrameIcon08]->Get2DPosition().y - 100.0f;

			/// <summary>
			/// アイテムポーチを選択中
			/// </summary>
			if (p_target == 0)
			{
				if(m_ItemList.size()-1>5&&UserTarget != m_ItemList.size() - 2)
				{
					m_spriteRender[ItemNext]->SetIsActive(true);
				}
				else m_spriteRender[ItemNext]->SetIsActive(false);


				switch (UserTarget)
				{


				case 1:
					m_spritePos[TargetMark].y = m_spriteRender[FrameIcon04]->Get2DPosition().y;
					m_fontPalam[ItemName00].pos = m_spriteRender[FrameIcon04]->Get2DPosition();
					for (int i = 1; i < 5; i++)
					{
						auto fontNum = i + ItemName00;
						auto IconNum = i + FrameIcon04;
						if (m_spriteRender[IconNum]->IsRender()) {
							m_fontPalam[fontNum].pos = m_spriteRender[IconNum]->Get2DPosition();
							//_itow_s(fontNum, m_fontPalam[fontNum].m_text, 10);
							//m_fontPalam[fontNum].m_textColor.Set(CVector4::White());
						}
						else m_fontPalam[fontNum].m_textColor.Set(0.0f, 0.0f, 0.0f, 0.0f);
					}
					break;
				case 2:
					m_spritePos[TargetMark].y = m_spriteRender[FrameIcon05]->Get2DPosition().y;
					m_fontPalam[ItemName00].pos = m_spriteRender[FrameIcon05]->Get2DPosition();
					m_fontPalam[ItemName00 + sizeTag - 1].pos = m_spriteRender[FrameIcon04]->Get2DPosition();

					for (int i = 1; i < 4; i++)
					{
						auto fontNum = i + ItemName00;
						auto IconNum = i + FrameIcon05;
						if (m_spriteRender[IconNum]->IsRender()) {

							m_fontPalam[fontNum].pos = m_spriteRender[IconNum]->Get2DPosition();
						}
						else m_fontPalam[fontNum].m_textColor.Set(0.0f, 0.0f, 0.0f, 0.0f);
					}
					break;
				case 3:
					m_spritePos[TargetMark].y = m_spriteRender[FrameIcon06]->Get2DPosition().y;
					m_fontPalam[ItemName00 + sizeTag - 1].pos = m_spriteRender[FrameIcon04]->Get2DPosition();
					m_fontPalam[ItemName00 + sizeTag - 2].pos = m_spriteRender[FrameIcon05]->Get2DPosition();
					m_fontPalam[ItemName00].pos = m_spriteRender[FrameIcon06]->Get2DPosition();

					for (int i = 1; i < 3; i++)
					{
						auto fontNum = i + ItemName00;
						auto IconNum = i + FrameIcon06;
						if (m_spriteRender[IconNum]->IsRender()) {
							m_fontPalam[fontNum].pos = m_spriteRender[IconNum]->Get2DPosition();

						}
						else m_fontPalam[fontNum].m_textColor.Set(0.0f, 0.0f, 0.0f, 0.0f);
					}
					break;
				case 4:
					m_spritePos[TargetMark].y = m_spriteRender[FrameIcon07]->Get2DPosition().y;
					m_fontPalam[ItemName00 + sizeTag - 1].pos = m_spriteRender[FrameIcon04]->Get2DPosition();
					m_fontPalam[ItemName00 + sizeTag - 2].pos = m_spriteRender[FrameIcon05]->Get2DPosition();
					m_fontPalam[ItemName00 + sizeTag - 3].pos = m_spriteRender[FrameIcon06]->Get2DPosition();
					m_fontPalam[ItemName00].pos = m_spriteRender[FrameIcon07]->Get2DPosition();
					if (m_spriteRender[FrameIcon08]->IsRender())
					{
						m_fontPalam[ItemName01].pos = m_spriteRender[FrameIcon08]->Get2DPosition();



					}
					//else m_fontPalam[ItemName01].m_textColor.Set(0.0f, 0.0f, 0.0f, 0.0f);
					break;
				case 5:
					m_spritePos[TargetMark].y = m_spriteRender[FrameIcon08]->Get2DPosition().y;
					for (int i = 0; i < 5; i++) {
						auto fontNum = i + ItemName00;
						auto IconNum = FrameIcon08 - i;
						m_fontPalam[fontNum].pos = m_spriteRender[IconNum]->Get2DPosition();
					}

					break;
				default:
					break;
				}














			}

			/// <summary>
			/// /素材ポーチを選択中
			/// </summary>
			if (p_target == DropItemPouch) {
				if (m_DropItemList.size() > 5 && DropTarget != m_DropItemList.size() - 1)
				{
					m_spriteRender[ItemNext]->SetIsActive(true);
				}
				else m_spriteRender[ItemNext]->SetIsActive(false);
				switch (DropTarget)
				{


				case 0:
					m_spritePos[TargetMark].y = m_spriteRender[FrameIcon04]->Get2DPosition().y;
					m_fontPalam[ItemName00].pos = m_spriteRender[FrameIcon04]->Get2DPosition();
					for (int i = 1; i < 5; i++)
					{
						auto fontNum = i + ItemName00;
						auto IconNum = i + FrameIcon04;
						if (m_spriteRender[IconNum]->IsRender()) {
							m_fontPalam[fontNum].pos = m_spriteRender[IconNum]->Get2DPosition();
							//_itow_s(fontNum, m_fontPalam[fontNum].m_text, 10);
							//m_fontPalam[fontNum].m_textColor.Set(CVector4::White());
						}
						else m_fontPalam[fontNum].m_textColor.Set(0.0f, 0.0f, 0.0f, 0.0f);
					}
					break;
				case 1:
					m_spritePos[TargetMark].y = m_spriteRender[FrameIcon05]->Get2DPosition().y;
					m_fontPalam[ItemName00].pos = m_spriteRender[FrameIcon05]->Get2DPosition();
					m_fontPalam[ItemName00 + sizeTag - 1].pos = m_spriteRender[FrameIcon04]->Get2DPosition();

					for (int i = 1; i < 4; i++)
					{
						auto fontNum = i + ItemName00;
						auto IconNum = i + FrameIcon05;
						if (m_spriteRender[IconNum]->IsRender()) {

							m_fontPalam[fontNum].pos = m_spriteRender[IconNum]->Get2DPosition();
						}
						else m_fontPalam[fontNum].m_textColor.Set(0.0f, 0.0f, 0.0f, 0.0f);
					}
					break;
				case 2:
					m_spritePos[TargetMark].y = m_spriteRender[FrameIcon06]->Get2DPosition().y;
					m_fontPalam[ItemName00 + sizeTag - 1].pos = m_spriteRender[FrameIcon04]->Get2DPosition();
					m_fontPalam[ItemName00 + sizeTag - 2].pos = m_spriteRender[FrameIcon05]->Get2DPosition();
					m_fontPalam[ItemName00].pos = m_spriteRender[FrameIcon06]->Get2DPosition();

					for (int i = 1; i < 3; i++)
					{
						auto fontNum = i + ItemName00;
						auto IconNum = i + FrameIcon06;
						if (m_spriteRender[IconNum]->IsRender()) {
							m_fontPalam[fontNum].pos = m_spriteRender[IconNum]->Get2DPosition();

						}
						else m_fontPalam[fontNum].m_textColor.Set(0.0f, 0.0f, 0.0f, 0.0f);
					}
					break;
				case 3:
					m_spritePos[TargetMark].y = m_spriteRender[FrameIcon07]->Get2DPosition().y;
					m_fontPalam[ItemName00 + sizeTag - 1].pos = m_spriteRender[FrameIcon04]->Get2DPosition();
					m_fontPalam[ItemName00 + sizeTag - 2].pos = m_spriteRender[FrameIcon05]->Get2DPosition();
					m_fontPalam[ItemName00 + sizeTag - 3].pos = m_spriteRender[FrameIcon06]->Get2DPosition();
					m_fontPalam[ItemName00].pos = m_spriteRender[FrameIcon07]->Get2DPosition();
					if (m_spriteRender[FrameIcon08]->IsRender())
					{
						m_fontPalam[ItemName01].pos = m_spriteRender[FrameIcon08]->Get2DPosition();



					}
					//else m_fontPalam[ItemName01].m_textColor.Set(0.0f, 0.0f, 0.0f, 0.0f);
					break;
				case 4:
					m_spritePos[TargetMark].y = m_spriteRender[FrameIcon08]->Get2DPosition().y;
					for (int i = 0; i < 5; i++) {
						auto fontNum = i + ItemName00;
						auto IconNum = FrameIcon08 - i;
						m_fontPalam[fontNum].pos = m_spriteRender[IconNum]->Get2DPosition();
					}

					break;
				default:
					break;
				}
			}

			
			break;
	
		default:



			break;
			}
		
		
		if (MenuStageNum > 0)
		{
			if (g_pad[0].IsTrigger(enButtonB))
			{
				MenuStageNum--;
			}
		}

		if (g_pad[0].IsTrigger(enButtonA))
		{
			if (p_target == DropItemPouch || p_target == UserItemPouch) {
				if (MenuStageNum != 3) {
					MenuStageNum++;
				}
				m_spritePos[TargetMark].x = m_spritePos[FrameIcon04].x-210.0f;
			}
			else if (p_target == Help)
			{

			}
			else if (p_target == Exit)
			{
				exit(0);
			}
			for (int i = 0; i < MenuSize; i++)
			{
				
				if (p_target == i) {
					MenuFlag[i] = true;
				}
				else MenuFlag[i] = false;
			}

		}
		
		for (int i = FrameIcon00; i <= FrameIcon03; i++)
		{
			if (p_target != i - FrameIcon00 &&m_spritePos[i].x<-400.0f)
			{
				m_spritePos[i].x += 50.0f;
				m_spriteSca[i] /= 1.5f;
			}
		}
	}
	else
	{

	for (int i = FrameIcon00; i <= FrameIcon08; i++)
	{

		m_spriteRender[i]->SetIsActive(false);
	}
		m_spriteRender[Pause]->SetIsActive(false);
		m_spriteRender[ReturnCamp]->SetIsActive(false);
		m_spriteRender[TargetMark]->SetIsActive(false);
		m_spriteRender[ManeyPouch]->SetIsActive(false);
		m_spriteRender[ItemNext]->SetIsActive(false);

	}
}
void UI::Update()
{

	std::sort(m_DropItemList.begin(), m_DropItemList.end());
	
	auto m_game = Game::instance();
	auto m_Item = m_game->m_ItemBase;
	m_spriteRender[QuestPaper]->SetIsActive(m_game->IsLookBoard());
	
	m_spriteRender[OrdersQuest]->SetIsActive(m_game->m_quest->IsOnQuest());
	if (wcscmp(m_fontPalam[QuestName].m_text, m_game->m_quest->GetQuestInfo().m_questName) !=0|| !m_game->IsLookBoard())
	{
		m_spriteRender[OrdersQuest]->SetIsActive(false);
	}
	if (!m_game->m_quest->IsOnQuest())
	{
		m_endqestFlag = false;
	}
	if (m_game->m_quest->instance().GetGameState() == QuestManager::GameState::clear)
	{
		ClearDraw();
	}
	if (m_game->m_quest->instance().GetGameState() == QuestManager::GameState::over)
	{
		GameOverDraw();
	}
	
	if (m_game->m_dragon != nullptr&&m_game->GetStageNum() == 3) {
		if (m_game->m_dragon->GetHitFlag())
		{
			AttackEvent = true;
		}
		if (AttackEvent) {
			m_spriteRender[actionLine]->SetIsActive(true);
			m_spriteSca[actionLine] *= 1.6f;
		}
	}
	if (m_spriteSca[actionLine].x > 1280.0f)
	{
		m_spriteSca[actionLine].Set(CVector3::One());
		m_spriteRender[actionLine]->SetIsActive(false);
		AttackEvent = false;
	}

	if (m_game->m_player != nullptr) {
		hp = m_game->m_player->GetPlayerInformation().HP;
		float stamina = m_game->m_player->GetPlayerInformation().Stamina;
		if (hp < 30.0f)
		{
			m_spriteRender[HP]->SetIsActive(false);
			m_spriteRender[Red]->SetIsActive(true);
		}
		if (hp >= 30.0f) {
			m_spriteRender[HP]->SetIsActive(true);
			m_spriteRender[Red]->SetIsActive(false);
		}

		m_spriteSca[HP].x = hp;
		m_spriteSca[Stamina].x = stamina;
		m_spriteSca[Red].x = hp;
	}
	for (int i = 0; i < ItemSpriteTypeNum; i++)
	{
		m_ItemRender[i]->SetIsActive(false);
	}
	//m_Rendertest->SetIsActive(false);
	ChangeItem();
	PauseMenu();
	
	


	for (int i = 0; i < UITypeNum; i++)
	{
		m_spriteRender[i]->SetPosition(m_spritePos[i]);
		m_spriteRender[i]->SetScale(m_spriteSca[i]);
	}
	
	SetFontPalam();
}

