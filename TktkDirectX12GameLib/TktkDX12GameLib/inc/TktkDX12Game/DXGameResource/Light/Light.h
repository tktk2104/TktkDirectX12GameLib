#ifndef LIGHT_H_
#define LIGHT_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "LightData.h"

namespace tktk
{
	// 「LightData」を管理するクラス
	class Light
	{
	public:

		explicit Light(const tktkContainer::ResourceContainerInitParam& initParam);
		~Light() = default;

	public:

		// 「LightData」のインスタンスを作り、そのリソースのハンドルを返す
		unsigned int create(
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ライト情報の定数バッファを更新する
		void updateLightCBuffer(unsigned int handle) const;

		// 指定のライトの環境光を設定する
		void setAmbient(unsigned int handle, const tktkMath::Color& ambient);

		// 指定のライトの拡散反射光を設定する
		void setDiffuse(unsigned int handle, const tktkMath::Color& diffuse);

		// 指定のライトの鏡面反射光を設定する
		void setSpeqular(unsigned int handle, const tktkMath::Color& speqular);

		// 指定のライトの座標を設定する
		void setPosition(unsigned int handle, const tktkMath::Vector3& position);

	private:

		tktkContainer::ResourceContainer<LightData> m_lightArray;
	};
}
#endif // !LIGHT_H_