#ifndef DIRECTIONAL_LIGHT_CONTROLLER_H_
#define DIRECTIONAL_LIGHT_CONTROLLER_H_

#include <TktkMath/Structs/Vector3.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	// ディレクショナルライト制御コンポーネント
	class DirectionalLightController
		: public ComponentBase
	{
	public:

		DirectionalLightController(
			unsigned int lightHandle,
			const tktkMath::Vector3& direction,
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular
		);

	public:

		void start();
		void afterCollide();

	public:

		// ライトの方向を設定する
		void setDirection(const tktkMath::Vector3& direction);

		// 環境光を設定する
		void setAmbient(const tktkMath::Color& ambient);

		// 拡散反射光を設定する
		void setDiffuse(const tktkMath::Color& diffuse);

		// 鏡面反射光を設定する
		void setSpeqular(const tktkMath::Color& speqular);

	private:

		// ライト情報を更新する
		void updateLight();

	private:

		unsigned int				m_lightHandle;
		tktkMath::Vector3			m_direction;
		tktkMath::Color				m_ambient;
		tktkMath::Color				m_diffuse;
		tktkMath::Color				m_speqular;
	};
}
#endif // !DIRECTIONAL_LIGHT_CONTROLLER_H_
