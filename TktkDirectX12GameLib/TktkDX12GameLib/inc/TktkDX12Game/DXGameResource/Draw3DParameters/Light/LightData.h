#ifndef LIGHT_DATA_H_
#define LIGHT_DATA_H_

/* class member */
#include "LightCBuffer.h"

namespace tktk
{
	// ライト情報を管理するクラス
	class LightData
	{
	public:

		LightData(
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);
		~LightData();

		// ムーブコンストラクタ
		LightData(LightData&& other) noexcept;

	public:

		// ライト情報の定数バッファを更新する
		void updateLightCBuffer() const;

		// 環境光を設定する
		void setAmbient(const tktkMath::Color& ambient);

		// 拡散反射光を設定する
		void setDiffuse(const tktkMath::Color& diffuse);

		// 鏡面反射光を設定する
		void setSpeqular(const tktkMath::Color& speqular);

		// 座標を設定する
		void setPosition(const tktkMath::Vector3& position);

	private:

		// 定数バッファのコピー用バッファを更新する
		void updateCopyBuffer() const;

	private:

		size_t				m_createUploadBufferHandle{ 0U };
		LightCBuffer		m_lightCBuffer;
	};
}
#endif // !LIGHT_DATA_H_