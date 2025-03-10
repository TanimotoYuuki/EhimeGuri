#include "k2EngineLowPreCompile.h"
#include "FontRender.h"

namespace nsK2EngineLow {
	void FontRender::Draw(RenderContext& rc)
	{
		if (m_text == nullptr)
		{
			return;
		}
		m_font.Begin(rc);
		m_font.Draw(GetText(), Vector2(m_position.x, m_position.y), m_color, m_rotation, m_scale, m_pivot);
		m_font.End(rc);
	}
}