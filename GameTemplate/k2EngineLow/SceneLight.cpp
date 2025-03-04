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
		m_light.directionLight.color.x = 1.2f;
		m_light.directionLight.color.y = 1.2f;
		m_light.directionLight.color.z = 1.2f;

		//環境光
		m_light.ambientLight.x = 0.3f;
		m_light.ambientLight.y = 0.3f;
		m_light.ambientLight.z = 0.3f;
		m_light.eyePos = g_camera3D->GetPosition();
	}
}