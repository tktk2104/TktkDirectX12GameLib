#ifndef INERTIAL_ROTATEMENT_2D_H_
#define INERTIAL_ROTATEMENT_2D_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	/* class member */
	class Transform2D;

	// ２次元の慣性回転コンポーネント
	// 【前提コンポーネント：Transform2D】
	class InertialRotatement2D
		: public ComponentBase
	{
	public:

		InertialRotatement2D(
			float decelerationPerSec,	// 速度を１秒間でどれだけ減速させるか？
			float initVelocity			// 初期回転速度
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();

	public:

		// 瞬間的に力を加える（引数の値をそのまま速度に加える）
		void addMomentarilyForce(float force);

		// 継続的に力を加える（第一引数の速度を目指して、毎秒第二引数の強さの速度を加える）
		// ※毎フレーム呼んでください
		// ※第一引数がゼロだった場合は何もしません
		void addContinuousForce(float force, float accelerationPerSec);

		// 現在の回転速度を取得
		float getVelocity() const;

		// 現在の回転速度を設定
		void setVelocity(float velocity);

	private:

		// 自身の２次元座標コンポーネント
		ComponentPtr<Transform2D> m_transform2D;

		// 速度
		float m_velocity;

		// 速度を１秒間でどれだけ減速させるか？
		float m_decelerationPerSec;

		// 前フレームで加速したか？
		bool m_preFrameAddForce{ false };
	};
}
#endif // !INERTIAL_ROTATEMENT_2D_H_