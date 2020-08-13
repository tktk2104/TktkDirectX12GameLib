#ifndef POINT_LIGHT_CONTROLLER_H_
#define POINT_LIGHT_CONTROLLER_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// ポイントライト制御コンポーネント
	// 【必須コンポーネント：Transform3D】
	class PointLightController
		: public ComponentBase
	{
	public:

		PointLightController(
			unsigned int lightId,
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular
		);

	public:

		void start();
		void afterCollide();

	public:

		// 環境光を設定する
		void setAmbient(const tktkMath::Color& ambient);

		// 拡散反射光を設定する
		void setDiffuse(const tktkMath::Color& diffuse);

		// 鏡面反射光を設定する
		void setSpeqular(const tktkMath::Color& speqular);

	private:

		// ライト情報を自身の引数と「Transform3D」を使って更新する
		void updateLight();

	private:

		unsigned int				m_lightId;
		tktkMath::Color				m_ambient;
		tktkMath::Color				m_diffuse;
		tktkMath::Color				m_speqular;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !POINT_LIGHT_CONTROLLER_H_