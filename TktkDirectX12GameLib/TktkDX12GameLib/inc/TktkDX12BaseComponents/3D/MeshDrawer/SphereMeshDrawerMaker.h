#ifndef SPHERE_MESH_DRAWER_MAKER_H_
#define SPHERE_MESH_DRAWER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
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
		SphereMeshDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// 使用するカメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		SphereMeshDrawerMaker& cameraHandle(size_t value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		SphereMeshDrawerMaker& cameraId(ResourceIdCarrier value);

		// 使用するシャドウマップカメラハンドルを設定する
		// ※初期パラメータはデフォルトシャドウマップカメラ
		SphereMeshDrawerMaker& shadowMapCameraHandle(size_t value);

		// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		SphereMeshDrawerMaker& shadowMapCameraId(ResourceIdCarrier value);

		// 使用するライトハンドルを設定する
		// ※初期パラメータはデフォルトライト
		SphereMeshDrawerMaker& lightHandle(size_t value);

		// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトライト
		SphereMeshDrawerMaker& lightId(ResourceIdCarrier value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static SphereMeshDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr						m_user				{  };
		float								m_drawPriority		{ 0.0f };
		float								m_radius			{ 0.5f };
		tktkMath::Vector3					m_localPosition		{ tktkMath::Vector3_v::zero };
		tktkMath::Color						m_albedoColor		{ tktkMath::Color_v::white };
		SphereMeshDrawerUseResourceHandles	m_useResourceHandles{  };
	};
}
#endif // !SPHERE_MESH_DRAWER_MAKER_H_