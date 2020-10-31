#ifndef MOTION_CHANGER_MAKER_H_
#define MOTION_CHANGER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "MotionChanger.h"

namespace tktk
{
	// 「MotionChanger」を作るヘルパークラス
	class MotionChangerMaker
	{
	private: /* プライベートコンストラクタ達 */

		MotionChangerMaker() = default;
		MotionChangerMaker(const MotionChangerMaker& other) = default;
		MotionChangerMaker& operator = (const MotionChangerMaker& other) = default;

	public:

		// 作成開始
		static MotionChangerMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		static MotionChangerMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<MotionChanger> create();

	public:  /* パラメータ設定関数 */

		// モーションをループさせるかを設定する
		MotionChangerMaker& isLoop(bool value);

		// 使用するモーションハンドルを設定する
		MotionChangerMaker& initMotionHandle(unsigned int value);

		// 使用するモーションIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		template<class IdType, is_idType<IdType> = nullptr>
		MotionChangerMaker& initMotionId(IdType value);

		// 何秒間かけてモーションの遷移を行うか？
		MotionChangerMaker& lerpTimeSec(float value);

	private: /* 各種id指定系の関数の実装 */

		MotionChangerMaker& initMotionIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static MotionChangerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user				{  };
		std::vector<int>	m_targetState		{  };
		unsigned int		m_isLoop			{ true };
		unsigned int		m_initMotionHandle	{ 0U };
		float				m_lerpTimeSec		{ 1.0f };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MotionChangerMaker& initMotionId(IdType value) { static_assert(false, "MotionId Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// ステートを指定し、作成を開始する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline MotionChangerMaker& MotionChangerMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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

	// 使用する初期モーションIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline MotionChangerMaker& MotionChangerMaker::initMotionId(IdType value)
	{
		return initMotionIdImpl(static_cast<int>(value));
	}
}
#endif // !MOTION_CHANGER_MAKER_H_