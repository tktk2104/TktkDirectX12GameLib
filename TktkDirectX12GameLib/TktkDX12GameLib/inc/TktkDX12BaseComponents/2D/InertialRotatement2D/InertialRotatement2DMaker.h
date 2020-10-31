#ifndef INERTIAL_ROTATEMENT_2D_MAKER_H_
#define INERTIAL_ROTATEMENT_2D_MAKER_H_

#include "InertialRotatement2D.h"

namespace tktk
{
	// InertialRotatement2Dのインスタンスを作成するクラス
	class InertialRotatement2DMaker
	{
	private: /* プライベートコンストラクタ達 */

		InertialRotatement2DMaker() = default;
		InertialRotatement2DMaker(const InertialRotatement2DMaker& other) = default;
		InertialRotatement2DMaker& operator = (const InertialRotatement2DMaker& other) = default;

	public:

		// インスタンス作成開始
		static InertialRotatement2DMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		static InertialRotatement2DMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<InertialRotatement2D> create();

		// 速度を１秒間でどれだけ減速させるかを設定
		InertialRotatement2DMaker& decelerationPerSec(float value);

		// 初期速度を設定
		InertialRotatement2DMaker& initVelocity(float value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		// 自身のポインタ
		static InertialRotatement2DMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user					{ };
		std::vector<int>	m_targetState			{  };
		float				m_decelerationPerSec	{ 30.0f };
		float				m_initVelocity			{ 0.0f };
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// ステートを指定し、作成を開始する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline InertialRotatement2DMaker& InertialRotatement2DMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !INERTIAL_ROTATEMENT_2D_MAKER_H_