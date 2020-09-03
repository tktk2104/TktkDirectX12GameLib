#ifndef COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_
#define COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "ColliderWireFrameDrawer3D.h"

namespace tktk
{
	// 「ColliderWireFrameDrawer3D」のインスタンスを作成するクラス
	class ColliderWireFrameDrawer3DMaker
	{
	private:  /* プライベートコンストラクタ達 */

		ColliderWireFrameDrawer3DMaker() = default;
		ColliderWireFrameDrawer3DMaker(const ColliderWireFrameDrawer3DMaker& other) = default;
		ColliderWireFrameDrawer3DMaker& operator = (const ColliderWireFrameDrawer3DMaker& other) = default;

	public:

		// 作成開始
		static ColliderWireFrameDrawer3DMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<ColliderWireFrameDrawer3D> create();

		// 描画優先度を設定する
		ColliderWireFrameDrawer3DMaker& drawPriority(float value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		ColliderWireFrameDrawer3DMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// 使用するカメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		ColliderWireFrameDrawer3DMaker& cameraHandle(unsigned int value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		template<class IdType, is_idType<IdType> = nullptr>
		ColliderWireFrameDrawer3DMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

		// 使用するシャドウマップカメラハンドルを設定する
		// ※初期パラメータはデフォルトシャドウマップカメラ
		ColliderWireFrameDrawer3DMaker& shadowMapCameraHandle(unsigned int value);

		// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		template<class IdType, is_idType<IdType> = nullptr>
		ColliderWireFrameDrawer3DMaker& shadowMapCameraId(IdType value) { return shadowMapCameraIdImpl(static_cast<int>(value)); }

		// 使用するライトハンドルを設定する
		// ※初期パラメータはデフォルトライト
		ColliderWireFrameDrawer3DMaker& lightHandle(unsigned int value);

		// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトライト
		template<class IdType, is_idType<IdType> = nullptr>
		ColliderWireFrameDrawer3DMaker& lightId(IdType value) { return lightIdImpl(static_cast<int>(value)); }

		// 線の色を設定する
		ColliderWireFrameDrawer3DMaker& lineColor(const tktkMath::Color & value);

	private: /* 各種id指定系の関数の実装 */

		ColliderWireFrameDrawer3DMaker& cameraIdImpl(int value);
		ColliderWireFrameDrawer3DMaker& shadowMapCameraIdImpl(int value);
		ColliderWireFrameDrawer3DMaker& lightIdImpl(int value);

	private:

		static ColliderWireFrameDrawer3DMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr						m_user				{ };
		float								m_drawPriority		{ 0.0f };
		tktkMath::Color						m_lineColor			{ tktkMath::Color_v::white };
		SphereMeshDrawerUseResourceHandles	m_useResourceHandles{  }; // ※「RtvDescriptorHeap」の初期パラメータはバックバッファー
	
	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, is_not_idType<IdType> = nullptr>
		ColliderWireFrameDrawer3DMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }

		template<class IdType, is_not_idType<IdType> = nullptr>
		ColliderWireFrameDrawer3DMaker& shadowMapCameraId(IdType value) { static_assert(false, "ShadowMapCameraId Fraud Type"); }

		template<class IdType, is_not_idType<IdType> = nullptr>
		ColliderWireFrameDrawer3DMaker& lightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
}

#endif // !COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_