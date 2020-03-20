#include "stdafx.h"
#include "UI.h"
#include"Game.h"
#include"Player.h"
#include "QuestManager.h"
#include"Dragon.h"
#include"FontRender.h"


Item::Item()
{
	InitItem(&m_Item[noneItem], User_Item, 255, 255);
	InitItem(&m_Item[kaihukuyaku], User_Item, 5, 10);
	InitItem(&m_Item[ItemDummy00], User_Item, 2, 10);
	InitItem(&m_Item[ItemDummy01], User_Item, 6, 10);

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
	

	for (int i = 0; i < UITypeNum; i++) {
		m_spriteRender[i] = GameObjectManager::instance().NewGO<SpriteRender>();
		m_spriteSca[i].Set(100.0f, 2.0f, 1.0f);
		m_spritePos[i].Set(CVector3::One());
		m_spriteRender[i]->SetPivot({ 0.0f,0.5f });
	}
	for (int i = 0; i < ItemSpriteTypeNum; i++)
	{
		m_ItemRender[i] = GameObjectManager::instance().NewGO<SpriteRender>();
	}
	m_sideRender = GameObjectManager::instance().NewGO<SpriteRender>();
	m_spritePos[HP].Set(-550.0f, 340.0f, 0.0f);
	m_spritePos[Stamina].Set(-550.0f, 300.0f, 0.0f);
	m_spritePos[Red].Set(-550.0f, 340.0f, 0.0f);
	

	m_spriteRender[HP]->Init(L"Assets/sprite/MH_HP.dds",10.0f,10.0f);
	
	m_spriteRender[Stamina]->Init(L"Assets/sprite/MH_stamina.dds", 10.0f, 10.0f);
	m_spriteRender[Clear]->Init(L"Assets/sprite/MH_QUESTCLEAR .dds", 20.0f, 300.0f);
	m_spriteRender[Clear]->SetIsActive(false);
	m_spriteRender[Clear]->SetPivot({ 0.5f,0.5f });
	m_spriteRender[Clear]->SetScale(CVector3::One());

	m_spriteRender[GameOver]->Init(L"Assets/sprite/MH_QUESTFAILED.dds", 20.0f, 300.0f);
	m_spriteRender[GameOver]->SetIsActive(false);
	m_spriteRender[GameOver]->SetPivot({ 0.5f,0.5f });
	m_spriteRender[GameOver]->SetScale(CVector3::One());

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

	m_ItemRender[ItemDummy01]->Init(L"Assets/sprite/MH_HP.dds", 80.0f, 80.0f);
	m_ItemRender[ItemDummy01]->SetPivot({ 0.5f,0.5f });
	m_ItemRender[ItemDummy01]->SetIsActive(false);
	m_ItemRender[ItemDummy01]->SetAlpha(1.0f);

	m_spriteRender[QuestPaper]->Init(L"Assets/sprite/QuestPaper.dds", 40.0f, 60.0f);
	m_spriteRender[QuestPaper]->SetPivot({ 0.5f,0.5f });
	m_spriteSca[QuestPaper].Set(10.0f, 10.0f, 1.0f);
	m_spriteRender[QuestPaper]->SetIsActive(false);

	m_spriteRender[Pause]->Init(L"Assets/sprite/PauseMenu.dds",1280.f, 720.0f);
	m_spriteRender[Pause]->SetIsActive(false);
	m_spritePos[Pause].Set(0.0f, 0.0f, 0.0f);
	m_spriteRender[Pause]->SetPivot({ 0.5f, 0.5f });
	m_spriteSca[Pause].Set(CVector3::One());

	m_sideRender->Init(L"Assets/sprite/NonItem.dds", 80.0f, 80.0f);
	m_sideRender->SetAlpha(1.0f);
	m_sideRender->SetIsActive(false);
	m_sideRender->SetPivot({ 0.5f, 0.5f });
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
	m_ItemList.clear();
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
	auto m_Item = Game::instance()->m_Item;
		int itemnum = m_Item->GetData(targetItem).num;
		_itow_s(itemnum, m_fontPalam[ItemNumber].m_text, 10);
		m_fontPalam[ItemNumber].m_frameWidth = 3.0f;
		m_fontPalam[ItemNumber].pos = { 350.0f,-230.0f };
		m_fontPalam[ItemNumber].size = 0.7f;
		m_fontPalam[ItemNumber].m_textColor = CVector4::White();
		for (int i = 0; i < FontTypeNum; i++)
		{
			if (m_fontPalam[i].m_frameWidth > 0.0f)
			{
				m_fontPalam[i].frameFlag = true;
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
	m_spriteRender[Clear]->SetIsActive(true);
	m_spriteRender[Clear]->SetAlpha(m_alpha);
}

void UI::GameOverDraw()
{
	if (m_alpha < 1.0f) {
		m_alpha += 0.02f;
	}
	m_spriteRender[GameOver]->SetIsActive(true);
	m_spriteRender[GameOver]->SetAlpha(m_alpha);
}

void UI::Update()
{

	
	auto m_game = Game::instance();
	auto m_Item = m_game->m_Item;

	if (m_game->m_quest->instance().GetGameState() == QuestManager::GameState::clear)
	{
		ClearDraw();
	}
	if (m_game->m_quest->instance().GetGameState() == QuestManager::GameState::over)
	{
		GameOverDraw();
	}
	if (m_game->GetPauseFlag())
	{
		m_spriteRender[Pause]->SetIsActive(true);
	}
	else m_spriteRender[Pause]->SetIsActive(false);
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
	m_sideRender->SetIsActive(false);
	ChangeItem();
	SetFontPalam();
}

