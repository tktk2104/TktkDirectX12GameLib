#ifndef SPHERE_MESH_DRAWER_MAKER_H_
#define SPHERE_MESH_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "SphereMeshDrawer.h"

namespace tktk
{
	// 「SphereMeshDrawer」を作るヘルパークラス
	class SphereMeshDrawerMaker
	{
	private: /* プライベートコンストラクタ達 */

		SphereMeshDrawerMaker() = default;
		SphereMeshDrawerMaker(const SphereMeshDrawerMaker& other) = default;
		SphereMeshDrawerMaker& operator = (const SphereMeshDrawerMaker& other) = default;

	public:

		// 作成開始
		static SphereMeshDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<SphereMeshDrawer> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		SphereMeshDrawerMaker& drawPriority(float value);

		// 半径を設定する
		SphereMeshDrawerMaker& radius(float value);

		// ローカル座標を設定する
		SphereMeshDrawerMaker& localPosition(const tktkMath::Vector3& value);

		// 描画色を設定する
		SphereMeshDrawerMaker& albedoColor(const tktkMath::Color&  value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		// ※初期パラメータはバックバッファー
		SphereMeshDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// 使用するカメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		SphereMeshDrawerMaker& cameraHandle(unsigned int value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		template<class IdType, is_idType<IdType> = nullptr>
		SphereMeshDrawerMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

		// 使用するシャドウマップカメラハンドルを設定する
		// ※初期パラメータはデフォルトシャドウマップカメラ
		SphereMeshDrawerMaker& shadowMapCameraHandle(unsigned int value);

		// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		template<class IdType, is_idType<IdType> = nullptr>
		SphereMeshDrawerMaker& shadowMapCameraId(IdType value) { return shadowMapCameraIdImpl(static_cast<int>(value)); }

		// 使用するライトハンドルを設定する
		SphereMeshDrawerMaker& lightHandle(unsigned int value);

		// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		template<class IdType, is_idType<IdType> = nullptr>
		SphereMeshDrawerMaker& lightId(IdType value) { return lightIdImpl(static_cast<int>(value)); }

	private: /* 各種id指定系の関数の実装 */

		SphereMeshDrawerMaker& cameraIdImpl(int value);
		SphereMeshDrawerMaker& shadowMapCameraIdImpl(int value);
		SphereMeshDrawerMaker& lightIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static SphereMeshDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr						m_user				{  };
		float								m_drawPriority		{ 0.0f };
		float								m_radius			{ 0.5f };
		tktkMath::Vector3					m_localPosition		{ tktkMath::Vector3_v::zero };
		tktkMath::Color						m_albedoColor		{ tktkMath::Color_v::white };
		SphereMeshDrawerUseResourceHandles	m_useResourceHandles{  };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshDrawerMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshDrawerMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshDrawerMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
}
#endif // !SPHERE_MESH_DRAWER_MAKER_H_