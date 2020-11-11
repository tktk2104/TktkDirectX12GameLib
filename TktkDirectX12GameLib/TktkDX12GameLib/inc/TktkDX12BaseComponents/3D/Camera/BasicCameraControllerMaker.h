#ifndef BASIC_CAMERA_CONTROLLER_MAKER_H_
#define BASIC_CAMERA_CONTROLLER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
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

		// 使用する初期カメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		BasicCameraControllerMaker& initCameraHandle(size_t value);

		// 使用する初期カメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		BasicCameraControllerMaker& initCameraId(ResourceIdCarrier value);

		// 初期カメラ射角を設定する
		BasicCameraControllerMaker& initCameraFov(float value);

		// 初期カメラアスペクト比を設定する
		BasicCameraControllerMaker& initCameraAspect(float value);

		// 初期近クリップ値を設定する
		BasicCameraControllerMaker& initCameraNear(float value);

		// 初期遠クリップ値を設定する
		BasicCameraControllerMaker& initCameraFar(float value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BasicCameraControllerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user				{  };
		size_t				m_initCameraHandle	{ 0U };
		float				m_initCameraFov		{ 45.0f };
		float				m_initCameraAspect	{};	// デフォルトはゲームスクリーンの比率
		float				m_initCameraNear	{ 1.0f };
		float				m_initCameraFar		{ 100.0f };
	};
}
#endif // !BASIC_CAMERA_CONTROLLER_MAKER_H_