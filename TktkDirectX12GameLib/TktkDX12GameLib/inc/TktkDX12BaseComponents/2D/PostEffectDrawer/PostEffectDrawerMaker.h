#ifndef POST_EFFECT_DRAWER_MAKER_H_
#define POST_EFFECT_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "PostEffectDrawer.h"

namespace tktk
{
	// 「PostEffectDrawer」を作るヘルパークラス
	class PostEffectDrawerMaker
	{
	private: /* プライベートコンストラクタ達 */

		PostEffectDrawerMaker() = default;
		PostEffectDrawerMaker(const PostEffectDrawerMaker& other) = default;
		PostEffectDrawerMaker& operator = (const PostEffectDrawerMaker& other) = default;

	public:

		// 作成開始
		static PostEffectDrawerMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		static PostEffectDrawerMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<PostEffectDrawer> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		PostEffectDrawerMaker& drawPriority(float value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		PostEffectDrawerMaker& useRtvDescriptorHeapId(unsigned int value);
		
		// 使用するポストエフェクトマテリアルハンドルを設定する
		PostEffectDrawerMaker& postEffectMaterialHandle(unsigned int value);

		// 使用するポストエフェクトマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		template<class IdType, is_idType<IdType> = nullptr>
		PostEffectDrawerMaker& postEffectMaterialId(IdType value);

	private: /* 各種id指定系の関数の実装 */

		PostEffectDrawerMaker& postEffectMaterialIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static PostEffectDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user							{  };
		std::vector<int>	m_targetState					{  };
		float				m_drawPriority					{ 0.0f };
		unsigned int		m_useRtvDescriptorHeapHandle	{  }; // ※初期パラメータはバックバッファー
		unsigned int		m_postEffectMaterialHandle		{ 0U };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		PostEffectDrawerMaker& postEffectMaterialId(IdType value) { static_assert(false, "PostEffectMaterialId Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 使用するポストエフェクトマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline PostEffectDrawerMaker& PostEffectDrawerMaker::postEffectMaterialId(IdType value)
	{
		return postEffectMaterialIdImpl(static_cast<int>(value));
	}

	// ステートを指定し、作成を開始する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline PostEffectDrawerMaker& PostEffectDrawerMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !POST_EFFECT_DRAWER_MAKER_H_