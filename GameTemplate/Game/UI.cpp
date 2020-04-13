#include "stdafx.h"
#include "UI.h"
#include"Game.h"
#include"Player.h"
#include "QuestManager.h"
#include"Dragon.h"
#include"FontRender.h"


Item::Item()
{
	InitItem(&m_Item[noneItem], User_Item, 255, 255,0);
	InitItem(&m_Item[kaihukuyaku], User_Item, 5, 10,100);
	InitItem(&m_Item[ItemDummy00], User_Item, 2, 10,100);
	InitItem(&m_Item[ItemDummy01], User_Item, 6, 10,100);

	InitItem(&m_Item[Herbs], Drop_Item, 5, 99,20);
	InitItem(&m_Item[PoisonouMushroom], Drop_Item, 6, 99,20);
	InitItem(&m_Item[mushroom],Drop_Item, 10, 99,20);
	InitItem(&m_Item[Treenut], Drop_Item, 11, 99,1);
	InitItem(&m_Item[smallstone], Drop_Item, 12, 99,1);
	InitItem(&m_Item[B_L_LizardTail], Drop_Item, 3, 99,5000);
	InitItem(&m_Item[B_L_LizardClaw], Drop_Item, 1, 99,2500);
	InitItem(&m_Item[B_L_LizardScales], Drop_Item, 3, 99,100);
	InitItem(&m_Item[B_L_LizardFang], Drop_Item, 3, 99,2500);

}

