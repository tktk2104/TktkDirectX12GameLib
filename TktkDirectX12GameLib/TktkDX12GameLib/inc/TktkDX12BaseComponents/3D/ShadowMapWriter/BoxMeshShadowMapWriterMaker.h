#ifndef BOX_MESH_SHADOW_MAP_WRITER_MAKER_H_
#define BOX_MESH_SHADOW_MAP_WRITER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BoxMeshShadowMapWriter.h"

namespace tktk
{
	// 「BoxMeshShadowMapWriter」を作るヘルパークラス
	class BoxMeshShadowMapWriterMaker
	{
	private: /* プライベートコンストラクタ達 */

		BoxMeshShadowMapWriterMaker() = default;
		BoxMeshShadowMapWriterMaker(const BoxMeshShadowMapWriterMaker& other) = default;
		BoxMeshShadowMapWriterMaker& operator = (const BoxMeshShadowMapWriterMaker& other) = default;

	public:

		// 作成開始
		static BoxMeshShadowMapWriterMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		static BoxMeshShadowMapWriterMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<BoxMeshShadowMapWriter> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		BoxMeshShadowMapWriterMaker& drawPriority(float value);

		// 立方体の大きさを設定する
		BoxMeshShadowMapWriterMaker& boxSize(const tktkMath::Vector3& value);

		// ローカル座標を設定する
		BoxMeshShadowMapWriterMaker& localPosition(const tktkMath::Vector3 & value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		template<class IdType, is_idType<IdType> = nullptr>
		BoxMeshShadowMapWriterMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

	private: /* 各種id指定系の関数の実装 */

		BoxMeshShadowMapWriterMaker& cameraIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static BoxMeshShadowMapWriterMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user			{  };
		std::vector<int>	m_targetState	{  };
		float				m_drawPriority	{ 0.0f };
		tktkMath::Vector3	m_boxSize		{ tktkMath::Vector3_v::zero };
		tktkMath::Vector3	m_localPosition	{ tktkMath::Vector3_v::zero };
		unsigned int		m_cameraHandle	{ 0U };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, is_not_idType<IdType> = nullptr>
		BoxMeshShadowMapWriterMaker& cameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// ステートを指定し、作成を開始する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline BoxMeshShadowMapWriterMaker& BoxMeshShadowMapWriterMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !BOX_MESH_SHADOW_MAP_WRITER_MAKER_H_