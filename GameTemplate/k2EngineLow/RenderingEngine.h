#pragma once

#include "SceneLight.h"

namespace nsK2EngineLow
{
	class RenderingEngine : public Noncopyable
	{
	public:
		/// <summary>
		/// ‰Šú‰»
		/// </summary>
		void Init();

		/// <summary>
		/// •`‰æˆ—‚ğÀs
		/// </summary>
		/// <param name="rc"></param>
		void Execute(RenderContext& rc);

		/// <summary>
		/// ƒ‰ƒCƒg‚ğæ“¾
		/// </summary>
		/// <returns></returns>
		Light& GetLight()
		{
			return m_sceneLight.GetLight();
		}

	private:
		SceneLight m_sceneLight;
	};
}

