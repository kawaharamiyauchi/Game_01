#include "stdafx.h"
#include "FontRender.h"


FontRender::FontRender()
{
}


FontRender::~FontRender()
{
}

void FontRender::PostFontRender()
{
	m_font.Begin();
	const wchar_t* text = nullptr;
	if (m_textUnsafe != nullptr) {
		text = m_textUnsafe;
	}
	else if (m_text.c_str() != nullptr) {
		text = m_text.c_str();
	}
	m_font.Draw(
		text,
		m_position,
		m_color,
		m_rotation,
		m_scale,
		m_pivot);
	m_font.End();
}

void FontRender::Update()
{
}

void FontRender::Render()
{

}

//void FontRender::PostRender()
//{
//		
//	m_font.Begin();
//	const wchar_t* text = nullptr;
//	if (m_textUnsafe != nullptr) {
//		text = m_textUnsafe;
//	}
//	else if (m_text.c_str() != nullptr) {
//		text = m_text.c_str();
//	}
//	m_font.Draw(
//		text,
//		m_position,
//		m_color,
//		m_rotation,
//		m_scale,
//		m_pivot);
//	m_font.End();
//}
