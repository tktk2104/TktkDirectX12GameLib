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
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		static BasicMeshShadowMapWriterMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

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
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& meshId(IdType value) { return meshIdImpl(static_cast<int>(value)); }

		// 使用するスケルトンIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& skeletonId(IdType value) { return skeletonIdImpl(static_cast<int>(value)); }

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		template<class IdType, is_idType<IdType> = nullptr>
		BasicMeshShadowMapWriterMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

	private: /* 各種id指定系の関数の実装 */

		BasicMeshShadowMapWriterMaker& meshIdImpl(int value);
		BasicMeshShadowMapWriterMaker& skeletonIdImpl(int value);
		BasicMeshShadowMapWriterMaker& cameraIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BasicMeshShadowMapWriterMaker m_self;

	private: /* 変数達 */

		GameObjectPtr			m_user			{  };
		std::vector<int>		m_targetState	{  };
		float					m_drawPriority	{ 0.0f };
		tktkMath::Vector3		m_baseScale{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion	m_baseRotation{ tktkMath::Quaternion_v::identity };
		unsigned int			m_meshHandle	{ 0U };
		unsigned int			m_skeletonHandle{ 0U };
		unsigned int			m_cameraHandle	{ 0U };
		

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

	// ステートを指定し、作成を開始する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加
	template<class StateIdType>
	inline BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
	{
		// 作成開始処理を行う
		auto& result = makeStart(user);

		// 初期化子リストを配列に変換
		auto targetStateArray = std::vector<StateIdType>(targetState);

		// 対象のステートの階層数分のメモリを確保
		result.m_targetState.reserve(targetStateArray.size());

		// 対象のステートの階層を設定する
		for (const auto& node : targetStateArray) result.m_targetState.push_back(static_cast<int>(node));

		// 自身の参照を返す
		return result;
	}
}
#endif // !BASIC_MESH_SHADOW_MAP_WRITER_MAKER_H_
