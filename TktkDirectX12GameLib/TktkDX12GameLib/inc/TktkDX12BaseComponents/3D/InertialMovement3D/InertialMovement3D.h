#ifndef INERTIAL_MOVEMENT_3D_H_
#define INERTIAL_MOVEMENT_3D_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	class InertialMovement3D
		: public ComponentBase
	{
	public:

		InertialMovement3D(
			float decelerationPerSec,		// 速度を１秒間でどれだけ減速させるか？
			const tktkMath::Vector3 & initVelocity	// 初期速度
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();

	public:

		// 瞬間的に力を加える（引数のベクトルをそのまま速度に加える）
		void addMomentarilyForce(const tktkMath::Vector3& force);

		// 継続的に力を加える（第一引数のベクトルを目指して、毎秒第二引数の長さのベクトルを速度に加える）
		// ※毎フレーム呼んでください
		// ※第一引数がゼロベクトルだった場合は何もしません
		void addContinuousForce(const tktkMath::Vector3& force, float accelerationPerSec);

		// 現在の速度を取得
		tktkMath::Vector3 getVelocity() const;

		// 現在の速度を設定
		void setVelocity(const tktkMath::Vector3& velocity);

	private:

		// 自身の３次元座標コンポーネント
		ComponentPtr<Transform3D> m_transform3D;

		// 速度
		tktkMath::Vector3 m_velocity;

		// 速度を１秒間でどれだけ減速させるか？
		float m_decelerationPerSec;

		// 前フレームで加速したか？
		bool m_preFrameAddForce{ false };
	};
}
#endif // !INERTIAL_MOVEMENT_3D_H_