#include "k2EngineLowPreCompile.h"
#include "SceneLight.h"
namespace nsK2EngineLow
{
	void SceneLight::Init()
	{
		//ディレクションライトの方向
		m_light.directionLight.direction.x = 1.0f;
		m_light.directionLight.direction.y = -1.0f;
		m_light.directionLight.direction.z = -1.0f;

		//正規化
		m_light.directionLight.direction.Normalize();

		//ディレクションライトのカラー
		m_light.directionLight.color.x = 1.0f;
		m_light.directionLight.color.y = 1.0f;
		m_light.directionLight.color.z = 1.0f;

		//環境光
		m_light.ambientLight.x = 0.3f;
		m_light.ambientLight.y = 0.3f;
		m_light.ambientLight.z = 0.3f;
		m_light.eyePos = g_camera3D->GetPosition();

		//半球ライトの地面色
		m_light.hemLight.groundColor = Vector3(0.1f, 0.1f, 0.1f);
		//半球ライトの天球色
		m_light.hemLight.skyColor = Vector3(0.05f, 0.1f, 0.2f);
		//半球ライトの地面の法線
		m_light.hemLight.groundNormal = Vector3(0.0f, 1.0f, 0.0f);

		//カメラの位置を設定
		m_lightCamera.SetPosition(g_camera3D->GetTarget() + Vector3(0, 600, 0));
		//カメラの注視点を設定
		m_lightCamera.SetTarget(g_camera3D->GetTarget());
		//上方向を設定
		m_lightCamera.SetUp(1, 0, 0);
		//ライトビュープロジェクション行列の計算
		m_lightCamera.Update();
		m_light.mLVP = m_lightCamera.GetViewProjectionMatrix();
	}

	void SceneLight::LightCameraUpdate()
	{
		//カメラの位置を設定
		m_lightCamera.SetPosition(g_camera3D->GetTarget() + Vector3(-300, 600, 200));
		//カメラの注視点を設定
		m_lightCamera.SetTarget(g_camera3D->GetTarget());
		//ライトビュープロジェクション行列の計算
		m_lightCamera.Update();
		m_light.mLVP = m_lightCamera.GetViewProjectionMatrix();
	}
}