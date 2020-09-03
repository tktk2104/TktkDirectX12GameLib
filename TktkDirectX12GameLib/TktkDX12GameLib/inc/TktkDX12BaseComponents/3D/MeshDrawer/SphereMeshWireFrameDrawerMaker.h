#ifndef SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_
#define SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "SphereMeshWireFrameDrawer.h"

namespace tktk
{
	// 「SphereMeshWireFrameDrawer」を作るヘルパークラス
	class SphereMeshWireFrameDrawerMaker
	{
	private: /* プライベートコンストラクタ達 */

		SphereMeshWireFrameDrawerMaker() = default;
		SphereMeshWireFrameDrawerMaker(const SphereMeshWireFrameDrawerMaker& other) = default;
		SphereMeshWireFrameDrawerMaker& operator = (const SphereMeshWireFrameDrawerMaker& other) = default;

	public:

		// 作成開始
		static SphereMeshWireFrameDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<SphereMeshWireFrameDrawer> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		SphereMeshWireFrameDrawerMaker& drawPriority(float value);

		// 半径を設定する
		SphereMeshWireFrameDrawerMaker& radius(float value);

		// ローカル座標を設定する
		SphereMeshWireFrameDrawerMaker& localPosition(const tktkMath::Vector3& value);

		// 描画色を設定する
		SphereMeshWireFrameDrawerMaker& albedoColor(const tktkMath::Color & value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		// ※初期パラメータはバックバッファー
		SphereMeshWireFrameDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// 使用するカメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		SphereMeshWireFrameDrawerMaker& cameraHandle(unsigned int value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		template<class IdType, is_idType<IdType> = nullptr>
		SphereMeshWireFrameDrawerMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

		// 使用するシャドウマップカメラハンドルを設定する
		// ※初期パラメータはデフォルトシャドウマップカメラ
		SphereMeshWireFrameDrawerMaker& shadowMapCameraHandle(unsigned int value);

		// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		template<class IdType, is_idType<IdType> = nullptr>
		SphereMeshWireFrameDrawerMaker& shadowMapCameraId(IdType value) { return shadowMapCameraIdImpl(static_cast<int>(value)); }

		// 使用するライトハンドルを設定する
		SphereMeshWireFrameDrawerMaker& lightHandle(unsigned int value);

		// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		template<class IdType, is_idType<IdType> = nullptr>
		SphereMeshWireFrameDrawerMaker& lightId(IdType value) { return lightIdImpl(static_cast<int>(value)); }

	private: /* 各種id指定系の関数の実装 */

		SphereMeshWireFrameDrawerMaker& cameraIdImpl(int value);
		SphereMeshWireFrameDrawerMaker& shadowMapCameraIdImpl(int value);
		SphereMeshWireFrameDrawerMaker& lightIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static SphereMeshWireFrameDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr						m_user				{  };
		float								m_drawPriority		{ 0.0f };
		float								m_radius			{ 0.5f };
		tktkMath::Vector3					m_localPosition		{ tktkMath::Vector3_v::zero };
		tktkMath::Color						m_albedoColor		{ tktkMath::Color_v::white };
		SphereMeshDrawerUseResourceHandles	m_useResourceHandles{  };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, is_not_idType<IdType> = nullptr>
		SphereMeshWireFrameDrawerMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, is_not_idType<IdType> = nullptr>
		SphereMeshWireFrameDrawerMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, is_not_idType<IdType> = nullptr>
		SphereMeshWireFrameDrawerMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
}
#endif // !SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_