int Item::UseItem()
{
	auto m_selectItem = Game::instance()->m_UI->GetTargetItem();
	if (m_Item[m_selectItem].num > 0 && m_selectItem > 0)
	{
		m_Item[m_selectItem].num--;
		return m_selectItem;
	}

	else return -1;
}
void Item::Update()
{

}
void Item::Render()
{

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

	m_ItemRender[ItemDummy01]->Init(L"Assets/sprite/ago_free_03.dds", 80.0f, 80.0f);
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


	m_spriteRender[Result]->Init(L"Assets/sprite/Result.dds", 1280.0f, 720.0f);
	m_spriteRender[Result]->SetIsActive(false);
	m_spritePos[Result].Set(0.0f, 0.0f, 0.0f);
	m_spriteRender[Result]->SetPivot({ 0.5f, 0.5f });

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

	m_spriteRender[ManeyPouch]->Init(L"Assets/sprite/moneyPouch.dds", 100.0f, 80.0f);
	m_spritePos[ManeyPouch].Set( -600.0f, -300.0f,-0.0f );
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

	auto m_Item = Game::instance()->m_Item;
	nonhaveItem = 0;
	haveItemNum = 0;
	
	for (int i = 0; i < Item::ItemType::TypeNum; i++)
	{
		if (m_Item->GetData(i).isUse == Item::IsUse::User_Item) {
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
		else if (m_Item->GetData(i).isUse == Item::IsUse::Drop_Item)
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
			
			m_ItemRender[m_ItemList[targetItem+1]]->SetIsActive(true);
			m_ItemRender[m_ItemList[targetItem+1]]->SetPosition(m_nextItemPos);
			m_ItemRender[m_ItemList[targetItem+1]]->SetScale(m_sideItemSca);

			
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
	auto m_game = Game::instance();
	if (m_game->GetPauseFlag()&&MenuFlag[D_Pouch])
	{
		if (MenuStageNum == 1) {
			if (g_pad[0].IsTrigger(enButtonDown))
			{
				if (DropTarget < m_DropItemList.size() - 1)
				{
					DropTarget++;
				}

			}
			if (g_pad[0].IsTrigger(enButtonUp))
			{
				if (DropTarget > 0)
				{
					DropTarget--;
				}

			}
			d_target = m_DropItemList[DropTarget];
		}

	}
	m_ItemList.clear();
	m_DropItemList.clear();
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
	auto m_Item = Game::instance()->m_Item;
	auto m_quest = Game::instance()->m_quest;
	auto m_queboardInfo = m_quest->GetDispInfo();
	auto m_queInfo = m_quest->GetQuestInfo();
		int itemnum = m_Item->GetData(targetItem).num;
		int d_itemnum = m_Item->GetData(d_target).num;
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
		m_fontPalam[ItemName].size = 0.6f;
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





		switch (d_target)
		{
		case(Item::Herbs):

			wcscpy(m_fontPalam[ItemName].m_text, L"薬草");
			wcscpy(m_fontPalam[ItemSummry].m_text, L"フィールド広域で採取できる草。\n");
			break;
		case(Item::PoisonouMushroom):
			wcscpy(m_fontPalam[ItemName].m_text, L"毒茸");
			wcscpy(m_fontPalam[ItemSummry].m_text, L"毒を含むキノコ。\n");

			break;
		case(Item::mushroom):
			wcscpy(m_fontPalam[ItemName].m_text, L"大茸");
			wcscpy(m_fontPalam[ItemSummry].m_text, L"大きな美味しいキノコ。\n");

			break;
		case(Item::Treenut):
			wcscpy(m_fontPalam[ItemName].m_text, L"木の実");
			wcscpy(m_fontPalam[ItemSummry].m_text, L"小さい。\n");

			break;
		case(Item::smallstone):
			wcscpy(m_fontPalam[ItemName].m_text, L"小石");
			wcscpy(m_fontPalam[ItemSummry].m_text, L"何の変哲もないただの石。\n");

			break;
		case(Item::B_L_LizardTail):
			wcscpy(m_fontPalam[ItemName].m_text, L"青紋小竜の尻尾");
			wcscpy(m_fontPalam[ItemSummry].m_text, L"砂漠地帯に生息する青紋小竜の尻尾。\n切れてもまた生えてくる。");

			break;
		case(Item::B_L_LizardClaw):
			wcscpy(m_fontPalam[ItemName].m_text, L"青紋小竜の爪");
			wcscpy(m_fontPalam[ItemSummry].m_text, L"砂漠地帯に生息する青紋小竜の爪。\n獲物の肉に食い込む強靭な爪。");

			break;
		case(Item::B_L_LizardScales):
			wcscpy(m_fontPalam[ItemName].m_text, L"青紋小竜の鱗");
			wcscpy(m_fontPalam[ItemSummry].m_text, L"砂漠地帯に生息する青紋小竜の鱗。\n鮮やかな青色の鱗は価値が高く防具製作などに\nよく使われる。");

			break;
		case(Item::B_L_LizardFang):
			wcscpy(m_fontPalam[ItemName].m_text, L"青紋小竜の牙");
			wcscpy(m_fontPalam[ItemSummry].m_text, L"砂漠地帯に生息する青紋小竜の牙。\n獲物をかみ切る強靭な牙。");

			break;
		default:
			break;
		}
		/// <summary>
		/// 一時停止画面中
		/// </summary>
		if (m_game->GetPauseFlag())
		{

			
			

			int m_prizemoney = m_queInfo.m_prizeMoney;
			int goalnum = m_queInfo.m_targetNum;
			int targetnum = m_quest->GetQuestPoint();

			int m_havemoney = m_quest->GetMoney();
			wchar_t m_moneytext[255];
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
			_itow_s( d_itemnum,m_itemnum, 10);
			_itow_s(goalnum, m_fontPalam[GoalNum].m_text, 10);
			_itow_s(targetnum, m_fontPalam[QuestPoint].m_text, 10);
			_itow_s(m_havemoney, m_fontPalam[HaveMoney].m_text,10);
			wcscat(m_fontPalam[QuestPoint].m_text, L"/");
			//wcscat(m_fontPalam[HaveMoney].m_text, m_moneytext);
			wcscat( m_fontPalam[PrizeMoney].m_text,m_prizetext);
			wcscat(m_fontPalam[DropItemNumber].m_text, m_itemnum);

			m_fontPalam[QuestName].pivot = { 0.0f,0.5f };
			m_fontPalam[QuestSummary].pivot = { 0.0f,0.5f };
			m_fontPalam[PrizeMoney].pivot = { 0.0f,0.5f };
			m_fontPalam[RequesterName].pivot = { 0.0f,0.5f };
			m_fontPalam[GoalNum].pivot = { 0.0f,0.5f };
			m_fontPalam[QuestPoint].pivot = { 0.0f,0.5f }; 
			m_fontPalam[HaveMoney].pivot = { 0.0f,0.5f };
			m_fontPalam[DropItemNumber].pivot = { 1.0f,0.5f };
			m_fontPalam[ItemSummry].pivot = { 1.0f,0.5f };


			m_fontPalam[QuestName].pos = { -600.0f,220.0f };
			m_fontPalam[QuestSummary].pos = { -600.0f,190.0f };
			m_fontPalam[GoalNum].pos = { -560.0f,162.0f };
			m_fontPalam[QuestPoint].pos = { -600.0f,160.0f };
			m_fontPalam[PrizeMoney].pos = { -600.0f,130.0f };
			m_fontPalam[HaveMoney].pos = { -500.0f,-300.0f };
			m_fontPalam[DropItemNumber].pos = { 500.0f,200.0f };
			m_fontPalam[ItemSummry].pos = { 500.0f,300.0f };

			//m_fontPalam[DropItemNumber].m_textColor = CVector4::White();
			//m_fontPalam[ItemName].m_textColor = CVector4::White();
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
			/// かつ素材ポーチを見ている時
			/// </summary>
			if (MenuFlag[DropItemPouch])
			{
				if (MenuStageNum == 1) {
					m_fontPalam[ItemName].pos = m_spriteRender[FrameIcon04]->Get2DPosition();
					m_fontPalam[ItemName].m_textColor.Set(CVector4::White());
					
				}
				if (MenuStageNum >= 2)
				{
					m_fontPalam[ItemSummry].m_textColor.Set(CVector4::White());
					m_fontPalam[DropItemNumber].m_textColor.Set(CVector4::White());
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
			m_spriteRender[Pause]->SetIsActive(false);
			m_spriteRender[ReturnCamp]->SetIsActive(false);
			for (int i = FrameIcon00; i <= FrameIcon08; i++)
			{

				m_spriteRender[i]->SetIsActive(false);
			}
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
			
			m_fontPalam[HaveMoney].m_textColor.Set(CVector4::White());
			m_fontPalam[HaveMoney].size = 1.0f;
			m_fontPalam[HaveMoney].pos = { -600.0f,0.0f };

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
				m_fontPalam[i].frameFlag = false;
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

	
}
void UI::ClearDraw()
{
	if (m_alpha < 1.0f) {
		m_alpha += 0.02f;
	}
	if (!ResultFlag) {
		m_spriteRender[Clear]->SetIsActive(true);
		m_spriteRender[Clear]->SetAlpha(m_alpha);
	}

	if (g_pad[0].IsTrigger(enButtonStart))
	{
		m_alpha = 0;
		m_spriteRender[Result]->SetIsActive(true);
		ResultFlag = true;
		m_spriteRender[Clear]->SetIsActive(false);
	}
	m_spriteRender[Result]->SetAlpha(m_alpha);
}

void UI::GameOverDraw()
{
	if (m_alpha < 1.0f) {
		m_alpha += 0.02f;
	}
	m_spriteRender[GameOver]->SetIsActive(true);
	m_spriteRender[GameOver]->SetAlpha(m_alpha);
}

void UI::PauseMenu()
{
	auto m_game = Game::instance();
	
	
	if (m_game->GetPauseFlag()) {

		for (int i = FrameIcon00; i <= FrameIcon03; i++)
		{
			m_spriteRender[i]->SetIsActive(true);
			m_fontPalam[i+1].pos = m_spriteRender[i]->Get2DPosition();

		}

		for (int i = FrameIcon04; i <= FrameIcon08; i++)
		{
			m_spriteRender[i]->SetIsActive(true);
		}
		m_spriteRender[Pause]->SetIsActive(true);
		m_spriteRender[ReturnCamp]->SetIsActive(true);
		m_spriteRender[TargetMark]->SetIsActive(true);
		m_spriteRender[ManeyPouch]->SetIsActive(true);
		if (MenuStageNum == 0) {

			if (g_pad[0].IsTrigger(enButtonDown))
			{

				if (p_target != 3)
				{
					p_target++;
				}
			}
			if (g_pad[0].IsTrigger(enButtonUp))
			{

				if (p_target != 0) {

					p_target--;
				}
			}
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
		switch (p_target)
		{
		case 0:
			m_spritePos[TargetMark].y = m_spriteRender[FrameIcon00]->Get2DPosition().y;
			m_fontPalam[U_Pouch].m_textColor.Set(0.0f, 0.5f, 0.5f,1.0f);
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
		for (int i = FrameIcon00; i <= FrameIcon03; i++)
		{
			if (p_target != i - 10&&m_spritePos[i].x<-400.0f)
			{
				m_spritePos[i].x += 50.0f;
				m_spriteSca[i] /= 1.5f;
			}
		}
	}
	else
	{
		m_spriteRender[TargetMark]->SetIsActive(false);
	}
}
void UI::Update()
{

	
	auto m_game = Game::instance();
	auto m_Item = m_game->m_Item;
	m_spriteRender[QuestPaper]->SetIsActive(m_game->IsLookBoard());
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
	for (int i = 0; i < UITypeNum; i++)
	{
		m_spriteRender[i]->SetPosition(m_spritePos[i]);
		m_spriteRender[i]->SetScale(m_spriteSca[i]);
	}
	for (int i = 0; i < ItemSpriteTypeNum; i++)
	{
		m_ItemRender[i]->SetIsActive(false);
	}
	//m_Rendertest->SetIsActive(false);
	PauseMenu();
	ChangeItem();
	SetFontPalam();
}

