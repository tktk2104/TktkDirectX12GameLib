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
		BoxMeshWireFrameDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// 使用するカメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		BoxMeshWireFrameDrawerMaker& cameraHandle(unsigned int value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		template<class IdType, is_idType<IdType> = nullptr>
		BoxMeshWireFrameDrawerMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

		// 使用するシャドウマップカメラハンドルを設定する
		// ※初期パラメータはデフォルトシャドウマップカメラ
		BoxMeshWireFrameDrawerMaker& shadowMapCameraHandle(unsigned int value);

		// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		template<class IdType, is_idType<IdType> = nullptr>
		BoxMeshWireFrameDrawerMaker& shadowMapCameraId(IdType value) { return shadowMapCameraIdImpl(static_cast<int>(value)); }

		// 使用するライトハンドルを設定する
		// ※初期パラメータはデフォルトライト
		BoxMeshWireFrameDrawerMaker& lightHandle(unsigned int value);

		// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトライト
		template<class IdType, is_idType<IdType> = nullptr>
		BoxMeshWireFrameDrawerMaker& lightId(IdType value) { return lightIdImpl(static_cast<int>(value)); }

	private: /* 各種id指定系の関数の実装 */

		BoxMeshWireFrameDrawerMaker& cameraIdImpl(int value);
		BoxMeshWireFrameDrawerMaker& shadowMapCameraIdImpl(int value);
		BoxMeshWireFrameDrawerMaker& lightIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BoxMeshWireFrameDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr						m_user				{  };
		StateTypeHierarchy						m_targetState		{  };
		float								m_drawPriority		{ 0.0f };
		tktkMath::Vector3					m_boxSize			{ tktkMath::Vector3_v::one };
		tktkMath::Vector3					m_localPosition		{ tktkMath::Vector3_v::zero };
		tktkMath::Color						m_albedoColor		{ tktkMath::Color_v::white };
		BoxMeshDrawerUseResourceHandles		m_useResourceHandles{  };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BoxMeshWireFrameDrawerMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BoxMeshWireFrameDrawerMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BoxMeshWireFrameDrawerMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
}
#endif // !BOX_MESH_WIRE_FRAME_DRAWER_MAKER_H_