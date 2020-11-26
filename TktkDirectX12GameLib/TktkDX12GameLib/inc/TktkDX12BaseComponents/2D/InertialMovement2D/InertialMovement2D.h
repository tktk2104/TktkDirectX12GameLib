#ifndef INERTIAL_MOVEMENT_2D_H_
#define INERTIAL_MOVEMENT_2D_H_

/* class member */
#include <TktkMath/Structs/Vector2.h>

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	/* class member */
	class Transform2D;

	// ２次元の慣性移動コンポーネント
	// 【前提コンポーネント：Transform2D】
	class InertialMovement2D
		: public ComponentBase
	{
	public:

		InertialMovement2D(
			float decelerationPerSec,				// 速度を１秒間でどれだけ減速させるか？
			const tktkMath::Vector2& initVelocity	// 初期速度
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();

	public:

		// 瞬間的に力を加える（引数のベクトルをそのまま速度に加える）
		void addMomentarilyForce(const tktkMath::Vector2& force);

		// 継続的に力を加える（第一引数のベクトルを目指して、毎秒第二引数の長さのベクトルを速度に加える）
		// ※毎フレーム呼んでください
		// ※第一引数がゼロベクトルだった場合は何もしません
		void addContinuousForce(const tktkMath::Vector2& force, float accelerationPerSec);

		// 現在の速度を取得
		const tktkMath::Vector2& getVelocity() const;

		// 現在の速度を設定
		void setVelocity(const tktkMath::Vector2& velocity);

	private:

		// 自身の２次元座標コンポーネント
		ComponentPtr<Transform2D> m_transform2D;

		// 速度
		tktkMath::Vector2 m_velocity;

		// 速度を１秒間でどれだけ減速させるか？
		float m_decelerationPerSec;
	};
}
#endif // !INERTIAL_MOVEMENT_2D_H_