#pragma once

#include "SceneLight.h"
#include "IRenderer.h"
#include "Bloom.h"
#include "Shadow.h"

namespace nsK2EngineLow
{
	class RenderingEngine : public Noncopyable
	{
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		void Init();

		/// <summary>
		/// 描画処理を実行
		/// </summary>
		/// <param name="rc"></param>
		void Execute(RenderContext& rc);

		void AddRenderObject(IRenderer* renderObject)
		{
			m_renderObjects.push_back(renderObject);
		}

		/// <summary>
		/// シャドウマップを取得
		/// </summary>
		/// <returns></returns>
		RenderTarget& GetShadow()
		{
			return m_shadow.GetRenderTarget();
		}

		/// <summary>
		/// ライトを取得
		/// </summary>
		/// <returns></returns>
		Light& GetLight()
		{
			return m_sceneLight.GetLight();
		}

		/// <summary>
		/// ライトカメラを取得
		/// </summary>
		Camera& GetLightCamera()
		{
			return m_sceneLight.GetLightCamera();
		}

	private:

		/// <summary>
		/// メインレンダリングターゲットの初期化
		/// </summary>
		void InitMainRenderTarget();

		/// <summary>
		/// 2D(フォントとスプライト)の初期化
		/// </summary>
		void Init2DSprite();

		/// <summary>
		/// モノクロ用のレンダリングターゲットの初期化
		/// </summary>
		void InitMonochromeRenderTarget();

		/// <summary>
		/// メインレンダリングターゲットのカラーバッファの内容を
		/// フレームバッファにコピーするためのスプライトを初期化する
		/// </summary>
		void InitCopyMainRenderTargetToFrameBuffer();

		/// <summary>
		/// モデルの描画
		/// </summary>
		/// <param name="rc"></param>
		void ModelDraw(RenderContext& rc);

		/// <summary>
		/// 2D(フォントとスプライト)の描画
		/// </summary>
		/// <param name="rc"></param>
		void SpriteFontDraw(RenderContext& rc);

		/// <summary>
		/// モノクロの描画
		/// </summary>
		/// <param name="rc"></param>
		void OnMonochromeRendering(RenderContext& rc);

		/// <summary>
		/// メインレンダリングターゲットの内容をフレームバッファにコピーする
		/// </summary>
		/// <param name="rc"></param>
		void CopyMainRenderTargetToFrameBuffer(RenderContext& rc);

		SceneLight m_sceneLight; //シーンライト
		RenderTarget m_mainRenderTarget; //メインレンダリングターゲット
		RenderTarget m_2DRenderTarget; //2Dレンダリングターゲット
		RenderTarget m_monochromeRenderTarget; //モノクロ用レンダリングターゲット
		Sprite m_2DSprite; //2D(フォントとスプライト)用スクリプト
		Sprite m_mainSprite; //メイン(モデル)用スプライト
		Sprite m_monochromeSprite; //モノクロ用スプライト
		Sprite m_copyToFrameBufferSprite; //メインレンダリングターゲットをフレームバッファにコピーするためのレンダリングターゲット
		Bloom m_bloom; //ブルーム
		Shadow m_shadow; //シャドウマップ
		std::vector< IRenderer* > m_renderObjects; //レンダリングオブジェクトの格納
	};
}

