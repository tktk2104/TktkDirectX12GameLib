#ifndef BOX_MESH_DRAWER_MAKER_H_
#define BOX_MESH_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BoxMeshDrawer.h"

namespace tktk
{
	// 「BoxMeshDrawer」を作るヘルパークラス
	class BoxMeshDrawerMaker
	{
	private: /* プライベートコンストラクタ達 */

		BoxMeshDrawerMaker() = default;
		BoxMeshDrawerMaker(const BoxMeshDrawerMaker& other) = default;
		BoxMeshDrawerMaker& operator = (const BoxMeshDrawerMaker& other) = default;

	public:

		// 作成開始
		static BoxMeshDrawerMaker& makeStart(GameObjectPtr user);


		// ステートを指定し、作成を開始する
		static BoxMeshDrawerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<BoxMeshDrawer> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		BoxMeshDrawerMaker& drawPriority(float value);

		// 立方体の大きさを設定する
		BoxMeshDrawerMaker& boxSize(const tktkMath::Vector3& value);

		// ローカル座標を設定する
		BoxMeshDrawerMaker& localPosition(const tktkMath::Vector3 & value);

		// 描画色を設定する
		BoxMeshDrawerMaker& albedoColor(const tktkMath::Color & value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		// ※初期パラメータはバックバッファー
		BoxMeshDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// 使用するカメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		BoxMeshDrawerMaker& cameraHandle(size_t value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		BoxMeshDrawerMaker& cameraId(ResourceIdCarrier value);

		// 使用するシャドウマップカメラハンドルを設定する
		// ※初期パラメータはデフォルトシャドウマップカメラ
		BoxMeshDrawerMaker& shadowMapCameraHandle(size_t value);

		// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		BoxMeshDrawerMaker& shadowMapCameraId(ResourceIdCarrier value);

		// 使用するライトハンドルを設定する
		// ※初期パラメータはデフォルトライト
		BoxMeshDrawerMaker& lightHandle(size_t value);

		// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトライト
		BoxMeshDrawerMaker& lightId(ResourceIdCarrier value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BoxMeshDrawerMaker m_self;

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
#endif // !BOX_MESH_DRAWER_MAKER_H_