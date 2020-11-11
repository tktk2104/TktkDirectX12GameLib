#ifndef POINT_LIGHT_CONTROLLER_MAKER_H_
#define POINT_LIGHT_CONTROLLER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "PointLightController.h"

namespace tktk
{
	// 「PointLightController」を作るヘルパークラス
	class PointLightControllerMaker
	{
	private: /* プライベートコンストラクタ達 */

		PointLightControllerMaker() = default;
		PointLightControllerMaker(const PointLightControllerMaker& other) = default;
		PointLightControllerMaker& operator = (const PointLightControllerMaker& other) = default;

	public:

		// 作成開始
		static PointLightControllerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<PointLightController> create();

	public:  /* パラメータ設定関数 */

		// 使用する初期ライトハンドルを設定する
		// ※初期パラメータはデフォルトライト
		PointLightControllerMaker& initLightHandle(size_t value);

		// 使用する初期ライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトライト
		PointLightControllerMaker& initLightId(ResourceIdCarrier value);

		// 初期環境光を設定する
		PointLightControllerMaker& initAmbient(const tktkMath::Color& value);

		// 初期拡散反射光を設定する
		PointLightControllerMaker& initDiffuse(const tktkMath::Color& value);

		// 初期鏡面反射光を設定する
		PointLightControllerMaker& initSpeqular(const tktkMath::Color& value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static PointLightControllerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user				{  };
		size_t				m_initLightHandle	{ 0U };
		tktkMath::Color		m_initAmbient		{ 0.1f, 1.0f };
		tktkMath::Color		m_initDiffuse		{ 1.0f, 1.0f };
		tktkMath::Color		m_initSpeqular		{ 1.0f, 1.0f };
	};
}
#endif // !POINT_LIGHT_CONTROLLER_MAKER_H_