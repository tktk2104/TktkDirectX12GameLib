#ifndef LIGHT_H_
#define LIGHT_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

/* funcUseType */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	class LightData;

	// 「LightData」を管理するクラス
	class LightManager
	{
	public:

		explicit LightManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~LightManager();

	public:

		// 「LightData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ライト情報の定数バッファを更新する
		void updateLightCBuffer(size_t handle) const;

		// 指定のライトの環境光を設定する
		void setAmbient(size_t handle, const tktkMath::Color& ambient);

		// 指定のライトの拡散反射光を設定する
		void setDiffuse(size_t handle, const tktkMath::Color& diffuse);

		// 指定のライトの鏡面反射光を設定する
		void setSpeqular(size_t handle, const tktkMath::Color& speqular);

		// 指定のライトの座標を設定する
		void setPosition(size_t handle, const tktkMath::Vector3& position);

	private:

		tktkContainer::ResourceContainer<LightData> m_lightArray;
	};
}
#endif // !LIGHT_H_