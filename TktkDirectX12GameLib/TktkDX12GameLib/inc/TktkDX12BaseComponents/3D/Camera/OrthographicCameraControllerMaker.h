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

		// ステートを指定し、作成を開始する
		static OrthographicCameraControllerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<OrthographicCameraController> create();

	public:  /* パラメータ設定関数 */

		// 使用する初期カメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		OrthographicCameraControllerMaker& initCameraHandle(size_t value);

		// 使用する初期カメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		OrthographicCameraControllerMaker& initCameraId(ResourceIdCarrier value);

		// 初期カメラ横範囲を設定する
		OrthographicCameraControllerMaker& initCameraWidth(float value);

		// 初期カメラ縦範囲を設定する
		OrthographicCameraControllerMaker& initCameraHeight(float value);

		// 初期近クリップ値を設定する
		OrthographicCameraControllerMaker& initCameraNear(float value);

		// 初期遠クリップ値を設定する
		OrthographicCameraControllerMaker& initCameraFar(float value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static OrthographicCameraControllerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user				{  };
		StateTypeHierarchy	m_targetState		{  };
		size_t				m_initCameraHandle	{ 0U };
		float				m_initCameraWidth	{ 100.0f };
		float				m_initCameraHeight	{ 100.0f };
		float				m_initCameraNear	{ 1.0f };
		float				m_initCameraFar		{ 100.0f };
	};
}
#endif // !ORTHOGRAPHIC_CAMERA_CONTROLLER_MAKER_H_