#pragma once

namespace nsK2EngineLow
{
	class IRenderer : public Noncopyable
	{
	public:
		/// <summary>
		/// ƒ‚ƒfƒ‹‚Ì•`‰æ
		/// </summary>
		/// <param name="rc"></param>
		virtual void OnRenderModel(RenderContext& rc)
		{

		}

		/// <summary>
		/// 2D‚Ì•`‰æ
		/// </summary>
		/// <param name="rc"></param>
		virtual void OnRender2D(RenderContext& rc)
		{

		}
	};
}

