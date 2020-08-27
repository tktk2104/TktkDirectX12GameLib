#ifndef ORTHOGRAPHIC_CAMERA_CONTROLLER_MAKER_H_
#define ORTHOGRAPHIC_CAMERA_CONTROLLER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "OrthographicCameraController.h"

namespace tktk
{
	// 「OrthographicCameraController」を作るヘルパークラス
	class OrthographicCameraControllerMaker
	{
	private: /* プライベートコンストラクタ達 */

		OrthographicCameraControllerMaker() = default;
		OrthographicCameraControllerMaker(const OrthographicCameraControllerMaker& other) = default;
		OrthographicCameraControllerMaker& operator = (const OrthographicCameraControllerMaker& other) = default;

	public:

		// 作成開始
		static OrthographicCameraControllerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<OrthographicCameraController> create();

	public:  /* パラメータ設定関数 */

		// 使用する初期カメラハンドルを設定する
		OrthographicCameraControllerMaker& initCameraHandle(unsigned int value);

		// 使用する初期カメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		template<class IdType, is_idType<IdType> = nullptr>
		OrthographicCameraControllerMaker& initCameraId(IdType value);

		// 初期カメラ横範囲を設定する
		OrthographicCameraControllerMaker& initCameraWidth(float value);

		// 初期カメラ縦範囲を設定する
		OrthographicCameraControllerMaker& initCameraHeight(float value);

		// 初期近クリップ値を設定する
		OrthographicCameraControllerMaker& initCameraNear(float value);

		// 初期遠クリップ値を設定する
		OrthographicCameraControllerMaker& initCameraFar(float value);

	private: /* 各種id指定系の関数の実装 */

		OrthographicCameraControllerMaker& initCameraIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static OrthographicCameraControllerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr	m_user				{  };
		unsigned int	m_initCameraHandle	{ 0U };
		float			m_initCameraWidth	{ 100.0f };
		float			m_initCameraHeight	{ 100.0f };
		float			m_initCameraNear	{ 1.0f };
		float			m_initCameraFar		{ 100.0f };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		OrthographicCameraControllerMaker& initCameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 使用する初期カメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraId(IdType value)
	{
		return initCameraIdImpl(static_cast<int>(value));
	}
}
#endif // !ORTHOGRAPHIC_CAMERA_CONTROLLER_MAKER_H_