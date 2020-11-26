#ifndef SHADOW_MAP_CAMERA_CONTROLLER_MAKER_H_
#define SHADOW_MAP_CAMERA_CONTROLLER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "ShadowMapCameraController.h"

namespace tktk
{
	// 「ShadowMapCameraController」を作るヘルパークラス
	class ShadowMapCameraControllerMaker
	{
	private: /* プライベートコンストラクタ達 */

		ShadowMapCameraControllerMaker() = default;
		ShadowMapCameraControllerMaker(const ShadowMapCameraControllerMaker& other) = default;
		ShadowMapCameraControllerMaker& operator = (const ShadowMapCameraControllerMaker& other) = default;

	public:

		// 作成開始
		static ShadowMapCameraControllerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<ShadowMapCameraController> create();

	public:  /* パラメータ設定関数 */

		// 使用する初期カメラハンドルを設定する
		// ※初期パラメータはデフォルトシャドウマップカメラ
		ShadowMapCameraControllerMaker& initCameraHandle(size_t value);

		// 使用する初期カメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		ShadowMapCameraControllerMaker& initCameraId(ResourceIdCarrier value);

		// カメラの向く相手のタグを設定する
		ShadowMapCameraControllerMaker& targetTag(GameObjectTagCarrier value);

		// カメラ角度を設定する
		ShadowMapCameraControllerMaker& direction(const tktkMath::Vector3& value);

		// 初期カメラ横範囲を設定する
		ShadowMapCameraControllerMaker& initCameraWidth(float value);

		// 初期カメラ縦範囲を設定する
		ShadowMapCameraControllerMaker& initCameraHeight(float value);

		// 初期近クリップ値を設定する
		ShadowMapCameraControllerMaker& initCameraNear(float value);

		// 初期遠クリップ値を設定する
		ShadowMapCameraControllerMaker& initCameraFar(float value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static ShadowMapCameraControllerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr			m_user				{  };
		size_t					m_initCameraHandle	{ 0U };
		GameObjectTagCarrier	m_targetTag			{ -1 };
		tktkMath::Vector3		m_direction			{ tktkMath::Vector3_v::forwardLH };
		float					m_initCameraWidth	{ 100.0f };
		float					m_initCameraHeight	{ 100.0f };
		float					m_initCameraNear	{ 1.0f };
		float					m_initCameraFar		{ 100.0f };
	};
}
#endif // !SHADOW_MAP_CAMERA_CONTROLLER_MAKER_H_