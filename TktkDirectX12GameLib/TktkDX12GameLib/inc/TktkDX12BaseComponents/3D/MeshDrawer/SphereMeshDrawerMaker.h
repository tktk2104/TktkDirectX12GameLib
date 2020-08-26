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

		// 描画色を設定する
		SphereMeshDrawerMaker& albedoColor(const tktkMath::Color&  value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		SphereMeshDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, is_idType<IdType> = nullptr>
		SphereMeshDrawerMaker& cameraId(IdType value);

		// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, is_idType<IdType> = nullptr>
		SphereMeshDrawerMaker& shadowMapCameraId(IdType value);

		// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, is_idType<IdType> = nullptr>
		SphereMeshDrawerMaker& lightId(IdType value);

	private: /* 各種id指定系の関数の実装 */

		SphereMeshDrawerMaker& cameraIdImpl(unsigned int value);
		SphereMeshDrawerMaker& shadowMapCameraIdImpl(unsigned int value);
		SphereMeshDrawerMaker& lightIdImpl(unsigned int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static SphereMeshDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr	m_user{  };
		float			m_drawPriority{ 0.0f };
		float			m_radius{ 0.5f };
		tktkMath::Color	m_albedoColor{ tktkMath::colorWhite };
		unsigned int	m_useRtvDescriptorHeapHandle{  };		// ※初期パラメータはバックバッファー
		unsigned int	m_cameraId{ 0U };
		unsigned int	m_shadowMapCameraId{ 0U };
		unsigned int	m_lightId{ 0U };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshDrawerMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshDrawerMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SphereMeshDrawerMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline SphereMeshDrawerMaker& SphereMeshDrawerMaker::cameraId(IdType value)
	{
		return cameraIdImpl(static_cast<unsigned int>(value));
	}

	// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline SphereMeshDrawerMaker& SphereMeshDrawerMaker::shadowMapCameraId(IdType value)
	{
		return shadowMapCameraIdImpl(static_cast<unsigned int>(value));
	}

	// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline SphereMeshDrawerMaker& SphereMeshDrawerMaker::lightId(IdType value)
	{
		return lightIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !SPHERE_MESH_DRAWER_MAKER_H_