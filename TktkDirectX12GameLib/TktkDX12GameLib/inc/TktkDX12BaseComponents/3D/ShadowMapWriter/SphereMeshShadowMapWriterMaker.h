#ifndef SPHERE_MESH_SHADOW_MAP_WRITER_MAKER_H_
#define SPHERE_MESH_SHADOW_MAP_WRITER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "SphereMeshShadowMapWriter.h"

namespace tktk
{
	// 「SphereMeshShadowMapWriter」を作るヘルパークラス
	class SphereMeshShadowMapWriterMaker
	{
	private: /* プライベートコンストラクタ達 */

		SphereMeshShadowMapWriterMaker() = default;
		SphereMeshShadowMapWriterMaker(const SphereMeshShadowMapWriterMaker& other) = default;
		SphereMeshShadowMapWriterMaker& operator = (const SphereMeshShadowMapWriterMaker& other) = default;

	public:

		// 作成開始
		static SphereMeshShadowMapWriterMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<SphereMeshShadowMapWriter> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		SphereMeshShadowMapWriterMaker& drawPriority(float value);

		// 半径を設定する
		SphereMeshShadowMapWriterMaker& radius(float value);

		// ローカル座標を設定する
		SphereMeshShadowMapWriterMaker& localPosition(const tktkMath::Vector3& value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		template<class IdType, is_idType<IdType> = nullptr>
		SphereMeshShadowMapWriterMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

	private: /* 各種id指定系の関数の実装 */

		SphereMeshShadowMapWriterMaker& cameraIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static SphereMeshShadowMapWriterMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user			{  };
		float				m_drawPriority	{ 0.0f };
		float				m_radius		{ 0.5f };
		tktkMath::Vector3	m_localPosition	{ tktkMath::Vector3_v::zero };
		unsigned int		m_cameraHandle	{ 0U };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, is_not_idType<IdType> = nullptr>
		SphereMeshShadowMapWriterMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }
	};
}
#endif // !SPHERE_MESH_SHADOW_MAP_WRITER_MAKER_H_