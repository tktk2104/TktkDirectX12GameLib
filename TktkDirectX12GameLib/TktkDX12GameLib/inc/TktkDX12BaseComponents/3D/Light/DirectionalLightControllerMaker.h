#ifndef DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_
#define DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "DirectionalLightController.h"

namespace tktk
{
	class DirectionalLightControllerMaker
	{
	private: /* プライベートコンストラクタ達 */

		DirectionalLightControllerMaker() = default;
		DirectionalLightControllerMaker(const DirectionalLightControllerMaker& other) = default;
		DirectionalLightControllerMaker& operator = (const DirectionalLightControllerMaker& other) = default;

	public:

		// 作成開始
		static DirectionalLightControllerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<DirectionalLightController> create();

	public:  /* パラメータ設定関数 */

		// 使用する初期ライトハンドルを設定する
		// ※初期パラメータはデフォルトライト
		DirectionalLightControllerMaker& initLightHandle(unsigned int value);

		// 初期方向を設定する
		DirectionalLightControllerMaker& initDirection(const tktkMath::Vector3& value);

		// 使用する初期ライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトライト
		template<class IdType, is_idType<IdType> = nullptr>
		DirectionalLightControllerMaker& initLightId(IdType value) { return initLightIdImpl(static_cast<int>(value)); }

		// 初期環境光を設定する
		DirectionalLightControllerMaker& initAmbient(const tktkMath::Color & value);

		// 初期拡散反射光を設定する
		DirectionalLightControllerMaker& initDiffuse(const tktkMath::Color & value);

		// 初期鏡面反射光を設定する
		DirectionalLightControllerMaker& initSpeqular(const tktkMath::Color & value);

	private: /* 各種id指定系の関数の実装 */

		DirectionalLightControllerMaker& initLightIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static DirectionalLightControllerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user				{  };
		unsigned int		m_initLightHandle	{ 0U };
		tktkMath::Vector3	m_initDirection		{ 1.0f, -1.0f, 1.0f };
		tktkMath::Color		m_initAmbient		{ 0.25f, 1.0f };
		tktkMath::Color		m_initDiffuse		{ 0.25f, 1.0f };
		tktkMath::Color		m_initSpeqular		{ 0.25f, 1.0f };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		DirectionalLightControllerMaker& initLightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
}
#endif // !DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_