#ifndef BASIC_MESH_SHADOW_MAP_WRITER_MAKER_H_
#define BASIC_MESH_SHADOW_MAP_WRITER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BasicMeshShadowMapWriter.h"

namespace tktk
{
	// 「BasicMeshShadowMapWriter」を作るヘルパークラス
	class BasicMeshShadowMapWriterMaker
	{
	private: /* プライベートコンストラクタ達 */

		BasicMeshShadowMapWriterMaker() = default;
		BasicMeshShadowMapWriterMaker(const BasicMeshShadowMapWriterMaker& other) = default;
		BasicMeshShadowMapWriterMaker& operator = (const BasicMeshShadowMapWriterMaker& other) = default;

	public:

		// 作成開始
		static BasicMeshShadowMapWriterMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		static BasicMeshShadowMapWriterMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<BasicMeshShadowMapWriter> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		BasicMeshShadowMapWriterMaker& drawPriority(float value);

		// 基本のスケールを設定する
		BasicMeshShadowMapWriterMaker& baseScale(const tktkMath::Vector3& value);

		// 基本の回転を設定する
		BasicMeshShadowMapWriterMaker& baseRotation(const tktkMath::Quaternion& value);

		// 使用するメッシュIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		BasicMeshShadowMapWriterMaker& meshId(ResourceIdCarrier value);

		// 使用するスケルトンIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		BasicMeshShadowMapWriterMaker& skeletonId(ResourceIdCarrier value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		BasicMeshShadowMapWriterMaker& cameraId(ResourceIdCarrier value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BasicMeshShadowMapWriterMaker m_self;

	private: /* 変数達 */

		GameObjectPtr			m_user			{  };
		StateTypeHierarchy		m_targetState	{  };
		float					m_drawPriority	{ 0.0f };
		tktkMath::Vector3		m_baseScale{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion	m_baseRotation{ tktkMath::Quaternion_v::identity };
		size_t					m_meshHandle	{ 0U };
		size_t					m_skeletonHandle{ 0U };
		size_t					m_cameraHandle	{ 0U };
	};
}
#endif // !BASIC_MESH_SHADOW_MAP_WRITER_MAKER_H_
