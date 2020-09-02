#ifndef BASIC_MESH_DRAWER_MAKER_H_
#define BASIC_MESH_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BasicMeshDrawer.h"

namespace tktk
{
	// 「BasicMeshDrawer」を作るヘルパークラス
	class BasicMeshDrawerMaker
	{
	private: /* プライベートコンストラクタ達 */

		BasicMeshDrawerMaker() = default;
		BasicMeshDrawerMaker(const BasicMeshDrawerMaker& other) = default;
		BasicMeshDrawerMaker& operator = (const BasicMeshDrawerMaker& other) = default;

	public:

		// 作成開始
		static BasicMeshDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<BasicMeshDrawer> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		BasicMeshDrawerMaker& drawPriority(float value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		BasicMeshDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// 使用するメッシュハンドルを設定する
		BasicMeshDrawerMaker& meshHandle(unsigned int value);

		// 使用するメッシュIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshDrawerMaker& meshId(IdType value) { return meshIdImpl(static_cast<int>(value)); }

		// 使用するスケルトンのリソースハンドルを設定する
		BasicMeshDrawerMaker& skeletonHandle(unsigned int value);

		// 使用するスケルトンのリソースIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshDrawerMaker& skeletonId(IdType value) { return skeletonIdImpl(static_cast<int>(value)); }

		// 使用するカメラハンドルを設定する
		BasicMeshDrawerMaker& cameraHandle(unsigned int value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshDrawerMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

		// 使用するシャドウマップカメラハンドルを設定する
		BasicMeshDrawerMaker& shadowMapCameraHandle(unsigned int value);

		// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshDrawerMaker& shadowMapCameraId(IdType value) { return shadowMapCameraIdImpl(static_cast<int>(value)); }

		// 使用するライトハンドルを設定する
		BasicMeshDrawerMaker& lightHandle(unsigned int value);

		// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		template<class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		BasicMeshDrawerMaker& lightId(IdType value) { return lightIdImpl(static_cast<int>(value)); }

	private: /* 各種id指定系の関数の実装 */

		BasicMeshDrawerMaker& meshIdImpl(int value);
		BasicMeshDrawerMaker& skeletonIdImpl(int value);
		BasicMeshDrawerMaker& cameraIdImpl(int value);
		BasicMeshDrawerMaker& shadowMapCameraIdImpl(int value);
		BasicMeshDrawerMaker& lightIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BasicMeshDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr						m_user				{  };
		float								m_drawPriority		{ 0.0f };	
		BasicMeshDrawerUseResourceHandles	m_useResourceHandles{  }; // ※「RtvDescriptorHeap」の初期パラメータはバックバッファー

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BasicMeshDrawerMaker& meshId(IdType value) { static_assert(false, "MeshId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BasicMeshDrawerMaker& skeletonId(IdType value) { static_assert(false, "SkeletonId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BasicMeshDrawerMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BasicMeshDrawerMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BasicMeshDrawerMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
}
#endif // !BASIC_MESH_DRAWER_MAKER_H_