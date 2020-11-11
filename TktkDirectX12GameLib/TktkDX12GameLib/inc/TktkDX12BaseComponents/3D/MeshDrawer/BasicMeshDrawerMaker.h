#ifndef BASIC_MESH_DRAWER_MAKER_H_
#define BASIC_MESH_DRAWER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
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

		// 基本のスケールを設定する
		BasicMeshDrawerMaker& baseScale(const tktkMath::Vector3& value);

		// 基本の回転を設定する
		BasicMeshDrawerMaker& baseRotation(const tktkMath::Quaternion& value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		// ※初期パラメータはバックバッファー
		BasicMeshDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// 使用するメッシュハンドルを設定する
		BasicMeshDrawerMaker& meshHandle(size_t value);

		// 使用するメッシュIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		BasicMeshDrawerMaker& meshId(ResourceIdCarrier value);

		// 使用するスケルトンのリソースハンドルを設定する
		BasicMeshDrawerMaker& skeletonHandle(size_t value);

		// 使用するスケルトンのリソースIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		BasicMeshDrawerMaker& skeletonId(ResourceIdCarrier value);

		// 使用するカメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		BasicMeshDrawerMaker& cameraHandle(size_t value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		BasicMeshDrawerMaker& cameraId(ResourceIdCarrier value);

		// 使用するシャドウマップカメラハンドルを設定する
		// ※初期パラメータはデフォルトシャドウマップカメラ
		BasicMeshDrawerMaker& shadowMapCameraHandle(size_t value);

		// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		BasicMeshDrawerMaker& shadowMapCameraId(ResourceIdCarrier value);

		// 使用するライトハンドルを設定する
		// ※初期パラメータはデフォルトライト
		BasicMeshDrawerMaker& lightHandle(size_t value);

		// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトライト
		BasicMeshDrawerMaker& lightId(ResourceIdCarrier value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BasicMeshDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr						m_user				{  };
		float								m_drawPriority		{ 0.0f };
		tktkMath::Vector3					m_baseScale			{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion				m_baseRotation		{ tktkMath::Quaternion_v::identity };
		BasicMeshDrawerUseResourceHandles	m_useResourceHandles{  };
	};
}
#endif // !BASIC_MESH_DRAWER_MAKER_H_