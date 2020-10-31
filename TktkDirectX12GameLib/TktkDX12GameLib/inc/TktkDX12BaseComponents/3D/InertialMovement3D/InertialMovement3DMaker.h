#ifndef INERTIAL_MOVEMENT_3D_MAKER_H_
#define INERTIAL_MOVEMENT_3D_MAKER_H_

#include "InertialMovement3D.h"

namespace tktk
{
	// InertialMovement3Dのインスタンスを作成するクラス
	class InertialMovement3DMaker
	{
	private: /* プライベートコンストラクタ達 */

		InertialMovement3DMaker() = default;
		InertialMovement3DMaker(const InertialMovement3DMaker& other) = default;
		InertialMovement3DMaker& operator = (const InertialMovement3DMaker& other) = default;

	public:

		// インスタンス作成開始
		static InertialMovement3DMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		static InertialMovement3DMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<InertialMovement3D> craete();

		// 速度を１秒間でどれだけ減速させるかを設定
		InertialMovement3DMaker& decelerationPerSec(float value);

		// 初期速度を設定
		InertialMovement3DMaker& initVelocity(const tktkMath::Vector3& value);

	private:

		// 自身のポインタ
		static InertialMovement3DMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr		m_user				{ };
		std::vector<int>	m_targetState		{  };
		float				m_decelerationPerSec{ 64.0f };
		tktkMath::Vector3	m_initVelocity		{ tktkMath::Vector3_v::zero };
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// ステートを指定し、作成を開始する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline InertialMovement3DMaker& InertialMovement3DMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !INERTIAL_MOVEMENT_3D_MAKER_H_