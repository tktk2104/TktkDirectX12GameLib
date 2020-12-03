#ifndef DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_
#define DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
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
		DirectionalLightControllerMaker& initLightHandle(size_t value);

		// 使用する初期ライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトライト
		DirectionalLightControllerMaker& initLightId(ResourceIdCarrier value);

		// 初期環境光を設定する
		DirectionalLightControllerMaker& initAmbient(const tktkMath::Color & value);

		// 初期拡散反射光を設定する
		DirectionalLightControllerMaker& initDiffuse(const tktkMath::Color & value);

		// 初期鏡面反射光を設定する
		DirectionalLightControllerMaker& initSpeqular(const tktkMath::Color & value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static DirectionalLightControllerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user				{  };
		size_t				m_initLightHandle	{ 0U };
		tktkMath::Color		m_initAmbient		{ 0.1f, 1.0f };
		tktkMath::Color		m_initDiffuse		{ 1.0f, 1.0f };
		tktkMath::Color		m_initSpeqular		{ 1.0f, 1.0f };
	};
}
#endif // !DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_