#ifndef SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_
#define SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
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
		SphereMeshWireFrameDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// 使用するカメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		SphereMeshWireFrameDrawerMaker& cameraHandle(size_t value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		SphereMeshWireFrameDrawerMaker& cameraId(ResourceIdCarrier value);

		// 使用するシャドウマップカメラハンドルを設定する
		// ※初期パラメータはデフォルトシャドウマップカメラ
		SphereMeshWireFrameDrawerMaker& shadowMapCameraHandle(size_t value);

		// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		SphereMeshWireFrameDrawerMaker& shadowMapCameraId(ResourceIdCarrier value);

		// 使用するライトハンドルを設定する
		// ※初期パラメータはデフォルトライト
		SphereMeshWireFrameDrawerMaker& lightHandle(size_t value);

		// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトライト
		SphereMeshWireFrameDrawerMaker& lightId(ResourceIdCarrier value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static SphereMeshWireFrameDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr						m_user				{  };
		float								m_drawPriority		{ 0.0f };
		float								m_radius			{ 0.5f };
		tktkMath::Vector3					m_localPosition		{ tktkMath::Vector3_v::zero };
		tktkMath::Color						m_albedoColor		{ tktkMath::Color_v::white };
		SphereMeshDrawerUseResourceHandles	m_useResourceHandles{  };
	};
}
#endif // !SPHERE_MESH_WIRE_FRAME_DRAWER_MAKER_H_