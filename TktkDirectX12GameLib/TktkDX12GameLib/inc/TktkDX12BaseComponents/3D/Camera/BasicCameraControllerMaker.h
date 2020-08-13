#ifndef BASIC_CAMERA_CONTROLLER_MAKER_H_
#define BASIC_CAMERA_CONTROLLER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BasicCameraController.h"

namespace tktk
{
	// 「BasicCameraController」を作るヘルパークラス
	class BasicCameraControllerMaker
	{
	private: /* プライベートコンストラクタ達 */

		BasicCameraControllerMaker() = default;
		BasicCameraControllerMaker(const BasicCameraControllerMaker& other) = default;
		BasicCameraControllerMaker& operator = (const BasicCameraControllerMaker& other) = default;
	
	public:

		// 作成開始
		static BasicCameraControllerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<BasicCameraController> create();

	public:  /* パラメータ設定関数 */

		// 使用する初期カメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, is_idType<IdType> = nullptr>
		BasicCameraControllerMaker& initCameraId(IdType value);

		// 初期カメラ射角を設定する
		BasicCameraControllerMaker& initCameraFov(float value);

		// 初期カメラアスペクト比を設定する
		BasicCameraControllerMaker& initCameraAspect(float value);

		// 初期近クリップ値を設定する
		BasicCameraControllerMaker& initCameraNear(float value);

		// 初期遠クリップ値を設定する
		BasicCameraControllerMaker& initCameraFar(float value);

	private: /* 各種id指定系の関数の実装 */

		BasicCameraControllerMaker& initCameraIdImpl(unsigned int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BasicCameraControllerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr	m_user{  };
		unsigned int	m_initCameraId	{ 0U };
		float			m_initCameraFov		{ 45.0f };
		float			m_initCameraAspect	{};	// デフォルトはゲームスクリーンの比率
		float			m_initCameraNear	{ 1.0f };
		float			m_initCameraFar		{ 100.0f };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, is_not_idType<IdType>>
		BasicCameraControllerMaker& initCameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 使用する初期カメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraId(IdType value)
	{
		return initCameraIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !BASIC_CAMERA_CONTROLLER_MAKER_H_