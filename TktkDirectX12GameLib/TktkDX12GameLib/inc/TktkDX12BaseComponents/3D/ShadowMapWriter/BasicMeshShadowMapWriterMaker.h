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

	public:

		// 作成完了
		ComponentPtr<BasicMeshShadowMapWriter> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		BasicMeshShadowMapWriterMaker& drawPriority(float value);

		// 使用するメッシュIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& meshId(IdType value);

		// 使用するスケルトンIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& skeletonId(IdType value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& cameraId(IdType value);

	private: /* 各種id指定系の関数の実装 */

		BasicMeshShadowMapWriterMaker& meshIdImpl(unsigned int value);
		BasicMeshShadowMapWriterMaker& skeletonIdImpl(unsigned int value);
		BasicMeshShadowMapWriterMaker& cameraIdImpl(unsigned int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BasicMeshShadowMapWriterMaker m_self;

	private: /* 変数達 */

		GameObjectPtr	m_user			{  };
		float			m_drawPriority	{ 0.0f };
		unsigned int	m_meshId		{ 0U };
		unsigned int	m_skeletonId	{ 0U };
		unsigned int	m_cameraId		{ 0U };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, is_not_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& meshId(IdType value) { static_assert(false, "MeshId Fraud Type"); }

		template<class IdType, is_not_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& skeletonId(IdType value) { static_assert(false, "SkeletonId Fraud Type"); }
	
		template<class IdType, is_not_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 使用するメッシュIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::meshId(IdType value)
	{
		return meshIdImpl(static_cast<unsigned int>(value));
	}

	// 使用するスケルトンIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::skeletonId(IdType value)
	{
		return skeletonIdImpl(static_cast<unsigned int>(value));
	}

	// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::cameraId(IdType value)
	{
		return cameraIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !BASIC_MESH_SHADOW_MAP_WRITER_MAKER_H_
