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
		static InertialMovement3DMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

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
		StateTypeHierarchy		m_targetState		{  };
		float				m_decelerationPerSec{ 64.0f };
		tktkMath::Vector3	m_initVelocity		{ tktkMath::Vector3_v::zero };
	};
}
#endif // !INERTIAL_MOVEMENT_3D_MAKER_H_