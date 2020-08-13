#ifndef TRANSFORM_2D_H_
#define TRANSFORM_2D_H_

#include <TktkMath/Structs/Matrix3.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "TraceParentType.h"

namespace tktk
{
	// ２次元の自身の座標、回転、スケールを管理するコンポーネント
	class Transform2D
		: public ComponentBase
	{
	public:

		Transform2D(
			const tktkMath::Vector2& initPosition,	// 初期座標
			const tktkMath::Vector2& initScaleRate,	// 初期スケール
			float initRotationDeg,			// 初期回転
			TraceParentType traceType		// 親のTransform2Dとの関係性の種類
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();

	public:

		// ワールド座標を取得
		const tktkMath::Vector2& getWorldPosition() const;
		// ワールドスケールを取得
		const tktkMath::Vector2& getWorldScaleRate() const;
		// ワールド回転を取得
		float getWorldRotationDeg() const;

		// ローカル座標を取得
		const tktkMath::Vector2& getLocalPosition() const;
		// ローカルスケールを取得
		const tktkMath::Vector2& getLocalScaleRate() const;
		// ローカル回転を取得
		float getLocalRotationDeg() const;

		// ワールドの行列を計算
		tktkMath::Matrix3 calculateWorldMatrix() const;
		// ローカルの行列を計算
		tktkMath::Matrix3 calculateLocalMatrix() const;

		// ワールド座標を指定分だけ増加
		void addWorldPosition(const tktkMath::Vector2& position);
		// ワールドスケールを指定分だけ増加
		void addWorldScaleRate(const tktkMath::Vector2& scaleRate);
		// ワールド回転を指定分だけ増加
		void addWorldRotationDeg(float rotationDeg);

		// ローカル座標を指定分だけ増加
		void addLocalPosition(const tktkMath::Vector2& position);
		// ローカルスケールを指定分だけ増加
		void addLocalScaleRate(const tktkMath::Vector2& scaleRate);
		// ローカル回転を指定分だけ増加
		void addLocalRotationDeg(float rotationDeg);

		// ワールド座標を設定
		void setWorldPosition(const tktkMath::Vector2& position);
		// ワールドスケールを設定
		void setWorldScaleRate(const tktkMath::Vector2& scaleRate);
		// ワールド回転を設定
		void setWorldRotationDeg(float rotationDeg);

		// ローカル座標を設定
		void setLocalPosition(const tktkMath::Vector2& position);
		// ローカルスケールを設定
		void setLocalScaleRate(const tktkMath::Vector2& scaleRate);
		// ローカル回転を設定
		void setLocalRotationDeg(float rotationDeg);

	private:

		// 新しいローカル行列を指定して自身のローカルのトランスフォームを更新する
		void updateLocalTransform(const tktkMath::Matrix3& newLocalMat);

		// 新しいワールド行列を指定して自身のワールドのトランスフォームを更新する
		void updateWorldTransform(const tktkMath::Matrix3& newWorldMat);

		// 親のTransform2Dを追従するのに使用するワールド行列を取得
		tktkMath::Matrix3 calculateParentTraceUseMat();

		// 親のTransform2Dを取得
		ComponentPtr<Transform2D> findParentTransform2D() const;

		// 全ての子供のTransform2Dを更新する
		void updateAllChildTransform();

		// 指定した子供のTransform2Dを更新する
		void updateChildTransform(const GameObjectPtr& child);

		// 親のTransform2Dを追従するかを判定する
		bool isTransformParentCheck(const ComponentPtr<Transform2D>& parentTransform2D);

		// 親のTransform2Dの追従を開始
		void enableParentTransform();

		// 親のTransform2Dの追従を終了
		void disableParentTransform();

		// 大元のTransformから全ての子供を更新する（生ポインタ版）
		void findAndUpdateRootTransform(Transform2D* curTransform);

		// 大元のTransformから全ての子供を更新する（CfpPtr版）
		void findAndUpdateRootTransform(const ComponentPtr<Transform2D>& curTransform);

	private:

		// 親のTransformを追従しているか？
		bool m_isTransformParent{ false };

		// ローカルの座標
		tktkMath::Vector2 m_localPosition{ tktkMath::vec2Zero };
		// ローカルのスケール
		tktkMath::Vector2 m_localScaleRate{ tktkMath::vec2One };
		// ローカルの回転（度数法）
		float m_localRotationDeg{ 0.0f };

		// ワールドの座標
		tktkMath::Vector2 m_worldPosition{ tktkMath::vec2Zero };
		// ワールドのスケール
		tktkMath::Vector2 m_worldScaleRate{ tktkMath::vec2One };
		// ローカルの回転（度数法）
		float m_worldRotationDeg{ 0.0f };

		// 親のTransform2Dとの関係性
		TraceParentType m_traceType;
	};
}
#endif // !TRANSFORM_2D_H_