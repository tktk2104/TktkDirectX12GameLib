#ifndef BOX_MESH_WIRE_FRAME_DRAWER_MAKER_H_
#define BOX_MESH_WIRE_FRAME_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BoxMeshWireFrameDrawer.h"

namespace tktk
{
	// 「BoxMeshWireFrameDrawer」を作るヘルパークラス
	class BoxMeshWireFrameDrawerMaker
	{
	private: /* プライベートコンストラクタ達 */

		BoxMeshWireFrameDrawerMaker() = default;
		BoxMeshWireFrameDrawerMaker(const BoxMeshWireFrameDrawerMaker& other) = default;
		BoxMeshWireFrameDrawerMaker& operator = (const BoxMeshWireFrameDrawerMaker& other) = default;

	public:

		// 作成開始
		static BoxMeshWireFrameDrawerMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		static BoxMeshWireFrameDrawerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<BoxMeshWireFrameDrawer> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		BoxMeshWireFrameDrawerMaker& drawPriority(float value);

		// 立方体の大きさを設定する
		BoxMeshWireFrameDrawerMaker& boxSize(const tktkMath::Vector3 & value);

		// ローカル座標を設定する
		BoxMeshWireFrameDrawerMaker& localPosition(const tktkMath::Vector3 & value);

		// 描画色を設定する
		BoxMeshWireFrameDrawerMaker& albedoColor(const tktkMath::Color & value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		// ※初期パラメータはバックバッファー
		BoxMeshWireFrameDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// 使用するカメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		BoxMeshWireFrameDrawerMaker& cameraHandle(size_t value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		BoxMeshWireFrameDrawerMaker& cameraId(ResourceIdCarrier value);

		// 使用するシャドウマップカメラハンドルを設定する
		// ※初期パラメータはデフォルトシャドウマップカメラ
		BoxMeshWireFrameDrawerMaker& shadowMapCameraHandle(size_t value);

		// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		BoxMeshWireFrameDrawerMaker& shadowMapCameraId(ResourceIdCarrier value);

		// 使用するライトハンドルを設定する
		// ※初期パラメータはデフォルトライト
		BoxMeshWireFrameDrawerMaker& lightHandle(size_t value);

		// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトライト
		BoxMeshWireFrameDrawerMaker& lightId(ResourceIdCarrier value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BoxMeshWireFrameDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr						m_user				{  };
		StateTypeHierarchy					m_targetState		{  };
		float								m_drawPriority		{ 0.0f };
		tktkMath::Vector3					m_boxSize			{ tktkMath::Vector3_v::one };
		tktkMath::Vector3					m_localPosition		{ tktkMath::Vector3_v::zero };
		tktkMath::Color						m_albedoColor		{ tktkMath::Color_v::white };
		BoxMeshDrawerUseResourceHandles		m_useResourceHandles{  };
	};
}
#endif // !BOX_MESH_WIRE_FRAME_DRAWER_MAKER_H_